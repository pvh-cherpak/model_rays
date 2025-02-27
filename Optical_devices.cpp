#include "Optical_devices.h"
#include <cmath>
#include <iomanip>

using namespace std;

Optical_devices::Optical_devices()
{
    //ctor
}

Optical_devices::~Optical_devices()
{
    //dtor
}

pryam Optical_devices::normal(point p, pryam pr)
{
    pryam otv;
    otv.a = pr.b;
    otv.b = -pr.a;
    otv.c = pr.a * p.y - pr.b * p.x;
    return otv;
}

double Optical_devices::rast_pr(point p, pryam pr)
{
    double otv;
    otv = (fabs(pr.a * p.x + pr.b * p.y + pr.c)) / (sqrt(pr.a * pr.a + pr.b * pr.b));
    return otv;
}

double Optical_devices::sin_pr(pryam pr1, pryam pr2)
{
    double t1, t2, otv;
    t2 = pr1.a * pr2.a + pr1.b * pr2.b;
    if(fabs(t2) <= 0.00001)
        return 1;
    t1 = pr1.a * pr2.b - pr2.a * pr1.b;
	otv = fabs(1. * t1 / t2);
    otv = sin(atan(otv));
    return fabs(otv);
}

double Optical_devices::rast_seg(point p, segment s)
{
    point t1, t2, t3;
    double r, a, b, c, r1;
    t1.x = p.x; t1.y = p.y;
    t2.x = s.p1.x; t2.y = s.p1.y;
    t3.x = s.p2.x; t3.y = s.p2.y;

    t1.x = t1.x - t2.x;
    t1.y = t1.y - t2.y;
    t3.x = t3.x - t2.x;
    t3.y = t3.y - t2.y;
    t2.x = 0;
    t2.y = 0;
    a = t3.y;
    b = -1. * t3.x;
    c = 0;
    bool b1 = false, b2 = false;
    if(t1.x * t3.x + t1.y * t3.y < 0)
        b1 = true;
       r = sqrt(t1.x * t1.x + t1.y * t1.y);
    t1.x = t1.x - t3.x;
    t1.y = t1.y - t3.y;
    t2.x = t2.x - t3.x;
    t2.y = t2.y - t3.y;
    t3.x = 0;
    t3.y = 0;
       r1 = sqrt(t1.x * t1.x + t1.y * t1.y);
    a = t2.y;
    b = -1. * t2.x;
    c = 0;
    if(t1.x * t2.x + t1.y * t2.y < 0)
       b2 = true;
	if(b1 || b2)
	{
		if(r1 < r)
            r = r1;
	}
    else
       r = fabs(a * t1.x + b * t1.y + c) / sqrt(a * a + b * b);
    return r;
}

bool Optical_devices::is_cross_seg(pryam pr, segment s)
{
    double z1, z2;
    z1 = pr.a * s.p1.x + pr.b * s.p1.y + pr.c;
    z2 = pr.a * s.p2.x + pr.b * s.p2.y + pr.c;
    if(z1 * z2 < 0.00001)
        return true;
    else
        return false;

}

point Optical_devices::tchk_segment_ray(segment s, ray r)
{
    double x, y;
    pryam p1, p2;
    p2 = r.pr;
    p1.a = s.p2.y - s.p1.y;
    p1.b = s.p1.x - s.p2.x;
    p1.c = s.p1.y * s.p2.x - s.p2.y * s.p1.x;
    x = (p1.b * p2.c - p2.b * p1.c) / (p1.a * p2.b - p2.a * p1.b);
    y = (p2.a * p1.c - p1.a * p2.c) / (p1.a * p2.b - p2.a * p1.b);
    point otv;
    otv.x = x;
    otv.y = y;
    return otv;
}

bool Optical_devices::is_tchk_ray(segment s, point p)
{
   if(((p.x - s.p1.x) * (s.p2.x - s.p1.x) >= 0) && ((p.y - s.p1.y) * (s.p2.y - s.p1.y) >= 0))
    return true;
   else
    return false;

}

pryam Optical_devices::to_pryam(segment s)
{
    pryam otv;
    otv.a = s.p1.y - s.p2.y;
    otv.b = s.p2.x - s.p1.x;
    otv.c = s.p1.y * (s.p1.x - s.p2.x) - s.p1.x * (s.p1.y - s.p2.y);
    return otv;
}

