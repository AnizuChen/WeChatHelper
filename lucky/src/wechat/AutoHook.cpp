
#include "AutoHook.h"
#include <windows.h>
#include "detours.h"


HookPoint::~HookPoint() {

}

int32_t DetoursHook::Hook(void* o, void* n) {
	LONG ret = 0;
	ret = DetourRestoreAfterWith();
	ret = DetourTransactionBegin();
	ret = DetourUpdateThread(GetCurrentThread());
	ret=  DetourAttach((PVOID*)o, n);
	ret =  DetourTransactionCommit();
	return (int32_t)ret;
}

int32_t DetoursHook::UnHook(void* o, void* n) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((PVOID*)o, n);
	return DetourTransactionCommit();
}