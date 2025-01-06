#include "OpticalDevice.h"

const std::vector<String> ElipseOpticalDevice_t::param_names = {"A: ", "B:"};


VirtualOpticalDevice_t::VirtualOpticalDevice_t(
	const std::vector<String>& param_names)
    : parameter_names(param_names)
{
}

void VirtualOpticalDevice_t::set_params(std::vector<float>& params){
	for(int i = 0; i < params.size(); i++)
		parametrs[i]=params[i];
}

VirtualOpticalDevice_t::~VirtualOpticalDevice_t()
{
}


ElipseOpticalDevice_t::ElipseOpticalDevice_t()
: VirtualOpticalDevice_t(param_names){}
ElipseOpticalDevice_t::ElipseOpticalDevice_t(float x0, float y0)
: VirtualOpticalDevice_t(param_names)
{
	this->x0 = x0;
	this->y0 = y0;
	this->a = 0.5;
    this->b = 0.2;
}
ElipseOpticalDevice_t::ElipseOpticalDevice_t(
	float x0, float y0, float a, float b, float n)
: VirtualOpticalDevice_t(param_names)
{
    this->x0 = x0;
	this->y0 = y0;
	this->a = a;
	this->b = b;
    this->n = n;
}

void ElipseOpticalDevice_t::display(
    Vcl::Graphics::TCanvas* Canvas, int pixels_per_meter)
{
    int X = x0 * pixels_per_meter;
    int Y = y0 * pixels_per_meter;
    int A = a * pixels_per_meter;
	int B = b * pixels_per_meter;

	Canvas->Pen->Color = clBlue;
	Canvas->Brush->Color = clBlue;

	Canvas->Ellipse(X - A, Y - B, X + A, Y + B);
}