bool Optical_devices::check_razn2(point t1, point t2, pryam lin1, pryam lin2)
{
  if((lin1.a * t1.x + lin1.b * t1.y + lin1.c) * (lin1.a * t2.x + lin1.b * t2.y + lin1.c) < 0)
	return false;
  if((lin2.a * t1.x + lin2.b * t1.y + lin2.c) * (lin2.a * t2.x + lin2.b * t2.y + lin2.c) > 0)
	return false;
  return true;
}

void Optical_devices::zerkalo(ray &r, pryam lin1, point p1, pryam lin2, double shag)
{
	/**pryam checker;
	double sinus;
	sinus = sin_pr(r.pr, lin2);
	checker.a = tan(asin(sinus) + atan(-lin2.a / lin2.b));
    checker.b = -1.;
    checker.c = p1.y - checker.a * p1.x;
    if(sin_pr(r.pr, checker) < 0.00001)
    {
	   checker.a = tan(-asin(sinus) + atan(-lin2.a / lin2.b));
       checker.b = -1.;
       checker.c = p1.y - checker.a * p1.x;
    }
    point poi1;
    poi1.x = p1.x + 1;
    poi1.y = (-checker.a * poi1.x - checker.c) / checker.b;
    segment otr;
    otr.p1 = r.s.p2;
    otr.p2 = poi1;
    if(is_cross_seg(to_pryam(s1), otr))
    {
       r.pr = checker;
       poi1.x = p1.x - 1;
       poi1.y = (-checker.a * poi1.x - checker.c) / checker.b;
       r.s.p1 = poi1;
       poi1.x = p1.x - 2;
       poi1.y = (-checker.a * poi1.x - checker.c) / checker.b;
       r.s.p2 = poi1;
    }
    else
    {
       r.pr = checker;
       r.s.p1 = poi1;
       poi1.x = p1.x + 2;
       poi1.y = (-checker.a * poi1.x - checker.c) / checker.b;
	   r.s.p2 = poi1;
	} **/

	double sinus2;
	sinus2 = sin_pr(r.pr, lin2);
	pryam plus_sin, min_sin;
	min_sin.a = tan(-asin(sinus2) + atan(-lin2.a / lin2.b));
	plus_sin.a = tan(asin(sinus2) + atan(-lin2.a / lin2.b));
	min_sin.b = -1.;
	min_sin.c = p1.y - min_sin.a * p1.x;
	plus_sin.b = -1.;
	plus_sin.c = p1.y - plus_sin.a * p1.x;


	point checker_point;
	checker_point.x = p1.x + shag;
	checker_point.y = (-plus_sin.a * checker_point.x - plus_sin.c) / plus_sin.b;
	if(check_razn2(checker_point, r.s.p1, lin1, lin2))
	{
		r.s.p1 = checker_point;
		checker_point.x = p1.x + 2 * shag;
		checker_point.y = (-plus_sin.a * checker_point.x - plus_sin.c) / plus_sin.b;
		r.s.p2 = checker_point;
		r.pr = plus_sin;
	}
	else
	{
	  checker_point.x = p1.x - shag;
	  checker_point.y = (-plus_sin.a * checker_point.x - plus_sin.c) / plus_sin.b;
	  if(check_razn2(checker_point, r.s.p1, lin1, lin2))
	  {
		r.s.p1 = checker_point;
		checker_point.x = p1.x - 2 * shag;
		checker_point.y = (-plus_sin.a * checker_point.x - plus_sin.c) / plus_sin.b;
		r.s.p2 = checker_point;
		r.pr = plus_sin;
	  }
	  else
	  {
		  checker_point.x = p1.x + shag;
		  checker_point.y = (-min_sin.a * checker_point.x - min_sin.c) / min_sin.b;
		  if(check_razn2(checker_point, r.s.p1, lin1, lin2))
		  {
			r.s.p1 = checker_point;
			checker_point.x = p1.x + 2 * shag;
			checker_point.y = (-min_sin.a * checker_point.x - min_sin.c) / min_sin.b;
			r.s.p2 = checker_point;
			r.pr = min_sin;
		  }
		  else
		  {
			  checker_point.x = p1.x - shag;
			  checker_point.y = (-min_sin.a * checker_point.x - min_sin.c) / min_sin.b;
			  if(check_razn2(checker_point, r.s.p1, lin1, lin2))
			  {
				r.s.p1 = checker_point;
				checker_point.x = p1.x - 2 * shag;
				checker_point.y = (-min_sin.a * checker_point.x - min_sin.c) / min_sin.b;
				r.s.p2 = checker_point;
				r.pr = min_sin;
			  }
          }
      }
	}



}

