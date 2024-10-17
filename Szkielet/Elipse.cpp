#include <d2d1_3.h>
#include "Elipse.h"

using D2D1::Point2F;
using D2D1::RectF;
using D2D1::RoundedRect;
using D2D1::Ellipse;

namespace {
    // ...
    // Interfejsy potrzebne do rysowania
    ID2D1SolidColorBrush* brush = nullptr;
    // ...
    // Sta³e z kolorami
    D2D1_COLOR_F const clear_color = {
        .r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f };
    D2D1_COLOR_F const brush_color_1 = {
        .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f };
    D2D1_COLOR_F const brush_color_2 = {
        .r = 1.0f, .g = 0.25f, .b = 0.25f, .a = 1.0f };
    D2D1_COLOR_F const brush_color_3 = {
        .r = 0.75f, .g = 0.0f, .b = 0.0f, .a = 1.0f };
    D2D1_COLOR_F const brush_color_4 = {
        .r = 0.25f, .g = 1.0f, .b = 0.25f, .a = 0.875f };
    D2D1_COLOR_F const brush_color_5 = {
        .r = 0.0f, .g = 0.75f, .b = 0.0f, .a = 0.875f };
    D2D1_COLOR_F const brush_color_6 = {
        .r = 0.25f, .g = 0.25f, .b = 1.0f, .a = 0.5f };
    D2D1_COLOR_F const brush_color_7 = {
        .r = 0.0f, .g = 0.0f, .b = 0.75f, .a = 0.5f };
}

void setupElipse(ID2D1Factory7* d2d_factory, ID2D1HwndRenderTarget* d2d_render_target) {
    d2d_render_target->CreateSolidColorBrush(
        brush_color_1, &brush);
}

void drawElipse(ID2D1HwndRenderTarget* d2d_render_target) {
    d2d_render_target->Clear(clear_color);

    brush->SetColor(brush_color_2);
    d2d_render_target->FillRectangle(
        RectF(100.0f, 100.0f, 500.0f, 300.0f),
        brush);
    brush->SetColor(brush_color_3);
    d2d_render_target->DrawRectangle(
        RectF(100.0f, 100.0f, 500.0f, 300.0f),
        brush, 2.0f);

    brush->SetColor(brush_color_4);
    d2d_render_target->FillRoundedRectangle(
        RoundedRect(
            RectF(300.0f, 200.0f, 700.0f, 400.0f),
            40.0f, 100.0),
        brush);
    brush->SetColor(brush_color_5);
    d2d_render_target->DrawRoundedRectangle(
        RoundedRect(
            RectF(300.0f, 200.0f, 700.0f, 400.0f),
            40.0f, 100.0),
        brush, 2.0f);

    brush->SetColor(brush_color_6);
    d2d_render_target->FillEllipse(
        Ellipse(Point2F(600.0f, 350.0f), 150.0f, 200.0),
        brush);
    brush->SetColor(brush_color_7);
    d2d_render_target->DrawEllipse(
        Ellipse(Point2F(600.0f, 350.0f), 150.0f, 200.0),
        brush, 2.0f);
}

void destroyElipse() {
    if (brush) brush->Release();
}