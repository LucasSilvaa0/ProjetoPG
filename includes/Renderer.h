#ifndef RENDERHEADER
#define RENDERHEADER
#include <windows.h>
#include <vector>
#include "Point.h"


struct RGB {
    BYTE r, g, b;
};

class Renderer {
public:

    HWND m_hWnd;
    int m_width, m_height;
    std::vector<Point3D> indio;

    Renderer(int width, int height)
        : m_width(width), m_height(height){
        // Inicializa a janela
        WNDCLASS wc = {0};
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = "RendererClass";
        RegisterClass(&wc);

        m_hWnd = CreateWindowEx(0, "RendererClass", "RGB Renderer", WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height, nullptr, nullptr, wc.hInstance, this);
        ShowWindow(m_hWnd, SW_SHOW);
        UpdateWindow(m_hWnd);
    }

    void Render() {
        // Cria o contexto de dispositivo para desenhar na janela
        HDC hdc = GetDC(m_hWnd);

        // Preenche cada pixel com a cor correspondente
        for (int y = 0; y < m_height; ++y) {
            for (int x = 0; x < m_width; ++x) {
                auto color = indio[y * m_width + x];
                SetPixel(hdc, x, y, RGB(color.getX(), color.getY(), color.getZ()));
            }
        }

        // Libera o contexto de dispositivo
        ReleaseDC(m_hWnd, hdc);
    }

    void Run() {
        // Loop de mensagens da janela
        MSG msg = {0};
        while (GetMessage(&msg, nullptr, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        Renderer* pRenderer;
        if (uMsg == WM_CREATE) {
            pRenderer = reinterpret_cast<Renderer*>(((CREATESTRUCT*)lParam)->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pRenderer));
        } else {
            pRenderer = reinterpret_cast<Renderer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }

        if (pRenderer) {
            switch (uMsg) {
            case WM_PAINT:
                pRenderer->Render();
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            }
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    void updateIndio(std::vector<Point3D>& indio_novo){
        indio.resize(0);
        indio = indio_novo;
    }
    
};

#endif