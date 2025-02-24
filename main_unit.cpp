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
            LabeledEdit1->Text =
                FloatToStr(rays_soursec.back().direction * RAD_TO_DEG);

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
            p3.y = (VI_centre - (Y + user_rect.Top)) / (double)pixels_per_meter;
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
        case 3: {
            Memo1->Visible = true;
            point prov;
            prov.x =
                (X + user_rect.Left - VI_centre) / (double)pixels_per_meter;
            prov.y =
                (VI_centre - (Y + user_rect.Top)) / (double)pixels_per_meter;

            for (int i = 0; i < vec_N.size(); i++) {
                if (vec_N[i].check(prov)) {
                    Memo1->Lines->Insert(
                        0, "Показатель преломления: " +
                               FloatToStrF(vec_N[i].get_prel(), ffFixed, 8, 3));
                    Memo1->Lines->Insert(
                        1, "Оптическая длина пути: " +
                               FloatToStrF(
                                   vec_N[i].get_op_dl_pt() * pixels_per_meter,
                                   ffFixed, 8, 3) +
                               " м");
                    Memo1->Lines->Insert(
                        2, "Угол входа (к нормали): " +
                               IntToStr(vec_N[i].get_ugl_vhoda()) + "°");
                    Memo1->Lines->Insert(
                        3, "Угол выхода (к нормали): " +
                               IntToStr(vec_N[i].get_ugl_vyhoda()) + "°");
                }
            }

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
bool need_to_redraw;
double new_step;
int new_pixels_per_meter;
int new_draw_precision;
int new_number_of_ray_points;
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
                StrToFloat(LabeledEdit1->Text * DEG_TO_RAD);
            break;
        case menu_type::Optical_dev: {
            double tempn;
            tempn = StrToFloat(LabeledEditN->Text);
            vector<segment> s;
            vec_N[now_dev].get_vector(s);
            seg.p1 = s.back().p2;
            seg.p2 = s.front().p1;
            s.push_back(seg);
            vec_N[now_dev].set_Nugol(s.size(), s, tempn);
            v.resize(0);
            //            reDraw();
        } break;
        case menu_type::field:
            need_to_redraw = false;

            new_pixels_per_meter = StrToInt(LabeledEdit2->Text);
            if (new_pixels_per_meter != pixels_per_meter) {
                pixels_per_meter = new_pixels_per_meter;
                need_to_redraw = true;
            }

            new_draw_precision = StrToInt(LabeledEdit3->Text);
            if (new_draw_precision != pixels_per_meter) {
                draw_precision = new_draw_precision;
                need_to_redraw = true;
            }

            new_number_of_ray_points = StrToInt(LabeledEdit4->Text);
            if (new_number_of_ray_points != number_of_ray_points) {
                number_of_ray_points = new_number_of_ray_points;
                need_to_redraw = true;
            }

            new_step = StrToFloat(LabeledEdit5->Text);
            if (new_step != step) {
                step = new_step;
                need_to_redraw = true;
            }

            formula = AnsiString(LabeledEdit1->Text).c_str();
            if (formula != drive.get_n_expression_str() &&
                drive.set_new_n_expression(formula))
                need_to_redraw = true;

            if (need_to_redraw) {
                calculate_heat_map();
                DrawCoordinates(Heat_map->Canvas, pixels_per_meter);
                reCalculate();
                //                reDraw();
            }
            break;
    }

    reDraw();
}
//---------------------------------------------------------------------------

