#include <vector>
#include "data_types.h"
#include "vector.h"
#include <math.h>
#include "exprtk.hpp"
#include <string>


//typedef exprtk::symbol_table<double> symbol_table_t;
//typedef exprtk::expression<double> expression_t;
//typedef exprtk::parser<double> parser_t;
//typedef exprtk::derivative<double> derivative_t;

using namespace std;

class basicDrive_t
{
private:
	vector <vector <point_t>>& points;
    vector <ray_t>& rays;
	vector <bool> &errors;

//	double x_;
//	double y_;
//	symbol_table_t symbol_table_x;
//	expression_t expression_x;
//	parser_t parser;
//	derivative_t derivative;
//	expression_t derivative_expression_x;

public:
	basicDrive_t(vector <vector <point_t>>& points,
					vector <ray_t>& rays_v,
					vector <bool> &errors);
	void calculate();
	void set_new_x_expression(string &epr_str);
    double n(double x, double y);
    ~basicDrive_t();
private:
vector_t grad_n_ch(double x, double y, double dt);
    vector_t grad_n(double x, double y);
};

