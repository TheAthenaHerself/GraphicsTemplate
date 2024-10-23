#pragma once

void setupSmoke(ID2D1Factory7* d2d_factory, ID2D1HwndRenderTarget* d2d_render_target);
void drawSmoke(ID2D1HwndRenderTarget* d2d_render_target, HWND hwnd, FLOAT time);
void destroySmoke();