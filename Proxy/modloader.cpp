#include "modloader.hpp"

#include <filesystem>
#include <Windows.h>

typedef void (*modloader_init)();

void init_modloader() {
    wchar_t current_filename[MAX_PATH];
    (void)GetModuleFileNameW(nullptr, current_filename, MAX_PATH);
    const std::filesystem::path module_path = current_filename;
    const std::filesystem::path alpha1_path = module_path.parent_path() / "alpha1" / "alpha1.dll";

    const HMODULE alpha1_handle = LoadLibraryW(alpha1_path.c_str());
    const auto alpha1_init_proc = reinterpret_cast<modloader_init>(GetProcAddress(alpha1_handle, "modloader_init"));
    alpha1_init_proc();
}
