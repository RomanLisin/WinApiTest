//#include <d3d9.h>
//#include <Windows.h>
//#include <string>
//#include <filesystem>
//#include <iostream>
//
//// Пример функции инициализации Direct3D
//void init3D(HWND hwnd) {
//    LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);
//    if (!d3d) return;
//
//    D3DPRESENT_PARAMETERS d3dpp = {};
//    d3dpp.Windowed = TRUE;
//    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
//    d3dpp.hDeviceWindow = hwnd;
//
//    LPDIRECT3DDEVICE9 d3dDevice;
//    d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
//        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3dDevice);
//
//    // Отрисовка шрифта
//    ID3DXFont* font = nullptr;
//    D3DXCreateFont(d3dDevice, 20, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
//        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
//        L"Arial", &font);
//
//    RECT rect = { 100, 100, 500, 500 };
//    font->DrawText(nullptr, L"3D Preview", -1, &rect, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));
//
//    font->Release();
//    d3dDevice->Release();
//    d3d->Release();
//}
//
//int main() {
//    std::cout << "Initializing 3D visualization...\n";
//
//    HWND hwnd = GetConsoleWindow();
//    init3D(hwnd);
//
//    std::cout << "3D visualization is ready!\n";
//
//    return 0;
//}



//
//#include <d2d1.h>
//#include <dwrite.h>
//#include <Windows.h>
//#include <iostream>
//
//#pragma comment(lib, "d2d1.lib")
//#pragma comment(lib, "dwrite.lib")
//
//void drawText(HWND hwnd) {
//    // Инициализация Direct2D
//    ID2D1Factory* d2dFactory = nullptr;
//    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory);
//
//    RECT rc;
//    GetClientRect(hwnd, &rc);
//    D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
//
//    ID2D1HwndRenderTarget* renderTarget = nullptr;
//    d2dFactory->CreateHwndRenderTarget(
//        D2D1::RenderTargetProperties(),
//        D2D1::HwndRenderTargetProperties(hwnd, size),
//        &renderTarget);
//
//    ID2D1SolidColorBrush* brush = nullptr;
//    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &brush);
//
//    // Инициализация DirectWrite
//    IDWriteFactory* writeFactory = nullptr;
//    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&writeFactory));
//
//    IDWriteTextFormat* textFormat = nullptr;
//    writeFactory->CreateTextFormat(
//        L"Arial",                    // Шрифт
//        nullptr,                     // Поставщик шрифта
//        DWRITE_FONT_WEIGHT_BOLD,     // Жирность
//        DWRITE_FONT_STYLE_NORMAL,    // Стиль
//        DWRITE_FONT_STRETCH_NORMAL,  // Растяжение
//        20.0f,                       // Размер шрифта
//        L"en-us",                    // Локаль
//        &textFormat);
//
//    // Рисование текста
//    renderTarget->BeginDraw();
//    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
//    renderTarget->DrawTextW(
//        L"3D Preview",
//        wcslen(L"3D Preview"),
//        textFormat,
//        D2D1::RectF(100, 100, 500, 500),
//        brush);
//    renderTarget->EndDraw();
//
//    // Освобождение ресурсов
//    textFormat->Release();
//    writeFactory->Release();
//    brush->Release();
//    renderTarget->Release();
//    d2dFactory->Release();
//}
//
//int main() {
//    HWND hwnd = GetConsoleWindow();
//    drawText(hwnd);
//
//    std::cout << "Text rendering completed.\n";
//    return 0;
//}



#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include <iostream>
#include <string>

using namespace DirectX;
using Microsoft::WRL::ComPtr;

// Инициализация Direct3D 11
void init3D(HWND hwnd) {
    // Создание устройства и контекста
    D3D_FEATURE_LEVEL featureLevel;
    ComPtr<ID3D11Device> d3dDevice;
    ComPtr<ID3D11DeviceContext> d3dContext;

    D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        d3dDevice.GetAddressOf(),
        &featureLevel,
        d3dContext.GetAddressOf());

    // Создание своп-чейна
    ComPtr<IDXGISwapChain> swapChain;
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = 800;
    swapChainDesc.BufferDesc.Height = 600;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hwnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = TRUE;

    ComPtr<IDXGIFactory> factory;
    CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(factory.GetAddressOf()));
    factory->CreateSwapChain(d3dDevice.Get(), &swapChainDesc, swapChain.GetAddressOf());

    // Создание рендера и бэк-буфера
    ComPtr<ID3D11RenderTargetView> renderTargetView;
    ComPtr<ID3D11Texture2D> backBuffer;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
    d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, renderTargetView.GetAddressOf());

    d3dContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);

    // Загрузка шрифта и отрисовка текста
    std::unique_ptr<SpriteBatch> spriteBatch = std::make_unique<SpriteBatch>(d3dContext.Get());
    std::unique_ptr<SpriteFont> spriteFont = std::make_unique<SpriteFont>(d3dDevice.Get(), L"Arial.spritefont");

    d3dContext->ClearRenderTargetView(renderTargetView.Get(), DirectX::Colors::CornflowerBlue);

    spriteBatch->Begin();
    spriteFont->DrawString(spriteBatch.get(), L"3D Preview", XMFLOAT2(100, 100), DirectX::Colors::White);
    spriteBatch->End();

    swapChain->Present(1, 0);
}

// Основная функция
int main() {
    std::cout << "Initializing 3D visualization...\n";

    HWND hwnd = GetConsoleWindow();
    init3D(hwnd);

    std::cout << "3D visualization is ready!\n";

    return 0;
}
