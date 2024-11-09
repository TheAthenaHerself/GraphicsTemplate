#include <d2d1_3.h>
#include <cmath>
#include <array>
#include <wincodec.h>
#include "BitmapLesson.h"

using D2D1::BitmapProperties;
using D2D1::PixelFormat;
using D2D1::Point2F;
using D2D1::RectF;
using D2D1::Matrix3x2F;
using std::sin;
using std::array;
using D2D1::SizeU;

namespace {
    ID2D1SolidColorBrush* brush = nullptr;
    IWICImagingFactory* pIWICFactory = nullptr;
    D2D1_COLOR_F const brush_color_1 = {
        .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f };
    constexpr UINT BMP_WIDTH = 2;
    constexpr UINT BMP_HEIGHT = 2;
    constexpr array<BYTE, 4 * BMP_WIDTH * BMP_HEIGHT> BMP_BITS = {
        // dane BGRA     
        0, 0, 230, 230,         128, 128, 128, 128,    // opacity 90%, 50%
        255, 255, 255, 255,     0, 0, 255, 255
    };
    // ...
    // Interfejs reprezentuj¹cy bitmapê
    ID2D1Bitmap* bitmap = nullptr;
    // ...
    // Sta³e kolorów
    D2D1_COLOR_F const clear_color = {
        .r = 0.75f, .g = 0.5f, .b = 0.25f, .a = 1.0f };
    D2D1_COLOR_F const brush_color = {
        .r = 0.0f, .g = 0.5f, .b = 0.0f, .a = 1.0f };
    HRESULT LoadBitmapFromFile(
        ID2D1RenderTarget* pRenderTarget,
        IWICImagingFactory* pIWICFactory,
        PCWSTR uri,
        UINT destinationWidth,
        UINT destinationHeight,
        ID2D1Bitmap** ppBitmap)
    {
        IWICBitmapDecoder* pDecoder = NULL;
        IWICBitmapFrameDecode* pSource = NULL;
        IWICStream* pStream = NULL;
        IWICFormatConverter* pConverter = NULL;
        IWICBitmapScaler* pScaler = NULL;

        HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
            uri,
            NULL,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &pDecoder
        );
        if (SUCCEEDED(hr))
        {
            // Create the initial frame.
            hr = pDecoder->GetFrame(0, &pSource);
        }
        if (SUCCEEDED(hr))
        {

            // Convert the image format to 32bppPBGRA
            // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
            hr = pIWICFactory->CreateFormatConverter(&pConverter);

        }

        if (SUCCEEDED(hr))
        {
            hr = pConverter->Initialize(
                pSource,
                GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                NULL,
                0.f,
                WICBitmapPaletteTypeMedianCut
            );
        }
        if (SUCCEEDED(hr))
        {

            // Create a Direct2D bitmap from the WIC bitmap.
            hr = pRenderTarget->CreateBitmapFromWicBitmap(
                pConverter,
                NULL,
                ppBitmap
            );
        }
        if (pDecoder) pDecoder->Release();
        if (pSource) pSource->Release();
        if (pStream) pStream->Release();
        if (pConverter) pConverter->Release();
        if (pScaler) pScaler->Release();

        return hr;
    }
}

void setupBitmap(ID2D1Factory7* d2d_factory, ID2D1HwndRenderTarget* d2d_render_target) {
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    //...
    CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        __uuidof(IWICImagingFactory),
        reinterpret_cast<LPVOID*>(&pIWICFactory));
    d2d_render_target->CreateSolidColorBrush(
        brush_color_1, &brush);
    d2d_render_target->CreateBitmap(
        SizeU(BMP_WIDTH, BMP_HEIGHT),
        BMP_BITS.data(),
        4 * BMP_WIDTH,
        BitmapProperties(
            PixelFormat(
                DXGI_FORMAT_B8G8R8A8_UNORM,
                D2D1_ALPHA_MODE_PREMULTIPLIED)),
        &bitmap);
    LoadBitmapFromFile(d2d_render_target, pIWICFactory, L"persona.jpg", 200, 200, &bitmap);
}

void drawBitmap(ID2D1HwndRenderTarget* d2d_render_target, FLOAT angle) {
    d2d_render_target->Clear(clear_color);
    d2d_render_target->SetTransform(Matrix3x2F::Identity());
    d2d_render_target->FillRectangle(RectF(10, 10, 400, 200), brush);
    d2d_render_target->SetTransform(
        Matrix3x2F::Rotation(-angle, Point2F(350, 250)));
    // Rysowanie bitmapy
    d2d_render_target->DrawBitmap(
        bitmap, RectF(200, 100, 500, 400), 1.0f,
        D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
        // D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
    );

}

void destroyBitmap() {
    if (bitmap) bitmap->Release();
    if (brush) brush->Release();
}