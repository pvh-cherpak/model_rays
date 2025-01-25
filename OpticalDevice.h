#include <vector>
#include <string>

class VirtualOpticalDevice_t
{
  protected:
    float &x0 = parametrs[0];
    float &y0 = parametrs[1];
    float &n = parametrs[2];
  public:
    float parametrs[7];
    const std::vector<String> &parameter_names;

    void set_params(std::vector<float> &params);
    void setX0(float x0)
    {
        this->x0 = x0;
    }
    void setY0(float y0)
    {
        this->y0 = y0;
    }
    void setN(float N)
    {
        this->n = N;
    }

    VirtualOpticalDevice_t(const std::vector<String> &param_names);
    virtual ~VirtualOpticalDevice_t();
    virtual void display(
        Vcl::Graphics::TCanvas* Canvas, int pixels_per_meter) = 0;
};

class ElipseOpticalDevice_t : public VirtualOpticalDevice_t
{
  private:
    float &a = parametrs[3];
    float &b = parametrs[4];
  public:
    ElipseOpticalDevice_t(float x0, float y0, float a, float b, float n);
    ElipseOpticalDevice_t(float x0, float y0);
    ElipseOpticalDevice_t();
    void display(Vcl::Graphics::TCanvas* Canvas, int pixels_per_meter) override;
  private:
    const static std::vector<String> param_names;
};

