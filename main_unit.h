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
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.Menus.hpp>

#include <vector>
#include <algorithm>
#include <chrono>

#include "OpticalDevice.h"
#include "data_types.h"
#include "drive.h"
#include "vector.h"
#include "Optical_devices.h"
#include "visual_functios.h"

enum class menu_type
{
    ray_source,
    field,
    Optical_dev,
    NONE
};

const double RAD_TO_DEG = 180.0 / acos(-1);
const double DEG_TO_RAD = acos(-1) / 180.0;

using namespace std;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
  __published: // IDE-managed Components
    TImage* Image1;
    TButton* Button1;
    TComboBox* ComboBox1;
    TLabeledEdit* LabeledEditX;
    TLabeledEdit* LabeledEditY;
    TLabeledEdit* LabeledEdit3;
    TLabeledEdit* LabeledEdit4;
    TButton* ButtonAccept;
    TButton* ButtonReject;
    TLabeledEdit* LabeledEdit1;
    TLabeledEdit* LabeledEdit2;
    TLabeledEdit* LabeledEditN;
    TLabel* LabelPosition;
    TLabel* LabelN;
    TLabel* LabelTimeHeatMap;
    TLabel* LabelTimeScene;
    TLabel* LabelVersion;
	TMainMenu *MainMenu1;
	TOpenTextFileDialog *OpenTextFileDialog1;
	TSaveTextFileDialog *SaveTextFileDialog1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
    void __fastcall Image1Click(TObject* Sender);
    void __fastcall Image1MouseDown(
        TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall ButtonRejectClick(TObject* Sender);
    void __fastcall ButtonAcceptClick(TObject* Sender);
    void __fastcall Button1Click(TObject* Sender);
    void __fastcall FormCreate(TObject* Sender);
    void __fastcall Button2Click(TObject* Sender);
    void __fastcall FormKeyDown(TObject* Sender, WORD &Key, TShiftState Shift);
    void __fastcall Image1MouseMove(
        TObject* Sender, TShiftState Shift, int X, int Y);
    void __fastcall ComboBox1Change(TObject* Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
  private: // User declarations
    menu_type selected_type = menu_type::NONE;
    Graphics::TBitmap* Virtual_Image = new Graphics::TBitmap();
    Graphics::TBitmap* Heat_map = new Graphics::TBitmap();

    TRect screen_rect;

    std::vector<TLabeledEdit*> menu_LE = { LabeledEdit1, LabeledEdit2,
        LabeledEdit3, LabeledEdit4 };

    vector<std::unique_ptr<VirtualOpticalDevice_t> > OpticalDevices;

    vector<bool> errors;
    vector<ray_t> rays_soursec;
	vector<vector<point_t> > points;
    vector<Nugol> vec_N;

	basicDrive_t drive = basicDrive_t(points, rays_soursec, errors, vec_N);
	void hide_menu();
	void create_optecal_dev_menu();
    void reDraw();
    void draw_ray_source(ray_t &ray_source);
    void show();

    void calculate_heat_map();

    //	std::vector<Ray_t>& Rays;
    //	UI_t(OpticalDevices, Rays);
  public: // User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1* Form1;
//---------------------------------------------------------------------------

#endif

