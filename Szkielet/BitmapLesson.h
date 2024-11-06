#pragma once
void setupBitmap(ID2D1Factory7* d2d_factory, ID2D1HwndRenderTarget* d2d_render_target);

void drawBitmap(ID2D1HwndRenderTarget* d2d_render_target, FLOAT angle);

void destroyBitmap();