#pragma once

void setupWriting(ID2D1Factory7* d2d_factory, ID2D1HwndRenderTarget* d2d_render_target);

void drawWriting(ID2D1HwndRenderTarget* d2d_render_target, FLOAT angle, HWND hwnd);

void destroyWriting();