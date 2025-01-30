#pragma once

#define EXPRTK
//#define FPARSER

#ifdef EXPRTK
    #include "exprtk.hpp"
typedef exprtk::symbol_table<double> symbol_table_t;
typedef exprtk::expression<double> expression_t;
typedef exprtk::parser<double> parser_t;
#elif defined FPARSER
    #include "fparser.hh"
#endif


#include <string>

extern std::string expression_str;

class n_t
{
private:
	bool init();
#ifdef EXPRTK
    symbol_table_t symbol_table;
    expression_t n_expression;
    parser_t n_parser;
    double EXPRTK_x;
    double EXPRTK_y;
#elif defined FPARSER
    FunctionParser n_fparser;
#endif
public:
    bool set_new_expr(std::string &epr_str);
    double calculate (double x, double y);
    n_t(/* args */);
    ~n_t();
};


extern n_t global_n_obj;


