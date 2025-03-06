#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vector>
#include "Point.h"

class Renderer
{
public:
    int width, height;
    std::vector<Point3D> colors;
    HWND hwnd;
    HDC hdc;
    HBITMAP hBitmap;
    HDC hdcMem;

    void drawPixels()
    {

        std::vector<COLORREF> pixels(width * height);

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int index = y * width + x;
                if (index < colors.size())
                {

                    int r = static_cast<int>(colors[index].z * 255);
                    int g = static_cast<int>(colors[index].y * 255);
                    int b = static_cast<int>(colors[index].x * 255);

                    pixels[index] = RGB(r, g, b);
                }
                else
                {
                    // Preenche com preto se não houver cor definida
                    pixels[index] = RGB(0, 0, 0);
                }
            }
        }

        SetBitmapBits(hBitmap, width * height * sizeof(COLORREF), pixels.data());
    }

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Obtém o renderer associado à janela
            Renderer *renderer = reinterpret_cast<Renderer *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            if (renderer)
            {
                // Desenha o bitmap na janela
                BitBlt(hdc, 0, 0, renderer->width, renderer->height, renderer->hdcMem, 0, 0, SRCCOPY);
            }

            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    Renderer(int width, int height, const std::vector<Point3D> &colors, std::string appName)
        : width(width), height(height), colors(colors)
    {

        WNDCLASS wc = {};
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = TEXT("RendererClass");
        RegisterClass(&wc);

        hwnd = CreateWindowEx(
            0,
            TEXT("RendererClass"),
            TEXT(appName.c_str()),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, width, height,
            NULL,
            NULL,
            GetModuleHandle(NULL),
            NULL);

        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

        hdc = GetDC(hwnd);

        hdcMem = CreateCompatibleDC(hdc);

        hBitmap = CreateCompatibleBitmap(hdc, width, height);

        SelectObject(hdcMem, hBitmap);

        drawPixels();

        ShowWindow(hwnd, SW_SHOW);
    }

    ~Renderer()
    {
        DeleteObject(hBitmap);
        DeleteDC(hdcMem);
        ReleaseDC(hwnd, hdc);
    }

    void run()
    {
        MSG msg = {};
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void updateColors(std::vector<Point3D> &indio)
    {
        colors = indio;
        drawPixels();
    }
};