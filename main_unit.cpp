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
int selected_device = -1;

vector<point> v;
vector<segment> v_seg;
segment seg;
ray r;
point p3;
pryam pr;
int now_dev = -1;
double prel;

//------------------------------------------------------------------------------------

void __fastcall TForm1::Image1Click(TObject* Sender)
{
	reDraw();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseDown(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    bool is_new_device = false;
    switch (ComboBox1->ItemIndex) {
        case 1:
            selected_device = rays_soursec.size();
            selected_type = menu_type::ray_source;
            rays_soursec.push_back({ scrin_to_global_metrs(X, Y), 0 });

			ButtonAccept->Visible = true;
			ButtonReject->Visible = true;
			LabeledEditX->Visible = true;
            LabeledEditY->Visible = true;
            LabeledEdit1->Visible = true;

            LabeledEditX->Text = FloatToStr(rays_soursec.back().point.x);
            LabeledEditY->Text = FloatToStr(rays_soursec.back().point.y);
			LabeledEdit1->Text = FloatToStr(rays_soursec.back().direction);

			LabeledEdit1->EditLabel->Caption = "Direction";
            break;
        case 2: {
			//is_new_device = true;
			//selected_device = OpticalDevices.size();
			selected_type = menu_type::Optical_dev;
            ButtonAccept->Visible = true;
			ButtonReject->Visible = true;
            LabeledEditN->Visible = true;
			p3.x = (X + user_rect.Left - VI_centre) / (double)pixels_per_meter;
			p3.y = (VI_centre - (Y + user_rect.Top))/ (double)pixels_per_meter;
			if (v.size() != 0) {
				seg.p1 = v.back();
				seg.p2 = p3;
				v_seg.push_back(seg);
				vec_N[now_dev].set_Nugol(v_seg.size(), v_seg, 1);

			} else {
				v_seg.resize(0);
				now_dev++;
                Nugol N1(v_seg.size(), v_seg, 1);
				vec_N.push_back(N1);
            }
			v.push_back(p3);
            reDraw();
            break;
        }
        default:;
    }
	if (is_new_device) {
		create_optecal_dev_menu();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonRejectClick(TObject* Sender)
{
    hide_menu();
    selected_device = -1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonAcceptClick(TObject* Sender)
{
	string formula;
	switch (selected_type) {
        case menu_type::ray_source:
            rays_soursec[selected_device].point.x =
                StrToFloat(LabeledEditX->Text);
            rays_soursec[selected_device].point.y =
                StrToFloat(LabeledEditY->Text);
            rays_soursec[selected_device].direction =
                StrToFloat(LabeledEdit1->Text);
            break;
		case menu_type::field:
		formula = AnsiString(LabeledEdit1->Text).c_str();
			if (drive.set_new_n_expression(formula)) {
				pixels_per_meter = StrToInt(LabeledEdit2->Text);
				calculate_heat_map();
                DrawCoordinates(Heat_map->Canvas, pixels_per_meter);
                reDraw();
            }
			break;
		case menu_type::Optical_dev:
			double tempn;
			tempn = StrToFloat(LabeledEditN->Text);
            vector < segment > s;
			vec_N[now_dev].get_vector(s);
			seg.p1 = s.back().p2;
			seg.p2= s.front().p1;
			s.push_back(seg);
			vec_N[now_dev].set_Nugol(s.size(), s, tempn);
			v.resize(0);
            reDraw();
			break;
    }
    //    if (selected_type) {
    //        OpticalDevices[selected_device]->parametrs[0] =
    //            StrToFloat(LabeledEditX->Text);
    //        OpticalDevices[selected_device]->parametrs[1] =
    //            StrToFloat(LabeledEditY->Text);
    //        OpticalDevices[selected_device]->parametrs[2] =
    //            StrToFloat(LabeledEditN->Text);
    //        for (int i = 0;
    //             i < OpticalDevices[selected_device]->parameter_names.size(); i++)
    //        {
    //            OpticalDevices[selected_device]->parametrs[i + 3] =
    //                StrToFloat(menu_LE[i]->Text);
    //        }
    //    }
    //    hide_menu();
    //    selected_device = -1;
    reDraw();
}
//---------------------------------------------------------------------------

void TForm1::reDraw()
{
	Virtual_Image->Canvas->Pen->Color = clBlack;
    Virtual_Image->Canvas->Brush->Color = clBlack;
	TRect rect = Rect(0, 0, Virtual_Image->Width, Virtual_Image->Height);
    Virtual_Image->Canvas->FillRect(rect);
    //    for (int i = 0; i < OpticalDevices.size(); i++)
    //		OpticalDevices[i]->display(Virtual_Image->Canvas, pixels_per_meter);

    Virtual_Image->Assign(Heat_map);

    for (int i = 0; i < rays_soursec.size(); i++)
		draw_ray_source(rays_soursec[i]);

	for(int i = 0; i < vec_N.size(); i++)
		{
		Virtual_Image->Canvas->Pen->Color = clBlack;
		Virtual_Image->Canvas->Brush->Color = clBlack;
		Virtual_Image->Canvas->Pen->Width = 2;
			vector < segment > s;
			vec_N[i].get_vector(s);
			if(s.size() == 0)
				break;
			point p_nach;
			p_nach = s[0].p1;
			p_nach.x = p_nach.x * pixels_per_meter + VI_centre;
			p_nach.y = -p_nach.y * pixels_per_meter + VI_centre;
			Virtual_Image->Canvas->MoveTo(p_nach.x, p_nach.y);
			for(int i = 0; i < s.size(); i++)
			{
			p_nach = s[i].p2;
			p_nach.x = p_nach.x * pixels_per_meter + VI_centre;
			p_nach.y = -p_nach.y * pixels_per_meter + VI_centre;
			Virtual_Image->Canvas->LineTo(p_nach.x, p_nach.y);
			}
			if(fabs(s[0].p1.x - s.back().p2.x) <= 0.000001 && fabs(s[0].p1.y - s.back().p2.y) <= 0.000001)
			{
				double value = vec_N[i].get_prel() - 1;
				value = max(0.0, min(1.0, value)); // огрничьте значение между 0 и 1

				// Определите цвет (например, градиент от синего к красному)
				BYTE red = static_cast<BYTE>(255 * value);
				BYTE green = 0;
				BYTE blue = static_cast<BYTE>(255 * (1 - value));

				// Закрасьте пиксель на Bitmap
				TColor color = (TColor)RGB(red, green, blue);
				Virtual_Image->Canvas->Brush->Color= color;
				double x_ris, y_ris;
				x_ris = (s[0].p1.x + s[1].p2.x) / 2.;
				y_ris = (s[0].p1.y + s[1].p2.y) / 2.;
				x_ris = x_ris * pixels_per_meter + VI_centre;
				y_ris = -y_ris * pixels_per_meter + VI_centre;
				Virtual_Image->Canvas->FloodFill(x_ris, y_ris, clBlack, fsBorder);
				Virtual_Image->Canvas->Brush->Color = clBlack;
			}

        }

    Virtual_Image->Canvas->Pen->Color = clYellow;
    Virtual_Image->Canvas->Pen->Width = 5;
    for (int i = 0; i < points.size(); i++) {
        pair<int, int> t = to_picsels(points[i][0].x, points[i][0].y);
        Virtual_Image->Canvas->MoveTo(t.first, t.second);
        if (errors[i])
            Virtual_Image->Canvas->Pen->Color = clRed;
        else
            Virtual_Image->Canvas->Pen->Color = clYellow;
        for (int j = 1; j < points[i].size(); j++) {
            t = to_picsels(points[i][j].x, points[i][j].y);
            Virtual_Image->Canvas->LineTo(t.first, t.second);
        }
    }
    show();
}

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

void TForm1::create_optecal_dev_menu()
{
    ButtonAccept->Visible = true;
    ButtonReject->Visible = true;
    LabeledEditX->Visible = true;
    LabeledEditY->Visible = true;
    LabeledEditN->Visible = true;

    LabeledEditX->Text =
        FloatToStr(OpticalDevices[selected_device]->parametrs[0]);
    LabeledEditY->Text =
        FloatToStr(OpticalDevices[selected_device]->parametrs[1]);
    LabeledEditN->Text =
        FloatToStr(OpticalDevices[selected_device]->parametrs[2]);
    for (int i = 0; i < OpticalDevices[selected_device]->parameter_names.size();
         i++)
    {
        menu_LE[i]->Visible = true;
        menu_LE[i]->EditLabel->Caption =
            OpticalDevices[selected_device]->parameter_names[i];
        menu_LE[i]->Text =
            FloatToStr(OpticalDevices[selected_device]->parametrs[i + 3]);
    }
}

// Функция для рисования символа '*'
void DrawAsterisk(
    TCanvas* Canvas, int centerX, int centerY, int size, int lineWidth)
{
    // Устанавливаем толщину линий
    Canvas->Pen->Width = lineWidth;
    Canvas->Pen->Color = clWhite; // Цвет линии (черный)

    int halfSize = size / 2;

    // Вертикальная линия
    Canvas->MoveTo(centerX, centerY - halfSize);
    Canvas->LineTo(centerX, centerY + halfSize);

    // Горизонтальная линия
    Canvas->MoveTo(centerX - halfSize, centerY);
    Canvas->LineTo(centerX + halfSize, centerY);

    // Диагональ (левая верхняя -> правая нижняя)
    Canvas->MoveTo(centerX - halfSize, centerY - halfSize);
    Canvas->LineTo(centerX + halfSize, centerY + halfSize);

    // Диагональ (правая верхняя -> левая нижняя)
    Canvas->MoveTo(centerX + halfSize, centerY - halfSize);
    Canvas->LineTo(centerX - halfSize, centerY + halfSize);
}

void TForm1::draw_ray_source(ray_t &ray_source)
{
    pair<int, int> p = to_picsels(ray_source.point.x, ray_source.point.y);
    DrawAsterisk(Virtual_Image->Canvas, p.first, p.second, 50, 5);
}

void __fastcall TForm1::Button1Click(TObject* Sender)
{
    // Захватываем текущее время перед выполнением функции
    auto start = std::chrono::high_resolution_clock::now();

    drive.calculate();

    // Захватываем текущее время после выполнения функции
    auto end = std::chrono::high_resolution_clock::now();

    // Вычисляем разницу во времени
    std::chrono::duration<double> elapsed = end - start;

    LabelTimeScene->Caption =
        "Время расчёта сцены: " + FloatToStr(elapsed.count());

    reDraw();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject* Sender)
{
	LabelVersion->Caption = "math: ";
#ifdef EXPRTK
    LabelVersion->Caption += "exprtk";
#elif defined FPARSER
    LabelVersion->Caption += "fparser";
#else
    LabelVersion->Caption += "compiled";
#endif

    LabelVersion->Caption += "\t multitreading: ";
#ifdef multitreading
    LabelVersion->Caption += "TRUE";
#else
	LabelVersion->Caption += "FALSE";
#endif

    LabelVersion->Caption += "\t GPU: ";
#ifdef GPU_HEAT_MAP
    LabelVersion->Caption += "TRUE";
#else
    LabelVersion->Caption += "FALSE";
#endif

    Virtual_Image->Width = VI_size;
    Virtual_Image->Height = VI_size;
    user_rect = Bounds(VI_centre - Image1->Width, VI_centre - Image1->Height,
        Image1->Width, Image1->Height);
    screen_rect = Bounds(0, 0, Image1->Width, Image1->Height);

    Heat_map->Width = VI_size;
	Heat_map->Height = VI_size;

    //    calculate_heat_map();

	DrawCoordinates(Heat_map->Canvas, pixels_per_meter);
    reDraw();
}
//---------------------------------------------------------------------------

void TForm1::show()
{
    Image1->Canvas->CopyRect(screen_rect, Virtual_Image->Canvas, user_rect);
}
void __fastcall TForm1::Button2Click(TObject* Sender)
{
    OffsetRect(&user_rect, 100, 0);
    show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(
    TObject* Sender, WORD &Key, TShiftState Shift)
{
    switch (Key) {
        case VK_LEFT:
            OffsetRect(&user_rect, -10, 0);
            show();
            break;
        case VK_RIGHT:
            OffsetRect(&user_rect, 10, 0);
            show();
            break;
        case VK_UP:
            OffsetRect(&user_rect, 0, -10);
            show();
            break;
        case VK_DOWN:
            OffsetRect(&user_rect, 0, 10);
            show();
            break;
    }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseMove(
    TObject* Sender, TShiftState Shift, int X, int Y)
{
    point_t t = scrin_to_global_metrs(X, Y);
    LabelPosition->Caption =
        "X: " + FloatToStr(t.x) + "\n Y: " + FloatToStr(t.y);
    LabelN->Caption = "N: " + FloatToStr(drive.n(t.x, t.y));
}
//---------------------------------------------------------------------------

void TForm1::calculate_heat_map()
{
    double ppm = pixels_per_meter;

    // Захватываем текущее время перед выполнением функции
    auto start = std::chrono::high_resolution_clock::now();

    for (int y = VI_size / 4; y < VI_size / 2 + VI_size / 4; y++) {
        for (int x = VI_size / 4; x < VI_size; x++) {
            double value =
				drive.n((x - VI_centre) / ppm, (VI_centre - y) / ppm) - 1;
			value = max(0.0, min(1.0, value)); // огрничьте значение между 0 и 1

			// Определите цвет (например, градиент от синего к красному)
			BYTE red = static_cast<BYTE>(255 * value);
			BYTE green = 0;
			BYTE blue = static_cast<BYTE>(255 * (1 - value));

			// Закрасьте пиксель на Bitmap
			TColor color = (TColor)RGB(red, green, blue);
			Heat_map->Canvas->Pixels[x][y] = color;
        }
    }

    // Захватываем текущее время после выполнения функции
    auto end = std::chrono::high_resolution_clock::now();

    // Вычисляем разницу во времени
    std::chrono::duration<double> elapsed = end - start;

    LabelTimeHeatMap->Caption =
        "Время расчёта тепловой карты: " + FloatToStr(elapsed.count());
}

void __fastcall TForm1::ComboBox1Change(TObject* Sender)
{
	hide_menu();
	switch (ComboBox1->ItemIndex) {
		case 0:
            selected_type = menu_type::field;
			LabeledEdit1->EditLabel->Caption = "формула n(x,y)";
			LabeledEdit1->Text =
				AnsiString(drive.get_n_expression_str().c_str());

			LabeledEdit2->EditLabel->Caption = "пиксели/метр";
			LabeledEdit2->Text = IntToStr(pixels_per_meter);

			LabeledEdit1->Visible = true;
            LabeledEdit2->Visible = true;
            ButtonAccept->Visible = true;
			break;

		default:
			selected_device = -1;
			break;
    }
}
//---------------------------------------------------------------------------

