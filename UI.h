#include "OpticalDevice.h"
#include <vector>

class UI_t
{
private:
    int pixels_per_meter = 1000;
    std::vector<std::unique_ptr<VirtualOpticalDevice_t>>& devices_; 
	std::vector<Ray_t>& rays_;
    TButton *ButtonAccept;
	TButton *ButtonReject;
    TImage *Image;
    TLabeledEdit *LabeledEditX;
	TLabeledEdit *LabeledEditY;
	TLabeledEdit *LabeledEdit1;
	TLabeledEdit *LabeledEdit2;
private:
	int selected_device_ = -1;
	int selected_device_type = -1;
public:
    UI_t(std::vector<std::unique_ptr<VirtualOpticalDevice_t>>& opticalDevices,
		 std::vector<Ray_t>& rays, TImage *Image,
         TLabeledEdit *LabeledEditX, TLabeledEdit *LabeledEditY,
         TButton *ButtonAccept,
         TButton *ButtonReject,
	     TLabeledEdit *LabeledEdit1, TLabeledEdit *LabeledEdit2);
    newDevice(int X, int Y, int type);
    ~UI_t();
};

UI_t::UI_t(std::vector<std::unique_ptr<VirtualOpticalDevice_t>>& opticalDevices,
		 std::vector<Ray_t>& rays, TImage *Image,
         TLabeledEdit *LabeledEditX, TLabeledEdit *LabeledEditY,
         TButton *ButtonAccept,
         TButton *ButtonReject,
	     TLabeledEdit *LabeledEdit1, TLabeledEdit *LabeledEdit2)
{
    this.rays_ = rays;
    this.devices_ = opticalDevices;
    this.Image = Image;
    this.ButtonAccept = ButtonAccept;
	this.ButtonReject = ButtonReject;
    this.LabeledEditX = LabeledEditX;
	this.LabeledEditY = LabeledEditY;
	this.LabeledEdit1 = LabeledEdit1;
	this.LabeledEdit2 = LabeledEdit2;
}

UI_t::~UI_t()
{
}
