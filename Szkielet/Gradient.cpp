#include <d2d1_3.h>
#include <cmath>
#include "Gradient.h"

// Deklaracje u¿ycia pomocniczych funkcji
using D2D1::ColorF;
using D2D1::LinearGradientBrushProperties;
using D2D1::Point2F;
using D2D1::RadialGradientBrushProperties;
using D2D1::Matrix3x2F;
using D2D1::RectF;
using D2D1::Ellipse;
using std::sin;

namespace {
    // ...
    // Interfejsy potrzebne do rysowania
    ID2D1SolidColorBrush* brush = nullptr;
    // - Pêdzel - gradient liniowy
    ID2D1LinearGradientBrush* lin_brush = nullptr;
    ID2D1GradientStopCollection* lin_stops = nullptr;
    UINT const NUM_LIN_STOPS = 3;
    D2D1_GRADIENT_STOP lin_stops_data[NUM_LIN_STOPS];
    // - Pêdzel - gradient promienisty
    ID2D1RadialGradientBrush* rad_brush = nullptr;
    ID2D1GradientStopCollection* rad_stops = nullptr;
    UINT const NUM_RAD_STOPS = 2;
    D2D1_GRADIENT_STOP rad_stops_data[NUM_RAD_STOPS];

    // - Macierz do po³¹czenia transformacji
    Matrix3x2F transformation;
    // ...
    // Sta³e kolorów
    D2D1_COLOR_F const clear_color = {
        .r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f };
    D2D1_COLOR_F const brush_color = {
        .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f };
    // Sta³e ustawienia geometrii
    D2D1_RECT_F const rectangle_dims = {
        .left = 10, .top = 10, .right = 310, .bottom = 210 };
    D2D1_POINT_2F const ellipse_center = { .x = 300, .y = 300 };
    D2D1_POINT_2F const ellipse_radii = { .x = 200, .y = 150 };
    FLOAT const brush_width = 2.0f;
}

void setupGradient(ID2D1Factory7* d2d_factory, ID2D1HwndRenderTarget* d2d_render_target) {
    // ...
    // Utworzenie pêdzla
    d2d_render_target->CreateSolidColorBrush(brush_color, &brush);
    // Ustawienia gradientu liniowego
    lin_stops_data[0] = {
        .position = 0.0f, .color = ColorF(ColorF::Yellow, 1.0f) };
    lin_stops_data[1] = {
        .position = 0.25f, .color = ColorF(ColorF::Red, 1.0f) };
    lin_stops_data[2] = {
        .position = 0.75f, .color = ColorF(ColorF::ForestGreen, 1.0f) };
    // Utworzenie gradientu liniowego
    d2d_render_target->CreateGradientStopCollection(
        lin_stops_data, NUM_LIN_STOPS, &lin_stops);
    if (lin_stops) {
        d2d_render_target->CreateLinearGradientBrush(
            LinearGradientBrushProperties(
                Point2F(20, 20), Point2F(200, 300)),
            lin_stops,
            &lin_brush);
    }
    // Ustawienia gradientu promienistego
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
                ellipse_center, Point2F(0, 0), 200, 150),
            rad_stops,
            &rad_brush);
    }
}
void drawGradient(ID2D1HwndRenderTarget* d2d_render_target, HWND hwnd, FLOAT angle) {
    // ...
    // Rysowanie klatki animacji
    d2d_render_target->Clear(clear_color);
    // Okreœlenie transformacji dla prostok¹ta
    transformation = Matrix3x2F::Skew(-15, 0, Point2F(100, 100));
    transformation.SetProduct(
        transformation,
        Matrix3x2F::Translation(200 * sin(angle / 50.0f) + 220, 50));
    d2d_render_target->SetTransform(transformation);
    // Narysowanie prostok¹ta
    d2d_render_target->FillRectangle(rectangle_dims, lin_brush);
    d2d_render_target->DrawRectangle(
        rectangle_dims, brush, brush_width);
    // Okreœlenie transformacji dla elipsy
    d2d_render_target->SetTransform(
        Matrix3x2F::Rotation(angle, Point2F(400, 300)));
    // Narysowanie elipsy
    d2d_render_target->FillEllipse(
        Ellipse(ellipse_center, ellipse_radii.x, ellipse_radii.y),
        rad_brush);
    d2d_render_target->DrawEllipse(
        Ellipse(ellipse_center, ellipse_radii.x, ellipse_radii.y),
        brush, brush_width);
}

void destroyGradient() {
    if (brush) brush->Release();
    if (lin_brush) lin_brush->Release();
    if (lin_stops) lin_stops->Release();
    if (rad_brush) rad_brush->Release();
    if (rad_stops) rad_stops->Release();
}