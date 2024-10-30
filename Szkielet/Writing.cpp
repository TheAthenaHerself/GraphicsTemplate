#include <d2d1_3.h>
#include <dwrite_3.h>	// i do³¹czyæ dwrite.lib do projektu
#include <cmath>

#include "Writing.h"

using D2D1::Point2F;
using D2D1::Matrix3x2F;
using D2D1::RectF;
using std::sin;


namespace {
    IDWriteFactory* write_factory = nullptr;
    IDWriteTextFormat* text_format = nullptr;
    ID2D1SolidColorBrush* brush = nullptr;
    // ...
    // Sta³e kolorów
    D2D1_COLOR_F const clear_color = {
        .r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f };
    D2D1_COLOR_F const brush_color = {
        .r = 0.75f, .g = 0.0f, .b = 0.0f, .a = 1.0f };
    D2D1_COLOR_F const shadow_color = {
        .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 0.125f };
    // ...
    // Dane napisu w UNICODE
    WCHAR const NAPIS[] = L"Czeœæ Œwiecie";

}

void setupWriting(ID2D1Factory7* d2d_factory, ID2D1HwndRenderTarget* d2d_render_target) {
    d2d_render_target->CreateSolidColorBrush(brush_color, &brush);
    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&write_factory)
    );
    // ...
    // Utworzenie formatu napisu DirectWrite
    write_factory->CreateTextFormat(
        L"Times New Roman", nullptr,
        DWRITE_FONT_WEIGHT_BOLD,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        150.0f, L"en-us", &text_format);
}

void drawWriting(ID2D1HwndRenderTarget* d2d_render_target, FLOAT angle, HWND hwnd) {
    d2d_render_target->Clear(clear_color);

    RECT rc;
    GetClientRect(hwnd, &rc);

    d2d_render_target->SetTransform(
        Matrix3x2F::Rotation(-angle, Point2F(500, 300)));

    brush->SetColor(shadow_color);
    d2d_render_target->DrawText(
        NAPIS, sizeof(NAPIS) / sizeof(NAPIS[0]),
        text_format,
        RectF(158.0f, 88.0f,
            static_cast<FLOAT>(rc.right),
            static_cast<FLOAT>(rc.bottom)),
        brush);
    brush->SetColor(brush_color);
    d2d_render_target->DrawText(
        NAPIS, sizeof(NAPIS) / sizeof(NAPIS[0]),
        text_format,
        RectF(150.0f, 80.0f,
            static_cast<FLOAT>(rc.right),
            static_cast<FLOAT>(rc.bottom)),
        brush);
}

void destroyWriting() {
    if (text_format) text_format->Release();
    if (write_factory) write_factory->Release();
    if (brush) brush->Release();
}