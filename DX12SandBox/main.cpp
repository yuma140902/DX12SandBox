#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#endif

// @brief �R���\�[����ʂɕ������\��
// @param format %d�Ȃǂ̃t�H�[�}�b�g
// @remarks �f�o�b�O���̂ݓ��삷��
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
