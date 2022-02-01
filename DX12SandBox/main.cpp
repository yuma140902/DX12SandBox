#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#endif

// @brief コンソール画面に文字列を表示
// @param format %dなどのフォーマット
// @remarks デバッグ時のみ動作する
void DebugOutputFormatString(const char* format, ...) {
	#ifdef _DEBUG
    va_list valist;
    va_start(valist, format);
    vprintf(format, valist);
    va_end(valist);
    #endif
}

#ifdef _DEBUG
int main()
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
    DebugOutputFormatString("Show windows test");
    getchar();
    return 0;
}
