#include "WeChatHelper.h"
#include <Windows.h>

/*
int WINAPI WinMain(
    HINSTANCE hInstance,        // 当前实例句柄
    HINSTANCE hPrevInstance,    // 前一个实例句柄（在现代 Windows 中一般为 NULL）
    LPSTR lpCmdLine,            // 命令行参数
    int nCmdShow                // 窗口显示方式
) {
    lucky::WeChatHelper helper;
    helper.Run();
    return 0;
}*/

int  main() {
    lucky::WeChatHelper helper;
    helper.Run();
    return 0;
}
