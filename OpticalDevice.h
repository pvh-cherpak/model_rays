class VirtualOpticalDevice_t
{
private:
    /* data */
public:
	VirtualOpticalDevice_t();
	virtual ~VirtualOpticalDevice_t();
	virtual void display(Vcl::Graphics::TCanvas* Canvas, int pixels_per_meter) = 0;
};


class CircleOpticalDevice_t : public VirtualOpticalDevice_t {
public:
	void display(Vcl::Graphics::TCanvas* Canvas, int pixels_per_meter) override;
};

class ElipseOpticalDevice_t : public VirtualOpticalDevice_t {
private:
	float x0 = 0, y0 = 0;
	float a = 1, b = 5;
	float n = 2;
public:
	ElipseOpticalDevice_t(float x0, float y0, float a, float b, float n);
	ElipseOpticalDevice_t(float x0, float y0);
	ElipseOpticalDevice_t();
	void setX0(float x0){this->x0 = x0;}
	void setY0(float y0){this->y0 = y0;}
	void setA(float b){this->a = a;}
	void setB(float a){this->b = b;}
	void setN(float n){this->n = n;}
	void display(Vcl::Graphics::TCanvas* Canvas, int pixels_per_meter) override;
};
