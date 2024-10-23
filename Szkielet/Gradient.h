#pragma once

void setupGradient(ID2D1Factory7* d2d_factory, ID2D1HwndRenderTarget* d2d_render_target);
void drawGradient(ID2D1HwndRenderTarget* d2d_render_target, HWND hwnd, FLOAT angle);
void destroyGradient();