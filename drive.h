#include <vector>
#include "data_types.h"
#include "vector.h"
#include <math.h>
#include <string>
#include "n.h"

using namespace std;

class basicDrive_t
{
  private:
    vector<vector<point_t> > &points;
    vector<ray_t> &rays;
    vector<bool> &errors;
    n_t n_obj;
    
  public:
    basicDrive_t(vector<vector<point_t> > &points, vector<ray_t> &rays_v,
        vector<bool> &errors);
    void calculate();
    bool set_new_n_expression(string &epr_str);
	double n(double x, double y);
	string get_n_expression_str()
    {
        return expression_str;
    }

    ~basicDrive_t();
  private:
    vector_t grad_n_ch(double x, double y, double dt);
    vector_t grad_n(double x, double y);
};

