#include <d2d1_3.h>
#include <cmath>
#include "Smoke.h"

using D2D1::ColorF;
using D2D1::Point2F;
using D2D1::BezierSegment;
using D2D1::Matrix3x2F;
using D2D1::RadialGradientBrushProperties;

namespace {
    ID2D1PathGeometry* path = nullptr;
    ID2D1GeometrySink* path_sink = nullptr;
    ID2D1SolidColorBrush* brush1 = nullptr;
    ID2D1SolidColorBrush* brush2 = nullptr;
    D2D1_COLOR_F const clear_color = {
        .r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f };
    D2D1_COLOR_F const brush1_color = {
        .r = 1.0f, .g = 0.5f, .b = 0.5f, .a = 1.0f };
    D2D1_COLOR_F const brush2_color = {
        .r = 1.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f };
    FLOAT const brush2_width = 3.0f;

    ID2D1RadialGradientBrush* rad_brush = nullptr;
    ID2D1GradientStopCollection* rad_stops = nullptr;
    UINT const NUM_RAD_STOPS = 2;
    D2D1_GRADIENT_STOP rad_stops_data[NUM_RAD_STOPS];
    D2D1_POINT_2F const ellipse_center = { .x = 800, .y = 500 };
    D2D1_POINT_2F const ellipse_radii = { .x = 700, .y = 400 };
}

void setupSmoke(ID2D1Factory7* d2d_factory, ID2D1HwndRenderTarget* d2d_render_target) {
    d2d_render_target->CreateSolidColorBrush(brush1_color, &brush1);
    d2d_render_target->CreateSolidColorBrush(brush2_color, &brush2);

    d2d_factory->CreatePathGeometry(&path);
    path->Open(&path_sink);
    path_sink->BeginFigure(Point2F(306.00f, 481.50f), D2D1_FIGURE_BEGIN_FILLED);
    path_sink->AddBezier(BezierSegment(
        Point2F(192.16f, 340.22f), Point2F(637.50f, 339.00f), Point2F(681.00f, 201.00f)));
    path_sink->AddBezier(BezierSegment(
        Point2F(730.33f, 6.61f), Point2F(1036.50f, 321.00f), Point2F(1188.00f, 309.00f)));
    path_sink->AddBezier(BezierSegment(
        Point2F(1303.86f, 302.07f), Point2F(1294.85f, 683.85f), Point2F(1066.50f, 697.50f)));
    path_sink->AddBezier(BezierSegment(
        Point2F(855.00f, 700.50f), Point2F(912.00f, 715.50f), Point2F(819.00f, 790.50f)));
    path_sink->AddBezier(BezierSegment(
        Point2F(672.07f, 903.35f), Point2F(504.49f, 757.18f), Point2F(306.00f, 481.50f)));
    path_sink->EndFigure(D2D1_FIGURE_END_CLOSED);
    path_sink->Close();

    rad_stops_data[0] = {
        .position = 0.0f, .color = ColorF(1.0f, 1.0f, 1.0f, 0.75f) };
    rad_stops_data[1] = {
        .position = 1.0f, .color = ColorF(0.25f, 0.25f, 1.0f, 0.75f) };
    // Utworzenie gradientu promienistego
    d2d_render_target->CreateGradientStopCollection(
        rad_stops_data, NUM_RAD_STOPS, &rad_stops);
    if (rad_stops) {
        d2d_render_target->CreateRadialGradientBrush(
            RadialGradientBrushProperties(
                ellipse_center, Point2F(0, 0), ellipse_radii.x, ellipse_radii.y),
            rad_stops,
            &rad_brush);
    }
}
void drawSmoke(ID2D1HwndRenderTarget* d2d_render_target, HWND hwnd, FLOAT time) {
    d2d_render_target->Clear(clear_color);
    d2d_render_target->FillGeometry(path, rad_brush);
    d2d_render_target->DrawGeometry(path, brush2, brush2_width);
}
void destroySmoke() {
    if (brush2) brush2->Release();
    if (path) path->Release();
    if (path_sink) path_sink->Release();
}