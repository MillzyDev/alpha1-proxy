#include <windows.h>
#include <filesystem>

#include "winhttp.hpp"
#include "modloader.hpp"

/*
 * This proxy is based on the version.dll proxy written by BitCrackers,
 * licensed under GNU General Public License (Version 3).
 * https://github.com/BitCrackers/version-proxy
 */

bool is_unity(const std::filesystem::path &file_path) {
    //const wchar_t *file_name = file_path.stem().c_str();

    const std::filesystem::path base_dir = file_path.parent_path();

    std::wstring data_name = file_path.stem().c_str();
    data_name += L"_Data";
    const std::filesystem::path data_path = base_dir / data_name;

    //MessageBoxW(nullptr, file_path.c_str(), L"Proxy", MB_OK);
    //MessageBoxW(nullptr, file_path.stem().c_str(), L"Proxy", MB_OK);
    
    if (!exists(data_path))
        return false;

    // ReSharper disable once CppTooWideScopeInitStatement
    const std::filesystem::path global_game_managers = data_path / "globalgamemanagers";

    if (!exists(global_game_managers))
        return false;
    
    return true;
}

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH)
        return TRUE;

    DisableThreadLibraryCalls(hmodule); // minor optimisation
    init_proxy();

    wchar_t main_module[MAX_PATH];
    (void)GetModuleFileNameW(nullptr, main_module, MAX_PATH); // get exe path

    if (is_unity(main_module)) // unity crash handler also loads this, we dont want that
        init_modloader();

    return TRUE;
}
