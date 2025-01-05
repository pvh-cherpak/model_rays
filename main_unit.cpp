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

void TForm1::hide_menu()
{
    LabeledEditX->Visible = false;
    LabeledEditY->Visible = false;
    LabeledEdit1->Visible = false;
    LabeledEdit2->Visible = false;
    LabeledEdit3->Visible = false;
    LabeledEdit4->Visible = false;
    ButtonAccept->Visible = false;
    ButtonReject->Visible = false;
}

int pixels_per_meter = 100;
int selected_device = -1;
int selected_device_type = -1;

void __fastcall TForm1::Image1Click(TObject* Sender)
{
    for (int i = 0; i < OpticalDevices.size(); i++)
        OpticalDevices[i]->display(Image1->Canvas, pixels_per_meter);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseDown(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    switch (ComboBox1->ItemIndex) {
        case 1:
            LabeledEditX->Visible = true;
            LabeledEditY->Visible = true;
            LabeledEdit1->Visible = true;
            LabeledEdit1->EditLabel->Caption = "a: ";
            LabeledEdit2->Visible = true;
            LabeledEdit2->EditLabel->Caption = "b: ";
            ButtonAccept->Visible = true;
            ButtonReject->Visible = true;

            selected_device_type = 1;
            selected_device = OpticalDevices.size();
            OpticalDevices.push_back(std::unique_ptr<VirtualOpticalDevice_t>(
                new ElipseOpticalDevice_t((float)X / pixels_per_meter,
                    (float)Y / pixels_per_meter, 0.2, 0.3, 1)));
            OpticalDevices.front()->display(Image1->Canvas, pixels_per_meter);
            break;
        default:;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonRejectClick(TObject* Sender)
{
    hide_menu();
    selected_device_type = -1;
    selected_device = -1;
}
//---------------------------------------------------------------------------


