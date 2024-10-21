#include <d2d1_3.h>
#include "Animation.h"
#include <cmath>
#include <numbers>

using D2D1::RoundedRect;
using D2D1::RectF;
namespace {
    // ...
    // Interfejsy potrzebne do rysowania
    ID2D1SolidColorBrush* brush = nullptr;
    ID2D1LinearGradientBrush* brush_gradient = nullptr;

    D2D1_COLOR_F const clear_color = {
        .r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f };
    D2D1_COLOR_F const brush_color_1 = {
        .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f };
    D2D1_COLOR_F const brush_color_2 = {
        .r = 1.0f, .g = 0.25f, .b = 0.25f, .a = 1.0f };
    float width;
    int NR_width = 19;
    float height;
    int NR_height = 8;
    float height_single_left;
    float height_single_right;
}

void setupAnimation(ID2D1Factory7* d2d_factory, ID2D1HwndRenderTarget* d2d_render_target) {
    d2d_render_target->CreateSolidColorBrush(
        brush_color_1, &brush);

    ID2D1GradientStopCollection* pGradientStops = NULL;

    D2D1_GRADIENT_STOP gradientStops[2];
    gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::White, 1);
    gradientStops[0].position = 0.0f;
    gradientStops[1].color = brush_color_2, 1;
    gradientStops[1].position = 1.0f;
    // Create the ID2D1GradientStopCollection from a previously
    // declared array of D2D1_GRADIENT_STOP structs.
    d2d_render_target->CreateGradientStopCollection(
        gradientStops,
        2,
        D2D1_GAMMA_2_2,
        D2D1_EXTEND_MODE_CLAMP,
        &pGradientStops
    );

    d2d_render_target->CreateLinearGradientBrush(
        D2D1::LinearGradientBrushProperties(
            D2D1::Point2F(0, 0),
            D2D1::Point2F(150, 0)), 
        pGradientStops
        , &brush_gradient);
}

void drawAnimation(ID2D1HwndRenderTarget* d2d_render_target, HWND hwnd, int time) {
    d2d_render_target->Clear(clear_color);

    RECT rc;
    GetClientRect(hwnd, &rc);

    width = rc.right - rc.left;
    height = rc.bottom - rc.top;
    height_single_left = height / NR_height / 2;
    height_single_right = height_single_left * (1 + std::cos((time+180) * std::numbers::pi_v<float> / 180)/4);
    height_single_left *= (1 + std::cos(time * std::numbers::pi_v<float> / 180)/4);

    float start_point = width * std::sin(time * std::numbers::pi_v<float> / 180) / 2;
    float end_point = width * std::sin((time + 180) * std::numbers::pi_v<float> / 180) / 2;

    for (int i = 0; i < NR_width; i++) {
        float temp_height;
        if (i % 2) {
            temp_height = height_single_left;
        }
        else {
            temp_height = height_single_right;
        }
        if (i < NR_width / 2) {
            brush_gradient->SetEndPoint(D2D1::Point2F(end_point, 0));
            brush_gradient->SetStartPoint(D2D1::Point2F(start_point, 0));
        }
        else {
            if (end_point < width / 2) {
                brush_gradient->SetEndPoint(D2D1::Point2F(end_point + width, 0));
            }
            else {
                brush_gradient->SetEndPoint(D2D1::Point2F(end_point, 0));
            }
            if (start_point < 0) {
                brush_gradient->SetStartPoint(D2D1::Point2F(start_point + width, 0));
            }
            else {
                brush_gradient->SetStartPoint(D2D1::Point2F(start_point, 0));
            }
            
        }
        
        d2d_render_target->FillRoundedRectangle(
            RoundedRect(
                RectF(i * width / NR_width, height / 2 - temp_height, (i + 1) * width / NR_width, height / 2 + temp_height),
                10.0f, 50.0),
            brush_gradient);
        d2d_render_target->DrawRoundedRectangle(
            RoundedRect(
                RectF(i * width / NR_width, height / 2 - temp_height, (i + 1) * width / NR_width, height / 2 + temp_height),
                10.0f, 50.0),
            brush, 2.0f);
    }
}

void destroyAnimation() {
    if (brush) brush->Release();
}