void Nugol::set_Nugol(int a, vector < segment > &b, double c)
{
   k = a;
   seg = b;
   n = c;
}

double Nugol::get_prel()
{
    return n;
}

void Nugol::get_vector(vector < segment > &s)
{
	s = seg;
}

double Nugol::s_to_dev(ray r)
{
    point p;
    p.x = r.s.p2.x;
    p.y = r.s.p2.y;
    double mini = rast_seg(p, seg[0]);
    for(int i = 1; i < k; i++)
    {
        double t;
       t = rast_seg(p, seg[i]);
       if(t < mini)
            mini = t;
    }
    return mini;
}

bool Nugol::check_razn(point t1, point t2, pryam lin1, pryam lin2)
{
  if((lin1.a * t1.x + lin1.b * t1.y + lin1.c) * (lin1.a * t2.x + lin1.b * t2.y + lin1.c) > 0)
	return false;
  if((lin2.a * t1.x + lin2.b * t1.y + lin2.c) * (lin2.a * t2.x + lin2.b * t2.y + lin2.c) > 0)
	return false;
  return true;
}

bool Nugol::is_crossing(ray r)
{
    bool otv = false;
    for(int i = 0; i < k; i++)
    {
        if(is_cross_seg(r.pr, seg[i]))
        {
            point p;
            p = tchk_segment_ray(seg[i], r);
            if(is_tchk_ray(r.s, p))
                return true;
        }
    }
    return otv;
}

bool Nugol::check(point p)
{
   bool otv = true;
    double k2;
    point p1, p2;
    p1 = seg[0].p1;
    p2 = seg[0].p2;
    k2 = (p1.y - p2.y) * (p1.x - p.x) - (p1.y - p.y) * (p1.x - p2.x);
    if(fabs(k2) < 0.00001)
        k2 = 0;
    for(int i = 1; i < k; i++)
    {
        double k1;
        p1 = seg[i].p1;
        p2 = seg[i].p2;
        k1 = (p1.y - p2.y) * (p1.x - p.x) - (p1.y - p.y) * (p1.x - p2.x);
        if(k1 * k2 <= 0)
            otv = false;
    }
    return otv;
}

bool Nugol::check_better(point p)
{
	ray ex_ray;
	int otv = 0;
	ex_ray.s.p1 = p;
	ex_ray.s.p2.x = p.x + shag;
	ex_ray.s.p2.y = p.y;
	ex_ray.pr = to_pryam(ex_ray.s);

    for(int i = 0; i < k; i++)
	{
		if(is_cross_seg(ex_ray.pr, seg[i]))
		{
			point ppp;
			ppp = tchk_segment_ray(seg[i], ex_ray);
			if(fabs(ppp.x - seg[i].p1.x) <= 0.1 && fabs(ppp.y - seg[i].p1.y) <= 0.1)
				continue;
			if(fabs(ppp.x - seg[i].p2.x) <= 0.1 && fabs(ppp.y - seg[i].p2.y) <= 0.1)
				continue;
			if(is_tchk_ray(ex_ray.s, ppp))
			{
			   otv++;
			}
		}
	}

	return otv % 2;
}

void Nugol::set_op_dl_pt(double a)
{
   op_dl_pt = a;
}

double Nugol::get_op_dl_pt()
{
    return op_dl_pt;
}

int Nugol::get_ugl_vhoda()
{
	int otv;
	otv = asin(sinus11) * 180 / acos(-1);
	return otv;
}

int Nugol::get_ugl_vyhoda()
{
	int otv;
	otv = asin(sinus2) * 180 / acos(-1);
	return otv;
}

