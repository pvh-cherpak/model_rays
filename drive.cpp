#include "drive.h"


pryam to_pr(segment s)
{
    pryam otv;
    otv.a = s.p1.y - s.p2.y;
    otv.b = s.p2.x - s.p1.x;
    otv.c = s.p1.y * (s.p1.x - s.p2.x) - s.p1.x * (s.p1.y - s.p2.y);
    return otv;
}

basicDrive_t::basicDrive_t(vector<vector<point_t> > &points_v,
    vector<ray_t> &rays_v, vector<bool> &errors, vector<Nugol> &vec_N) :
    points(points_v),
    rays(rays_v), errors(errors), vec_N(vec_N)
{
	string s =  "y*0.1+1";
	n_obj.set_new_expr(s);
}

vector_t basicDrive_t::grad_n_ch(double x, double y, double dt)
{
    double bN = n(x, y);
    double dNx = (n(x + dt, y) - bN) / dt;
    double dNy = (n(x, y + dt) - bN) / dt;
    return vector_t(dNx, dNy);
}

void basicDrive_t::calculate()
{
    points.clear();
    errors.clear();
    errors.resize(rays.size());
    double dt = 0.005;
    for (int ray_i = 0; ray_i < rays.size(); ray_i++) {
        vector<point_t> points_;
		points_.reserve(10000);
		vector_t r(rays[ray_i].point.x, rays[ray_i].point.y);
		vector_t tau(cos(rays[ray_i].direction), sin(rays[ray_i].direction));

		vector_t prev_tau = tau;
		vector_t gradient = grad_n_ch(r.x, r.y, dt);
		vector_t prev_tau_ = (gradient - tau * (tau * gradient)) / n(r.x, r.y);
		for (int iter = 1; iter < 10000; iter++) {
			if (n(r.x, r.y) < 1) {
				errors[ray_i] = true;
				break;
			}
			if(iter % 3 == 0)
			{
				ray r_dev;
				r_dev.s.p1.x = rays[ray_i - 1].point.x;
				r_dev.s.p1.y = rays[ray_i - 1].point.y;
				r_dev.s.p2.x = rays[ray_i].point.x;
				r_dev.s.p2.y = rays[ray_i].point.y;
				r_dev.pr = to_pr(r_dev.s);

                int pos = -1;
				double mini = -1;
				bool ok = false;
				for(int i = 0; i < vec_N.size(); i++)
				{
					if(vec_N[i].is_crossing(r_dev))
					{
						double temp = vec_N[i].s_to_dev(r_dev);
						if((pos == -1 && temp < 3. * dt) || (pos != -1 && temp < mini))
						{
							pos = i;
							mini = temp;
						}
					}
				}
				if(pos != -1)
				{
					vector < segment > otr;
					vec_N[pos].get_segments(r_dev, ok, otr);
					points_.push_back({ otr[0].p1.x, otr[0].p1.y });
					for(int i = 0; i < otr.size(); i++)
					{
					  points_.push_back({ otr[i].p2.x, otr[i].p2.y });
					}
					points_.push_back({ r_dev.s.p2.x, r_dev.s.p2.y });

					vector_t r2(r_dev.s.p2.x, r_dev.s.p2.y);
					vector_t tau2(r_dev.s.p2.x - r_dev.s.p1.x, r_dev.s.p2.y - r_dev.s.p1.y);
					tau2.normalization();
					r = r2;
					tau = tau2;

					prev_tau = tau;
					gradient = grad_n_ch(r.x, r.y, dt);
					prev_tau_ = (gradient - tau * (tau * gradient)) / n(r.x, r.y);

					otr.resize(0);
					pos = -1;
					mini = -1;
				}
				if (ok) {
				errors[ray_i] = true;
				break;
				}



            }
			gradient = grad_n_ch(r.x, r.y, dt);
			vector_t tau_ = (gradient - tau * (tau * gradient)) / n(r.x, r.y);
			if (!iter % 10)
				tau.normalization();
            tau = tau + ((tau_ + prev_tau_) * dt / 2);
			prev_tau_ = tau_;
            vector_t prev_r = r;
            r = r + (tau + prev_tau) * dt / 2;
            prev_tau = tau;
			points_.push_back({ r.x, r.y });
		}
        points.push_back(points_);
    }
}

basicDrive_t::~basicDrive_t() {}

double basicDrive_t::n(double x, double y)
{
   return n_obj.calculate(x, y);
}

bool basicDrive_t::set_new_n_expression(string &epr_str)
{
    return n_obj.set_new_expr(epr_str);
}

