#include "n.h"
std::string expression_str = "y*0.1 + 1";

n_t global_n_obj;

bool n_t::set_new_expr(std::string &epr_str)
{
#ifdef EXPRTK
	if (!n_parser.compile(epr_str, n_expression)) {
		ShowMessage("Error: " + AnsiString(n_parser.error().c_str()));
		n_parser.compile(expression_str, n_expression);
		return false;
    }
	expression_str = epr_str;
	return true;
#elif defined FPARSER
	if (n_fparser.Parse(epr_str, "x, y") != -1) {
		ShowMessage("Error: " + AnsiString(n_fparser.ErrorMsg()));
		n_fparser.Parse(expression_str, "x, y") ;
        return false;
    }

	expression_str = epr_str;
    return true;
#else
	ShowMessage("Текущая редакция не поддерживает изменение уравнения n(x, y)");
	return false;
#endif
}

double n_t::calculate(double x, double y)
{
#ifdef EXPRTK
    EXPRTK_x = x;
    EXPRTK_y = y;
    return n_expression.value();
#elif defined FPARSER
    double vars[2] = { x, y };
    return n_fparser.Eval(vars);
#else

    //    double t = y - 2 * sin(x / 6);
    //    return exp(-t * t) + 1;
    return 1;
    //    return 2 - 0.1*y;
    //    	if (x > 0)
    //			return 1;
    //	return exp
#endif
}
n_t::n_t(/* args */)
{
#ifdef EXPRTK
    symbol_table.add_variable("x", EXPRTK_x);
    symbol_table.add_variable("y", EXPRTK_y);
    symbol_table.add_constants();

    n_expression.register_symbol_table(symbol_table);

    init();
#elif defined FPARSER
    init();
#endif
}
bool n_t::init()
{
#ifdef EXPRTK
    if (!n_parser.compile(expression_str, n_expression)) {
        ShowMessage("Error: " + AnsiString(n_parser.error().c_str()));
        return false;
    }
    return true;
#elif defined FPARSER
    if (n_fparser.Parse(expression_str, "x, y") != -1) {
		ShowMessage("Error: " + AnsiString(n_fparser.ErrorMsg()));
        return false;
    }
#endif
    return false;
}

n_t::~n_t() {}

