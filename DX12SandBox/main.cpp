#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#endif

#include <d3d12.h>
#include <dxgi1_6.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include <vector>
#include <string>

// @brief �R���\�[����ʂɕ������\��
// @param format %d�Ȃǂ̃t�H�[�}�b�g
// @remarks �f�o�b�O���̂ݓ��삷��
void DebugOutputFormatString(const char* format, ...)
{
#ifdef _DEBUG
    va_list valist;
    va_start(valist, format);
    vprintf(format, valist);
    va_end(valist);
#endif
}

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

IDXGIFactory6* dxgi_factory = nullptr;

#ifdef _DEBUG
int main()
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
    DebugOutputFormatString("Show windows test\n");

    WNDCLASSEX w = {};
    w.cbSize = sizeof(WNDCLASSEX);
    w.lpfnWndProc = WndProc;
    w.lpszClassName = TEXT("DX12Sandbox");
    w.hInstance = GetModuleHandle(nullptr);
    RegisterClassEx(&w);

    RECT window_rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW, false);

    HWND hwnd = CreateWindow(
        w.lpszClassName,
        TEXT("DX12 �e�X�g"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        window_rect.right - window_rect.left,
        window_rect.bottom - window_rect.top,
        nullptr,
        nullptr,
        w.hInstance,
        nullptr);

    //TODO: Chapter 3.2.2
    if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&dxgi_factory)))) {
        DebugOutputFormatString("CreateDXGIFactory1 ���s\n");
        return -1;
    }
    // �A�_�v�^�[��񋓂���
    std::vector<IDXGIAdapter*> adapters;
    {
        IDXGIAdapter* tmp = nullptr;
        int i;
        for (i = 0; dxgi_factory->EnumAdapters(i, &tmp) != DXGI_ERROR_NOT_FOUND; ++i)
            adapters.push_back(tmp);
        DebugOutputFormatString("%d�̃A�_�v�^�[\n", i);
    }
    for (auto adapter : adapters) {
        DXGI_ADAPTER_DESC desc;
        adapter->GetDesc(&desc);
        DebugOutputFormatString("- %ls\n", desc.Description);
        std::wstring str = desc.Description;
    }

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = {};
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT) {
            break;
        }
    }

    UnregisterClass(w.lpszClassName, w.hInstance);
    return 0;
}
