#include <windows.h>
#include <filesystem>
#include <sstream>

#include "winhttp.hpp"
#include "modloader.hpp"

bool is_unity() {
    char current_module[MAX_PATH];
    (void)GetModuleFileNameA(nullptr, current_module, MAX_PATH);
    const std::filesystem::path module_path = current_module;

    const wchar_t *file_name = module_path.stem().c_str();
    const std::filesystem::path base_dir = module_path.parent_path();

    std::wstringstream ss;
    ss << file_name << L"_Data";
    const std::filesystem::path data_dir = base_dir / ss.str(); // get the path of the game's data directory

    // ReSharper disable once CppTooWideScopeInitStatement
    const std::filesystem::path global_game_managers = data_dir / "globalgamemanagers";

    if (exists(data_dir) && exists(global_game_managers))
        return true; // if the data dir and globalgamemanagers exist, then its probably a unity game.
    
    return false;
}

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH)
        return TRUE;

    DisableThreadLibraryCalls(hmodule); // minor optimisation
    init_proxy();

    if (is_unity())
        init_modloader();

    return TRUE;
}
