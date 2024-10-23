#include <d2d1_3.h>
#include <cmath>
#include "Path.h"

using D2D1::ColorF;
using D2D1::Point2F;
using D2D1::BezierSegment;
using D2D1::QuadraticBezierSegment;
using D2D1::Matrix3x2F;
using std::sin;

namespace {
    // ...
// Interfejsy potrzebne do rysowania
    ID2D1SolidColorBrush* brush1 = nullptr;
    ID2D1SolidColorBrush* brush2 = nullptr;
    // - Interfejsy do obs³ugi œcie¿ki
    ID2D1PathGeometry* path = nullptr;
    ID2D1GeometrySink* path_sink = nullptr;
    // ...
    // Sta³e kolorów
    D2D1_COLOR_F const clear_color = {
        .r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f };
    D2D1_COLOR_F const brush1_color = {
        .r = 1.0f, .g = 0.5f, .b = 0.5f, .a = 1.0f };
    D2D1_COLOR_F const brush2_color = {
        .r = 1.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f };
    // ...
    // Sta³e ustawienia geometrii
    FLOAT const brush2_width = 3.0f;

}

void setupPath(ID2D1Factory7* d2d_factory, ID2D1HwndRenderTarget* d2d_render_target) {
    d2d_render_target->CreateSolidColorBrush(brush1_color, &brush1);
    d2d_render_target->CreateSolidColorBrush(brush2_color, &brush2);
    // Utworzenie i zbudowanie geometrii œcie¿ki
    d2d_factory->CreatePathGeometry(&path);
    path->Open(&path_sink);
    path_sink->BeginFigure(Point2F(200, 300), D2D1_FIGURE_BEGIN_FILLED);
    path_sink->AddBezier(BezierSegment(
        Point2F(100, 150), Point2F(500, 150), Point2F(400, 300)));
    path_sink->AddQuadraticBezier(QuadraticBezierSegment(
        Point2F(300, 450), Point2F(200, 300)));
    path_sink->EndFigure(D2D1_FIGURE_END_OPEN);
    path_sink->Close();

}
void drawPath(ID2D1HwndRenderTarget* d2d_render_target, HWND hwnd, FLOAT time) {
    FLOAT angle = 45.0f * std::sin(time);
    d2d_render_target->Clear(clear_color);
    d2d_render_target->SetTransform(
        Matrix3x2F::Rotation(angle, Point2F(300, 300)));
    d2d_render_target->FillGeometry(path, brush1);
    d2d_render_target->DrawGeometry(path, brush2, brush2_width);
}
void destroyPath() {
    if (brush1) brush1->Release();
    if (brush2) brush2->Release();
    if (path) path->Release();
    if (path_sink) path_sink->Release();
}