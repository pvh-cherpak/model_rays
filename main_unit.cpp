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
int pixels_per_meter = 50;
int selected_device = -1;
int selected_type = 0;

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
            selected_type = 0;
            rays_soursec.push_back({ scrin_to_global_metrs(X, Y), 0 });

            ButtonAccept->Visible = true;
            ButtonReject->Visible = true;
            LabeledEditX->Visible = true;
            LabeledEditY->Visible = true;
            LabeledEdit1->Visible = true;

            LabeledEditX->Text = FloatToStr(rays_soursec.back().point.x);
            LabeledEditY->Text = FloatToStr(rays_soursec.back().point.y);
            LabeledEdit1->Text = FloatToStr(rays_soursec.back().direction);

            LabeledEdit1->EditLabel->Caption = "Derection";
            break;
        case 2:
            //            is_new_device = true;
            //            selected_device = OpticalDevices.size();
            //            selected_type = 1;
            //            OpticalDevices.push_back(std::unique_ptr<VirtualOpticalDevice_t>(
            //                new ElipseOpticalDevice_t((float)X / pixels_per_meter,
            //                    -(float)Y / pixels_per_meter)));
            break;
        case 0:
            break;
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
    if (selected_type) {
        OpticalDevices[selected_device]->parametrs[0] =
            StrToFloat(LabeledEditX->Text);
        OpticalDevices[selected_device]->parametrs[1] =
            StrToFloat(LabeledEditY->Text);
        OpticalDevices[selected_device]->parametrs[2] =
            StrToFloat(LabeledEditN->Text);
        for (int i = 0;
             i < OpticalDevices[selected_device]->parameter_names.size(); i++)
        {
            OpticalDevices[selected_device]->parametrs[i + 3] =
                StrToFloat(menu_LE[i]->Text);
        }
    } else {
        rays_soursec[selected_device].point.x = StrToFloat(LabeledEditX->Text);
        rays_soursec[selected_device].point.y = StrToFloat(LabeledEditY->Text);
        rays_soursec[selected_device].direction =
            StrToFloat(LabeledEdit1->Text);
    }
    //       hide_menu();
    //       selected_device = -1;
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
	drive.calculate();
	reDraw();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject* Sender)
{
	Virtual_Image->Width = VI_size;
    Virtual_Image->Height = VI_size;
    user_rect = Bounds(VI_centre - Image1->Width, VI_centre - Image1->Height,
        Image1->Width, Image1->Height);
    screen_rect = Bounds(0, 0, Image1->Width, Image1->Height);

    Heat_map->Width = VI_size;
    Heat_map->Height = VI_size;
    Heat_map->Canvas->Brush->Color = (TColor)RGB(0, 0, 255);
    TRect rect = Rect(0, 0, Heat_map->Width, Heat_map->Height);
    Heat_map->Canvas->FillRect(rect);

	double ppm = pixels_per_meter;

	vector <vector<double>> mass (VI_size, vector<double> (VI_size));
//	#pragma omp parallel for
//	for(int i = 0; i <  VI_size; i++)
//		for (int j = 0; j <  VI_size; j++)
//				mass[i][j] =

	for (int y = VI_size / 4; y < VI_size / 2 + VI_size / 4; y++) {
        for (int x = VI_size / 4; x < VI_size; x++) {
			double value = drive.n((x - VI_centre) / ppm,
								(VI_centre - y) / ppm) - 1;
            value = std::max(
                0.0, std::min(1.0, value)); // огрничьте значение между 0 и 1

            // Определите цвет (например, градиент от синего к красному)
            BYTE red = static_cast<BYTE>(255 * value);
            BYTE green = 0;
            BYTE blue = static_cast<BYTE>(255 * (1 - value));

            // Закрасьте пиксель на Bitmap
            TColor color = (TColor)RGB(red, green, blue);
            Heat_map->Canvas->Pixels[x][y] = color;
        }
    }
	DrawCoordinates(Heat_map->Canvas, pixels_per_meter);
                   	reDraw();
}
//---------------------------------------------------------------------------

point_t TForm1::scrin_to_global_metrs(int x, int y)
{
    int g_x = x + user_rect.Left - VI_centre;
    int g_y = VI_centre - (y + user_rect.Top);
    return { g_x / (double)pixels_per_meter, g_y / (double)pixels_per_meter };
}

pair<int, int> TForm1::to_picsels(double x, double y)
{
    return { x * pixels_per_meter + VI_centre,
        -y * pixels_per_meter + VI_centre };
}

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
    Label1->Caption = "X: " + FloatToStr(t.x) + "\n Y: " + FloatToStr(t.y);
}
//---------------------------------------------------------------------------

void TForm1::DrawCoordinates(TCanvas* Canvas, int unitPixels)
{
    int width = Canvas->ClipRect.Width();
    int height = Canvas->ClipRect.Height();

    // Рисуем оси координат
    Canvas->Pen->Color = clBlack;
    Canvas->Pen->Width = 3; // Устанавливаем ширину осей
    Canvas->MoveTo(width / 2, 0);
    Canvas->LineTo(width / 2, height);
    Canvas->MoveTo(0, height / 2);
    Canvas->LineTo(width, height / 2);

    // Рисуем сетку и подписи
    Canvas->Pen->Color = clSilver;
    Canvas->Pen->Width = 1; // Устанавливаем ширину линий сетки
    Canvas->Brush->Style = bsClear; // Прозрачный фон для текста

    for (int i = width / 2 + unitPixels; i < width; i += unitPixels) {
        Canvas->MoveTo(i, 0);
        Canvas->LineTo(i, height);
        Canvas->TextOut(i + 2, height / 2 + 5,
            IntToStr((i - width / 2) / unitPixels)); // Смещаем текст вправо
    }
    for (int i = width / 2 - unitPixels; i > 0; i -= unitPixels) {
        Canvas->MoveTo(i, 0);
        Canvas->LineTo(i, height);
        Canvas->TextOut(i + 2, height / 2 + 5,
            IntToStr((i - width / 2) / unitPixels)); // Смещаем текст вправо
    }
    for (int i = height / 2 + unitPixels; i < height; i += unitPixels) {
        Canvas->MoveTo(0, i);
        Canvas->LineTo(width, i);
        Canvas->TextOut(width / 2 + 5, i + 2,
            IntToStr((height / 2 - i) / unitPixels)); // Смещаем текст вправо
    }
    for (int i = height / 2 - unitPixels; i > 0; i -= unitPixels) {
        Canvas->MoveTo(0, i);
        Canvas->LineTo(width, i);
        Canvas->TextOut(width / 2 + 5, i + 2,
            IntToStr((height / 2 - i) / unitPixels)); // Смещаем текст вправо
    }

    // Отрисовываем ноль только в центре
    if (width / 2 > 0 && width / 2 < width && height / 2 > 0 &&
        height / 2 < height) {
        Canvas->TextOut(width / 2 + 5, height / 2 + 5, "0");
    }

    // Восстанавливаем кисть
    Canvas->Brush->Style = bsSolid;
}

