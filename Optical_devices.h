#ifndef OPTICAL_DEVICES_H
#define OPTICAL_DEVICES_H
#include <vector>
#include "n.h"

extern n_t global_n_obj;

using namespace std;

struct point
{
    double x, y;
};

struct pryam
{
    double a, b, c;
};

struct segment
{
    point p1, p2;
};

struct ray
{
    segment s;
    pryam pr;
};


class Optical_devices
{
    public:
        double sin_pr(pryam pr1, pryam pr2);
        double rast_pr(point p, pryam pr);
        double rast_seg(point p, segment s);
        pryam normal(point p, pryam pr);
        bool is_cross_seg(pryam pr, segment s);
        point tchk_segment_ray(segment s, ray r);
        bool is_tchk_ray(segment s, point p);
        pryam to_pryam(segment s);
		void zerkalo(ray &r, pryam lin1, point p1, pryam lin2);
        bool check_razn2(point t1, point t2, pryam lin1, pryam lin2);

        Optical_devices();
        virtual ~Optical_devices();
        virtual double s_to_dev(ray r) = 0;
		virtual bool is_crossing(ray r) = 0;
        virtual void get_segments(ray &r, bool &is_pvo, vector < segment > &otr) = 0;


};

class Nugol: public Optical_devices
{
    private:
        int k;
		vector < segment > seg;
		double n;
		double op_dl_pt;
		double sinus11, sinus2;
	public:
		Nugol(int a, vector < segment > &b, double c):
		k(a), seg(b), n(c){}
        Nugol(){}
		void set_Nugol(int a, vector < segment > &b, double c);
		double s_to_dev(ray r);
        bool is_crossing(ray r);
		void get_segments(ray &r, bool &is_pvo, vector < segment > &otr);
		double get_prel();
		bool check(point p);
		bool check_razn(point t1, point t2, pryam lin1, pryam lin2);
		void set_op_dl_pt(double a);
		double get_op_dl_pt();
		int get_ugl_vhoda();
		int get_ugl_vyhoda();
		void get_vector(vector < segment > &s);
};

#endif // OPTICAL_DEVICES_H
