//---------------------------------------------------------------------------

#ifndef main_unitH
#define main_unitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>

#include <vector>

#include "OpticalDevice.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TButton *Button1;
	TComboBox *ComboBox1;
	TLabeledEdit *LabeledEditX;
	TLabeledEdit *LabeledEditY;
	TLabeledEdit *LabeledEdit3;
	TLabeledEdit *LabeledEdit4;
	TButton *ButtonAccept;
	TButton *ButtonReject;
	TLabeledEdit *LabeledEdit1;
	TLabeledEdit *LabeledEdit2;
	TLabeledEdit *LabeledEditN;
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall ButtonRejectClick(TObject *Sender);
private:	// User declarations
	std::vector <TLabeledEdit*> menu_LE = {LabeledEdit1, LabeledEdit2, LabeledEdit3, LabeledEdit4}  ;

	std::vector<std::unique_ptr<VirtualOpticalDevice_t>> OpticalDevices;
	void hide_menu();
    void create_menu();
//	std::vector<Ray_t>& Rays;
//	UI_t(OpticalDevices, Rays);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
