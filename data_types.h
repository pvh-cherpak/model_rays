#pragma once
#include <cmath>
struct point_t
{
	double x = 0;
	double y = 0;

	point_t getRounded(){
		return{round(x), round(y)};
	}
};

struct ray_t
{
	 point_t point;
     double direction = 0;
};
