#include "visual_functios.h"

int pixels_per_meter = 70;
int VI_size = 3000;
int VI_centre = VI_size / 2;

TRect user_rect;
TColor ColorMin, ColorMax;

void DrawCoordinates(TCanvas* Canvas, int unitPixels)
{
    int width = Canvas->ClipRect.Width();
    int height = Canvas->ClipRect.Height();

    Canvas->Pen->Color = clBlack;
    Canvas->Pen->Width = 3;
    Canvas->MoveTo(width / 2, 0);
    Canvas->LineTo(width / 2, height);
    Canvas->MoveTo(0, height / 2);
    Canvas->LineTo(width, height / 2);

    Canvas->Pen->Color = clSilver;
    Canvas->Pen->Width = 1;
    Canvas->Brush->Style = bsClear;

    for (int i = width / 2 + unitPixels; i < width; i += unitPixels) {
        Canvas->MoveTo(i, 0);
        Canvas->LineTo(i, height);
        Canvas->TextOut(
            i + 2, height / 2 + 5, IntToStr((i - width / 2) / unitPixels));
    }
    for (int i = width / 2 - unitPixels; i > 0; i -= unitPixels) {
        Canvas->MoveTo(i, 0);
        Canvas->LineTo(i, height);
        Canvas->TextOut(
            i + 2, height / 2 + 5, IntToStr((i - width / 2) / unitPixels));
    }
    for (int i = height / 2 + unitPixels; i < height; i += unitPixels) {
        Canvas->MoveTo(0, i);
        Canvas->LineTo(width, i);
        Canvas->TextOut(
            width / 2 + 5, i + 2, IntToStr((height / 2 - i) / unitPixels));
    }
    for (int i = height / 2 - unitPixels; i > 0; i -= unitPixels) {
        Canvas->MoveTo(0, i);
        Canvas->LineTo(width, i);
        Canvas->TextOut(
            width / 2 + 5, i + 2, IntToStr((height / 2 - i) / unitPixels));
    }

    if (width / 2 > 0 && width / 2 < width && height / 2 > 0 &&
        height / 2 < height) {
        Canvas->TextOut(width / 2 + 5, height / 2 + 5, "0");
    }

    Canvas->Brush->Style = bsSolid;
}
point_t scrin_to_global_metrs(int x, int y)
{
    int g_x = x + user_rect.Left - VI_centre;
    int g_y = VI_centre - (y + user_rect.Top);
    return { g_x / (double)pixels_per_meter, g_y / (double)pixels_per_meter };
}

pair<int, int> to_picsels(double x, double y)
{
    return { x * pixels_per_meter + VI_centre,
        -y * pixels_per_meter + VI_centre };
}

void DrawAsterisk(
    TCanvas* Canvas, int centerX, int centerY, int size, int lineWidth)
{
    Canvas->Pen->Width = lineWidth;
    Canvas->Pen->Color = clWhite;

    int halfSize = size / 2;

    Canvas->MoveTo(centerX, centerY - halfSize);
    Canvas->LineTo(centerX, centerY + halfSize);

    Canvas->MoveTo(centerX - halfSize, centerY);
    Canvas->LineTo(centerX + halfSize, centerY);

    Canvas->MoveTo(centerX - halfSize, centerY - halfSize);
    Canvas->LineTo(centerX + halfSize, centerY + halfSize);

    Canvas->MoveTo(centerX + halfSize, centerY - halfSize);
    Canvas->LineTo(centerX - halfSize, centerY + halfSize);
}

TColor get_heat_color(double value)
{
    return (TColor)RGB(
        r_b + delta_r * value, g_b + delta_b * value, b_b + delta_b * value);
}

void update_grad_delt()
{
	r_b = GetRValue(ColorMin);
    g_b = GetGValue(ColorMin);
	b_b = GetBValue(ColorMin);

	delta_r =  GetRValue(ColorMax) - r_b;
	delta_g =  GetGValue(ColorMax) - g_b;
	delta_b =  GetBValue(ColorMax) - b_b;
}