void TForm1::reDraw()
{
    auto start = std::chrono::high_resolution_clock::now();

    Virtual_Image->Canvas->Pen->Color = clBlack;
    Virtual_Image->Canvas->Brush->Color = clBlack;
    TRect rect = Rect(0, 0, Virtual_Image->Width, Virtual_Image->Height);
    Virtual_Image->Canvas->FillRect(rect);
    //    for (int i = 0; i < OpticalDevices.size(); i++)
    //		OpticalDevices[i]->display(Virtual_Image->Canvas, pixels_per_meter);

    Virtual_Image->Assign(Heat_map);

    for (int i = 0; i < rays_soursec.size(); i++)
        draw_ray_source(rays_soursec[i]);

    for (int i = 0; i < vec_N.size(); i++) {
        Virtual_Image->Canvas->Pen->Color = clBlack;
        Virtual_Image->Canvas->Brush->Color = clBlack;
        Virtual_Image->Canvas->Pen->Width = 2;
        vector<segment> s;
        vec_N[i].get_vector(s);
        if (s.size() == 0)
            break;
        point p_nach;
        p_nach = s[0].p1;
        p_nach.x = p_nach.x * pixels_per_meter + VI_centre;
        p_nach.y = -p_nach.y * pixels_per_meter + VI_centre;
        Virtual_Image->Canvas->MoveTo(p_nach.x, p_nach.y);
        for (int i = 0; i < s.size(); i++) {
            p_nach = s[i].p2;
            p_nach.x = p_nach.x * pixels_per_meter + VI_centre;
            p_nach.y = -p_nach.y * pixels_per_meter + VI_centre;
            Virtual_Image->Canvas->LineTo(p_nach.x, p_nach.y);
        }
        if (fabs(s[0].p1.x - s.back().p2.x) <= 0.000001 &&
            fabs(s[0].p1.y - s.back().p2.y) <= 0.000001)
        {
            double value = vec_N[i].get_prel() - 1;
            value = max(0.0, min(1.0, value));

            Virtual_Image->Canvas->Brush->Color = get_heat_color(value);

            double x_ris, y_ris, x_ris2, y_ris2;
            x_ris = (s[0].p1.x + s[0].p2.x) / 2.;
            x_ris2 = (s[1].p1.x + s[1].p2.x) / 2.;
            y_ris = (s[0].p1.y + s[0].p2.y) / 2.;
            y_ris2 = (s[1].p1.y + s[1].p2.y) / 2.;
            x_ris = (x_ris + x_ris2) / 2.;
            y_ris = (y_ris + y_ris2) / 2.;
            x_ris = x_ris * pixels_per_meter + VI_centre;
            y_ris = -y_ris * pixels_per_meter + VI_centre;
            Virtual_Image->Canvas->FloodFill(x_ris, y_ris, clBlack, fsBorder);
            Virtual_Image->Canvas->Brush->Color = clBlack;
        }
    }

    Virtual_Image->Canvas->Pen->Color = clYellow;
    Virtual_Image->Canvas->Pen->Width = 5;
    for (int i = 0; i < points.size(); i++) {
        if (points[i].empty())
            continue;
        pair<int, int> t = to_picsels(points[i][0].x, points[i][0].y);
        Virtual_Image->Canvas->MoveTo(t.first, t.second);
        if (errors[i])
            Virtual_Image->Canvas->Pen->Color = ColorRayError;
        else
            Virtual_Image->Canvas->Pen->Color = ColorRay;

        int j = 0;
        for (int k = 0; k < necessary_index[i].size(); k += 2) {
            for (; j < necessary_index[i][k]; j += draw_precision) {
                t = to_picsels(points[i][j].x, points[i][j].y);
                Virtual_Image->Canvas->LineTo(t.first, t.second);
            }
            for (j = necessary_index[i][k]; j < necessary_index[i][k + 1]; j++)
            {
                t = to_picsels(points[i][j].x, points[i][j].y);
                Virtual_Image->Canvas->LineTo(t.first, t.second);
            }
        }
    }
    show();

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    LabelDrawScene->Caption =
        "Время отображения сцены: " + FloatToStr(elapsed.count());
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
    LabeledEdit5->Visible = false;
    ButtonAccept->Visible = false;
    ButtonReject->Visible = false;
    Memo1->Visible = false;
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

void TForm1::draw_ray_source(ray_t &ray_source)
{
    pair<int, int> p = to_picsels(ray_source.point.x, ray_source.point.y);
    DrawAsterisk(Virtual_Image->Canvas, p.first, p.second, 50, 5);
}

void __fastcall TForm1::Button1Click(TObject* Sender)
{
    reCalculate();
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

    LabelVersion->Caption += "\theat_map method: ";
#ifdef HEAT_MAP_POINTER_DRAW
    LabelVersion->Caption += "ScanLine[]";
#else
    LabelVersion->Caption += "Pixels[][]";
#endif
    LabelVersion->Caption += "\tPole size: " + IntToStr(VI_size);
    //    LabelVersion->Caption += "\t multitreading: ";
    //#ifdef multitreading
    //    LabelVersion->Caption += "TRUE";
    //#else
    //    LabelVersion->Caption += "FALSE";
    //#endif
    //
    //    LabelVersion->Caption += "\t GPU: ";
    //#ifdef GPU_HEAT_MAP
    //    LabelVersion->Caption += "TRUE";
    //#else
    //    LabelVersion->Caption += "FALSE";
    //#endif

    Virtual_Image->Width = VI_size;
    Virtual_Image->Height = VI_size;

    user_rect = Bounds(VI_centre - Image1->Width / 2,
        VI_centre - Image1->Height / 2, Image1->Width, Image1->Height);
    screen_rect = Bounds(0, 0, Image1->Width, Image1->Height);

    Heat_map->Width = VI_size;
    Heat_map->Height = VI_size;
    Heat_map->PixelFormat = pf24bit;

    ColorMin = (TColor)RGB(0, 0, 255);
    ColorMax = (TColor)RGB(255, 0, 0);
    ColorRay = clYellow;
    ColorRayError = clRed;
    update_grad_delt();

    calculate_heat_map();

    DrawCoordinates(Heat_map->Canvas, pixels_per_meter);
    reDraw();

    OpenTextFileDialog1->InitialDir = ExtractFilePath(ParamStr(0));
	SaveTextFileDialog1->InitialDir = OpenTextFileDialog1->InitialDir;

	this->ClientHeight = 500;
    this->ClientWidth = 1000;
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

    auto start = std::chrono::high_resolution_clock::now();

    for (int y = 0; y < VI_size; y++) {
#ifdef HEAT_MAP_POINTER_DRAW
        unsigned char* row = static_cast<unsigned char*>(Heat_map->ScanLine[y]);
#endif
        for (int x = 0; x < VI_size; x++) {
            double value =
                drive.n((x - VI_centre) / ppm, (VI_centre - y) / ppm) - 1;
            value = max(0.0, min(1.0, value));
            TColor color = get_heat_color(value);

#ifdef HEAT_MAP_POINTER_DRAW
            row[x * 3] = GetBValue(color); // Синий канал
            row[x * 3 + 1] = GetGValue(color); // Зеленый канал
            row[x * 3 + 2] = GetRValue(color); // Красный каналE
#else
            Heat_map->Canvas->Pixels[x][y] = get_heat_color(value);
#endif
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    LabelTimeHeatMap->Caption =
        "Время отрисовки тепловой карты: " + FloatToStr(elapsed.count());
}

void __fastcall TForm1::ComboBox1Change(TObject* Sender)
{
    hide_menu();
    switch (ComboBox1->ItemIndex) {
        case 0:
            selected_type = menu_type::field;
            LabeledEdit1->EditLabel->Caption = "функция n(x,y)";
            LabeledEdit1->Text =
                AnsiString(drive.get_n_expression_str().c_str());

            LabeledEdit2->EditLabel->Caption = "пиксели/метр";
            LabeledEdit2->Text = IntToStr(pixels_per_meter);

            LabeledEdit3->EditLabel->Caption = "Точность отрисовки: ";
            LabeledEdit3->Text = IntToStr(draw_precision);

            LabeledEdit4->EditLabel->Caption = "Кол-во точек в луче: ";
            LabeledEdit4->Text = IntToStr(number_of_ray_points);

            LabeledEdit5->EditLabel->Caption = "Шаг интегрирования (м): ";
            LabeledEdit5->Text = FloatToStr(step);

            LabeledEdit1->Visible = true;
            LabeledEdit2->Visible = true;
            LabeledEdit3->Visible = true;
            LabeledEdit4->Visible = true;
            LabeledEdit5->Visible = true;
            ButtonAccept->Visible = true;
            break;

        default:
            selected_device = -1;
            break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject* Sender)
{
    rays_soursec.clear();
	vec_N.clear();
	points.clear();

    user_rect = Bounds(VI_centre - Image1->Width / 2,
        VI_centre - Image1->Height / 2, Image1->Width, Image1->Height);
    screen_rect = Bounds(0, 0, Image1->Width, Image1->Height);

	//    string s = "1";
    //	drive.set_new_n_expression(s);
    vec_N.clear();

    reDraw();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject* Sender)
{
    if (SaveTextFileDialog1->Execute()) {
        String S = SaveTextFileDialog1->FileName;
        string s = AnsiString(S.c_str()).c_str();
        ofstream fout(s);
        fout << drive.get_n_expression_str() << endl;
        fout << "pixels_per_metr: " << pixels_per_meter << endl;
        fout << "ray_sources: " << rays_soursec.size() << endl;
        for (auto &i : rays_soursec)
            fout << i.point.x << ' ' << i.point.y << ' ' << i.direction << endl;
        fout << "n_ugolniki: " << vec_N.size() << endl;
        for (auto &i : vec_N) {
            vector<segment> vec;
            i.get_vector(vec);
            fout << "N: " << i.get_prel() << endl;
            fout << "segments: " << vec.size() << endl;
            for (auto &j : vec)
                fout << j.p1.x << ' ' << j.p1.y << ' ' << j.p2.x << ' '
                     << j.p2.y << endl;
        }
        fout.close();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject* Sender)
{
    if (OpenTextFileDialog1->Execute()) {
        String S = OpenTextFileDialog1->FileName;
        string s = AnsiString(S.c_str()).c_str();
        ifstream fin(s);

        string expr;
        fin >> expr;
        drive.set_new_n_expression(expr);

        fin.ignore(50, ' ');
        fin >> pixels_per_meter;
        fin.ignore(50, ' ');
        int rays_soursec_size = 0;
        fin >> rays_soursec_size;
        rays_soursec.resize(rays_soursec_size);
        for (auto &i : rays_soursec)
            fin >> i.point.x >> i.point.y >> i.direction;

        fin.ignore(50, ' ');
        int vec_N_size = 0;
        fin >> vec_N_size;
        vec_N.resize(vec_N_size);
        for (auto &i : vec_N) {
            fin.ignore(50, ' ');
            int act_n;
            fin >> act_n;
            fin.ignore(50, ' ');
            int lot_gran;
            fin >> lot_gran;
            vector<segment> vec(lot_gran);
            for (auto &j : vec)
                fin >> j.p1.x >> j.p1.y >> j.p2.x >> j.p2.y;
            i.set_Nugol(lot_gran, vec, act_n);
        }
        fin.close();

        calculate_heat_map();
        DrawCoordinates(Heat_map->Canvas, pixels_per_meter);
        reDraw();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N7Click(TObject* Sender)
{
    if (ColorDialog1->Execute())
        ColorMin = ColorDialog1->Color;
    update_grad_delt();

    calculate_heat_map();
    DrawCoordinates(Heat_map->Canvas, pixels_per_meter);
    reDraw();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N8Click(TObject* Sender)
{
    if (ColorDialog1->Execute())
        ColorMax = ColorDialog1->Color;
    update_grad_delt();

    calculate_heat_map();
    DrawCoordinates(Heat_map->Canvas, pixels_per_meter);
    reDraw();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N9Click(TObject* Sender)
{
    if (ColorDialog1->Execute())
        ColorRay = ColorDialog1->Color;
    reDraw();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N10Click(TObject* Sender)
{
    if (ColorDialog1->Execute())
        ColorRayError = ColorDialog1->Color;
    reDraw();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject* Sender)
{
    if (SaveTextFileDialog1->Execute()) {
        String S = SaveTextFileDialog1->FileName;
        string s = AnsiString(S.c_str()).c_str();
        ofstream fout(s);
        fout << rays_soursec.size() << endl;
        for (auto &i : points) {
            fout << i.size() << endl;
            for (auto &j : i)
                fout << j.x << ' ' << j.y << endl;
        }
        fout.close();
    }
}
//---------------------------------------------------------------------------
void TForm1::reCalculate()
{
    auto start = std::chrono::high_resolution_clock::now();

    drive.calculate();

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    LabelTimeScene->Caption =
        "Время расчёта сцены: " + FloatToStr(elapsed.count());
}

void __fastcall TForm1::FormResize(TObject* Sender)
{
    //	int w = GridPanel1->Left;
    //	int h = GridPanel1->Top;
    //
    //	user_rect = Bounds(VI_centre - w / 2,
    //		VI_centre - h / 2, w, h);
    //	screen_rect = Bounds(0, 0, w, h);
    user_rect = Bounds(VI_centre - Image1->Width / 2,
        VI_centre - Image1->Height / 2, Image1->Width, Image1->Height);
    screen_rect = Bounds(0, 0, Image1->Width, Image1->Height);

    show();

    //	ShowMessage(IntToStr(Image1->Width));
}
//---------------------------------------------------------------------------




