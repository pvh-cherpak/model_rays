#include "OpticalDevice.h"

VirtualOpticalDevice_t::VirtualOpticalDevice_t()
{
    // ������ ���������� ������������
}

VirtualOpticalDevice_t::~VirtualOpticalDevice_t()
{
    // ������ ���������� �����������
}

void CircleOpticalDevice_t::display(
    Vcl::Graphics::TCanvas* Canvas, int pixels_per_meter)
{
    Canvas->Ellipse(0, 0, 50, 50);
}

ElipseOpticalDevice_t::ElipseOpticalDevice_t() {}
ElipseOpticalDevice_t::ElipseOpticalDevice_t(float x0, float y0)
{
	this->x0 = x0;
	this->y0 = y0;
}
ElipseOpticalDevice_t::ElipseOpticalDevice_t(
    float x0, float y0, float a, float b, float n)
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

