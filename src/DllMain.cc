
#include <WinSock2.h>
#include <Windows.h>

#include "WeChatHelper.h"

BOOL APIENTRY DllMain(HMODULE module, DWORD ul_reason_for_call, LPVOID reserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
        OutputDebugString("DLL_PROCESS_ATTACH START\n"); 
       // DisableThreadLibraryCalls(module);
        lucky::WeChatHelper::GetInstance().Init();
        OutputDebugString("DLL_PROCESS_ATTACH  END\n");
      break;
    }
    case DLL_THREAD_ATTACH: {
      break;
    }
    case DLL_THREAD_DETACH: {
       // OutputDebugString("DLL_THREAD_DETACH  END\n");
      break;
    }
    case DLL_PROCESS_DETACH: {
        OutputDebugString("DLL_PROCESS_DETACH START\n");
        lucky::WeChatHelper::GetInstance().DeInit();
        OutputDebugString("DLL_PROCESS_DETACH END\n");
        break;
    }
  }
  return TRUE;
}

