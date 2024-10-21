#include <d2d1_3.h>
#include "Direct.h"
#include "Lines.h"
#include "Elipse.h"
#include "Animation.h"

// Deklaracje u¿ycia pomocniczych funkcji
using D2D1::RenderTargetProperties;
using D2D1::HwndRenderTargetProperties;
using D2D1::SizeU;

namespace {
    // Interfejsy potrzebne do zainicjowania Direct2D
    ID2D1Factory7* d2d_factory = nullptr;
    ID2D1HwndRenderTarget* d2d_render_target = nullptr;
    UINT_PTR timer;
    int time;
    void createRenderTarget(HWND hwnd) {
        RECT rc;
        GetClientRect(hwnd, &rc);
        // Utworzenie celu renderowania w oknie Windows
        d2d_factory->CreateHwndRenderTarget(
            RenderTargetProperties(),
            HwndRenderTargetProperties(
                hwnd,
                SizeU(
                    static_cast<UINT32>(rc.right) -
                    static_cast<UINT32>(rc.left),
                    static_cast<UINT32>(rc.bottom) -
                    static_cast<UINT32>(rc.top)
                )),
            &d2d_render_target);
    }
}
// ...
// Utworzenie fabryki Direct2D
void initD2(HWND hwnd) {
    D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d_factory);
    // ...
    createRenderTarget(hwnd);
    time = 0;
}

void paintD2(HWND hwnd) {
    if (!d2d_render_target) {
        createRenderTarget(hwnd);
    }

    //setupLines(d2d_factory, d2d_render_target);
    //setupElipse(d2d_factory, d2d_render_target);
    setupAnimation(d2d_factory, d2d_render_target);

    d2d_render_target->BeginDraw();

    //drawLines(d2d_render_target);
    //drawElipse(d2d_render_target);
    drawAnimation(d2d_render_target, hwnd, time);

    if (d2d_render_target->EndDraw() == D2DERR_RECREATE_TARGET) {
        if (d2d_render_target) d2d_render_target->Release();
    }
    //destroyLines();
    //destroyElipse();
    destroyAnimation();
}

void destroyD2() {
    // ...
    // Bezpieczne zwolnienie zasobów
    if (d2d_render_target) d2d_render_target->Release();
    if (d2d_factory) d2d_factory->Release();
}

void InitTimer(HWND hwnd) {
    timer = SetTimer(hwnd, NULL, NULL, NULL);
}

void OnTimer() {
    time++;
}

void ReleaseTimer(HWND hwnd) {
    KillTimer(hwnd, timer);
}