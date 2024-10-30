#include <d2d1_3.h>
#include <stdexcept>
#include "Direct.h"
#include "Lines.h"
#include "Elipse.h"
#include "Animation.h"
#include "Gradient.h"
#include "Path.h"
#include "Smoke.h"
#include "Writing.h"
using D2D1::RenderTargetProperties;
using D2D1::HwndRenderTargetProperties;
using D2D1::SizeU;

namespace {
    ID2D1Factory7* d2d_factory = nullptr;
    ID2D1HwndRenderTarget* d2d_render_target = nullptr;
    HRESULT error_code;
    UINT_PTR timer;
    int time;
    FLOAT angle = 0.0f;
    FLOAT time_path = 0.0f;
    FLOAT write_angle = 0.0f;
    void createRenderTarget(HWND hwnd) {
        RECT rc;
        GetClientRect(hwnd, &rc);
        error_code = d2d_factory->CreateHwndRenderTarget(
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
        if (error_code != S_OK) {
            throw std::runtime_error("Failed to create render target.");
        }
    }
}
void initD2(HWND hwnd) {
    error_code = D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d_factory);
    if (error_code != S_OK) {
        throw std::runtime_error("Failed to create D2D1 Factory.");
    }
    createRenderTarget(hwnd);
    time = 0;
}

void paintD2(HWND hwnd) {
    if (!d2d_render_target) {
        createRenderTarget(hwnd);
    }

    //setupLines(d2d_factory, d2d_render_target);
    //setupElipse(d2d_factory, d2d_render_target);
    //setupAnimation(d2d_factory, d2d_render_target);
    //setupGradient(d2d_factory, d2d_render_target);
    //setupPath(d2d_factory, d2d_render_target);
    //setupSmoke(d2d_factory, d2d_render_target);
    setupWriting(d2d_factory, d2d_render_target);

    d2d_render_target->BeginDraw();

    //drawLines(d2d_render_target);
    //drawElipse(d2d_render_target);
    //drawAnimation(d2d_render_target, hwnd, time);
    //drawGradient(d2d_render_target, hwnd, angle);
    //drawPath(d2d_render_target, hwnd, time_path);
    //drawSmoke(d2d_render_target, hwnd, time_path);
    drawWriting(d2d_render_target, write_angle, hwnd);

    if (d2d_render_target->EndDraw() == D2DERR_RECREATE_TARGET) {
        if (d2d_render_target) d2d_render_target->Release();
    }
    //destroyLines();
    //destroyElipse();
    //destroyAnimation();
    //destroyGradient();
    //destroyPath();
    //destroySmoke();
    destroyWriting();
}

void destroyD2() {
    if (d2d_render_target) d2d_render_target->Release();
    if (d2d_factory) d2d_factory->Release();
}

void InitTimer(HWND hwnd) {
    timer = SetTimer(hwnd, NULL, NULL, NULL);
}

void OnTimer() {
    time++;
    angle += 3.0f;
    time_path += 0.05f;
    write_angle += 0.5f;
}

void ReleaseTimer(HWND hwnd) {
    KillTimer(hwnd, timer);
}