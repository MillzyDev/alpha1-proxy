#include <windows.h>

#include "winhttp.hpp"

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH)
        return TRUE;

    DisableThreadLibraryCalls(hmodule); // minor optimisation
    init_proxy();
}