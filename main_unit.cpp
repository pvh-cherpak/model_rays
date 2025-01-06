//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1* Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
int pixels_per_meter = 100;
int selected_device = -1;
void TForm1::hide_menu()
{
    LabeledEditX->Visible = false;
	LabeledEditY->Visible = false;
    LabeledEditN->Visible = false;
    LabeledEdit1->Visible = false;
    LabeledEdit2->Visible = false;
    LabeledEdit3->Visible = false;
    LabeledEdit4->Visible = false;
    ButtonAccept->Visible = false;
	ButtonReject->Visible = false;
}

void TForm1::create_menu() {
    ButtonAccept->Visible = true;
	ButtonReject->Visible = true;
    LabeledEditX->Visible = true;
	LabeledEditY->Visible = true;
    LabeledEditN->Visible = true;
	for (int i = 0; i < OpticalDevices[selected_device]->parameter_names.size(); i++){
		menu_LE[i]->Visible = true;
		menu_LE[i]->EditLabel->Caption = OpticalDevices[selected_device]->parameter_names[i];
	}
}

void __fastcall TForm1::Image1Click(TObject* Sender)
{
    for (int i = 0; i < OpticalDevices.size(); i++)
        OpticalDevices[i]->display(Image1->Canvas, pixels_per_meter);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseDown(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    bool is_new_device = false;
    switch (ComboBox1->ItemIndex) {
        case 1:
			is_new_device = true;
            selected_device = OpticalDevices.size();
			OpticalDevices.push_back(std::unique_ptr<VirtualOpticalDevice_t>(
                new ElipseOpticalDevice_t(
					(float)X / pixels_per_meter, -(float)Y / pixels_per_meter)));
			OpticalDevices.front()->display(Image1->Canvas, pixels_per_meter);
            break;
	    case 0:
	    	is_new_device = true;
        default:;
    }
    if (is_new_device) {
       create_menu();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonRejectClick(TObject* Sender)
{
    hide_menu();
    selected_device = -1;
}
//---------------------------------------------------------------------------


