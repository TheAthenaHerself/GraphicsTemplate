#pragma once

void setupLines(ID2D1Factory7* d2d_factory, ID2D1HwndRenderTarget* d2d_render_target);

void drawLines(ID2D1HwndRenderTarget* d2d_render_target);

void destroyLines();
