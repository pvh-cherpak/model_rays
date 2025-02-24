#pragma once

#include "data_types.h"
#include "main_unit.h"

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>

using namespace std;

extern TRect user_rect;
extern int pixels_per_meter;
extern int VI_size;
extern int VI_centre;
extern TColor ColorMin, ColorMax;
static int r_b, g_b, b_b;
static int delta_r, delta_g, delta_b;

void update_grad_delt();
TColor get_heat_color(double value);

void DrawCoordinates(TCanvas* Canvas, int unitPixels);
point_t scrin_to_global_metrs(int x, int y);
pair<int, int> to_picsels(double x, double y);
void DrawAsterisk(
    TCanvas* Canvas, int centerX, int centerY, int size, int lineWidth);