void Nugol::get_segments(ray &r, bool &is_pvo, vector < segment > &otr)
{
    segment s1;
    point p1;
    segment otv;
    double mini = -1;
    //nahozhdenie tochki vhoda
	for(int i = 0; i < k; i++)
	{
		if(is_cross_seg(r.pr, seg[i]))
		{
			point p;
			p = tchk_segment_ray(seg[i], r);
			if(is_tchk_ray(r.s, p))
			{
                double l;
                l = sqrt((r.s.p2.x - p.x) * (r.s.p2.x - p.x) + (r.s.p2.y - p.y) * (r.s.p2.y - p.y));
                if(mini == -1)
                {
                    mini = l;
                    p1 = p;
                    s1 = seg[i];
                }
                else
                    if(mini > l)
                {
                    mini = l;
                    p1 = p;
                    s1 = seg[i];
                }
            }
        }
    }
    otv.p1 = p1;

    //proniknovenie

    pryam lin1, lin2;
    lin1 = to_pryam(s1);
	lin2 = normal(p1, lin1);
	double sinus1, n_vhoda;
	sinus1 = sin_pr(r.pr, lin2);
	sinus11 = sinus1;

    //ShowMessage(FloatToStr(global_n_obj.calculate(r.s.p1.x, r.s.p1.y)));
	sinus2 = global_n_obj.calculate(r.s.p1.x, r.s.p1.y) * sinus1 / n;
	//sinus2 = 1. * sinus1 / n;
	//????????????????????????????????
	pryam plus_sin, min_sin;
	min_sin.a = tan(-asin(sinus2) + atan(-lin2.a / lin2.b));
	plus_sin.a = tan(asin(sinus2) + atan(-lin2.a / lin2.b));
	min_sin.b = -1.;
	min_sin.c = p1.y - min_sin.a * p1.x;
	plus_sin.b = -1.;
	plus_sin.c = p1.y - plus_sin.a * p1.x;


	point checker_point;
	checker_point.x = p1.x + shag;
	checker_point.y = (-plus_sin.a * checker_point.x - plus_sin.c) / plus_sin.b;
	if(check_razn(checker_point, r.s.p1, lin1, lin2))
	{
		r.s.p1 = checker_point;
		checker_point.x = p1.x + 2 * shag;
		checker_point.y = (-plus_sin.a * checker_point.x - plus_sin.c) / plus_sin.b;
		r.s.p2 = checker_point;
		r.pr = plus_sin;
	}
	else
	{
	  checker_point.x = p1.x - shag;
	  checker_point.y = (-plus_sin.a * checker_point.x - plus_sin.c) / plus_sin.b;
	  if(check_razn(checker_point, r.s.p1, lin1, lin2))
	  {
		r.s.p1 = checker_point;
		checker_point.x = p1.x - 2 * shag;
		checker_point.y = (-plus_sin.a * checker_point.x - plus_sin.c) / plus_sin.b;
		r.s.p2 = checker_point;
		r.pr = plus_sin;
	  }
	  else
	  {
		  checker_point.x = p1.x + shag;
		  checker_point.y = (-min_sin.a * checker_point.x - min_sin.c) / min_sin.b;
		  if(check_razn(checker_point, r.s.p1, lin1, lin2))
		  {
			r.s.p1 = checker_point;
			checker_point.x = p1.x + 2 * shag;
			checker_point.y = (-min_sin.a * checker_point.x - min_sin.c) / min_sin.b;
			r.s.p2 = checker_point;
			r.pr = min_sin;
		  }
		  else
		  {
			  checker_point.x = p1.x - shag;
			  checker_point.y = (-min_sin.a * checker_point.x - min_sin.c) / min_sin.b;
			  if(check_razn(checker_point, r.s.p1, lin1, lin2))
			  {
				r.s.p1 = checker_point;
				checker_point.x = p1.x - 2 * shag;
				checker_point.y = (-min_sin.a * checker_point.x - min_sin.c) / min_sin.b;
				r.s.p2 = checker_point;
				r.pr = min_sin;
			  }
          }
      }
    }



    is_pvo = true;
	int otrazh = 0;
   /**if(!check(r.s.p1))
	{
		is_pvo = false;
		otv.p2 = r.s.p1;
        otr.push_back(otv);
	} **/

    while(is_pvo && otrazh < 10)
    {
        otrazh++;
        mini = -1;
        //nahozhdenie tochki vyhoda
        for(int i = 0; i < k; i++)
        {
            if(is_cross_seg(r.pr, seg[i]))
            {
                point p;
                p = tchk_segment_ray(seg[i], r);
                if(is_tchk_ray(r.s, p))
                {
                    double l;
                    l = sqrt((r.s.p2.x - p.x) * (r.s.p2.x - p.x) + (r.s.p2.y - p.y) * (r.s.p2.y - p.y));
                    if(mini == -1)
                    {
                        mini = l;
                        p1 = p;
                        s1 = seg[i];
                    }
                    else
                        if(mini > l)
                    {
                        mini = l;
                        p1 = p;
                        s1 = seg[i];
                    }
                }
            }
        }
        otv.p2 = p1;
        otr.push_back(otv);
        otv.p1 = p1;

        lin1 = to_pryam(s1);
        lin2 = normal(p1, lin1);
		//double sinus1, sinus2;
		sinus1 = sin_pr(r.pr, lin2);

		point n_checker_point;
		n_checker_point.x = p1.x + shag;
		n_checker_point.y = (-lin2.a * n_checker_point.x - lin2.c) / lin2.b;
		if(check_better(n_checker_point))
		{
			 n_checker_point.x = p1.x - shag;
			 n_checker_point.y = (-lin2.a * n_checker_point.x - lin2.c) / lin2.b;
		}

	   sinus2 = n * sinus1 / global_n_obj.calculate(n_checker_point.x, n_checker_point.y);
		//sinus2 = n * sinus1 / 1.;

        if(sinus2 > 1 || sinus2 < -1)
        {
			zerkalo(r, lin1, p1, lin2, shag);
        }
        else
        {
			min_sin.a = tan(-asin(sinus2) + atan(-lin2.a / lin2.b));
			plus_sin.a = tan(asin(sinus2) + atan(-lin2.a / lin2.b));
			min_sin.b = -1.;
			min_sin.c = p1.y - min_sin.a * p1.x;
			plus_sin.b = -1.;
			plus_sin.c = p1.y - plus_sin.a * p1.x;


			checker_point.x = p1.x + shag;
			checker_point.y = (-plus_sin.a * checker_point.x - plus_sin.c) / plus_sin.b;
			if(check_razn(checker_point, r.s.p1, lin1, lin2))
			{
				r.s.p1 = checker_point;
				checker_point.x = p1.x + 2 * shag;
				checker_point.y = (-plus_sin.a * checker_point.x - plus_sin.c) / plus_sin.b;
				r.s.p2 = checker_point;
				r.pr = plus_sin;
			}
			else
			{
			  checker_point.x = p1.x - shag;
			  checker_point.y = (-plus_sin.a * checker_point.x - plus_sin.c) / plus_sin.b;
			  if(check_razn(checker_point, r.s.p1, lin1, lin2))
			  {
				r.s.p1 = checker_point;
				checker_point.x = p1.x - 2 * shag;
				checker_point.y = (-plus_sin.a * checker_point.x - plus_sin.c) / plus_sin.b;
				r.s.p2 = checker_point;
				r.pr = plus_sin;
			  }
			  else
			  {
				  checker_point.x = p1.x + shag;
				  checker_point.y = (-min_sin.a * checker_point.x - min_sin.c) / min_sin.b;
				  if(check_razn(checker_point, r.s.p1, lin1, lin2))
				  {
					r.s.p1 = checker_point;
					checker_point.x = p1.x + 2 * shag;
					checker_point.y = (-min_sin.a * checker_point.x - min_sin.c) / min_sin.b;
					r.s.p2 = checker_point;
					r.pr = min_sin;
				  }
				  else
				  {
					  checker_point.x = p1.x - shag;
					  checker_point.y = (-min_sin.a * checker_point.x - min_sin.c) / min_sin.b;
					  if(check_razn(checker_point, r.s.p1, lin1, lin2))
					  {
						r.s.p1 = checker_point;
						checker_point.x = p1.x - 2 * shag;
						checker_point.y = (-min_sin.a * checker_point.x - min_sin.c) / min_sin.b;
						r.s.p2 = checker_point;
						r.pr = min_sin;
					  }
				  }
			  }
			}
            is_pvo = false;
        }
	}

	op_dl_pt = 0;
	for(int i = 0; i < otr.size(); i++)
	{
	   double temp;
	   temp = sqrt((otr[i].p1.x - otr[i].p2.x)*(otr[i].p1.x - otr[i].p2.x) + (otr[i].p1.y - otr[i].p2.y)*(otr[i].p1.y - otr[i].p2.y));
	   op_dl_pt += temp;
	}
    op_dl_pt *= n;
}
