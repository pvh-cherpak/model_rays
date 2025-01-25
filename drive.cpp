#include "drive.h"

basicDrive_t::basicDrive_t(vector<vector<point_t> > &points_v,
    vector<ray_t> &rays_v, vector<bool> &errors) :
    points(points_v),
    rays(rays_v), errors(errors)
{
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
            gradient = grad_n_ch(r.x, r.y, dt);
            vector_t tau_ = (gradient - tau * (tau * gradient)) / n(r.x, r.y);
            if (!iter % 10)
                tau.normalization();
			tau = tau + ((tau_ + prev_tau_) * dt / 2);
			prev_tau_ = tau_;
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
    	double t = y - 2 * sin(x / 6);
    	return exp (- t * t ) + 1;
	//    return 2 - 0.1*y;
//    	if (x > 0)
//			return 1;
//	return exp
}

void basicDrive_t::set_new_x_expression(string &epr_str) {
}

