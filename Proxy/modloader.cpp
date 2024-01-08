#include "modloader.hpp"

#include <filesystem>
#include <Windows.h>

#define LIB_WINPTHREAD_NAME "libwinpthread-1.dll"
#define LIB_STD_NAME "libstdc++-6.dll"
#define LIB_GCC_NAME "libgcc_s_seh-1.dll"
#define LIB_DOBBY_NAME "dobby.dll"

typedef void (*modloader_init)();

void load_core_libs(const std::filesystem::path &dir) {
    const std::filesystem::path winpthread_path = dir / LIB_WINPTHREAD_NAME;
    (void)LoadLibraryW(winpthread_path.c_str());
    
    const std::filesystem::path gcc_path = dir / LIB_GCC_NAME;
    (void)LoadLibraryW(gcc_path.c_str());
    
    const std::filesystem::path stdlib_path = dir / LIB_STD_NAME;
    (void)LoadLibraryW(stdlib_path.c_str());

    const std::filesystem::path dobby_path = dir / LIB_DOBBY_NAME;
    (void)LoadLibraryW(dobby_path.c_str());
}

void init_modloader() {
    wchar_t current_filename[MAX_PATH];
    (void)GetModuleFileNameW(nullptr, current_filename, MAX_PATH);
    const std::filesystem::path module_path = current_filename;
    const std::filesystem::path target_path = module_path.parent_path() / "alpha1";

    load_core_libs(target_path / "core"); // load core dependencies
    
    const std::filesystem::path alpha1_path = target_path / "alpha1.dll";

    const HMODULE alpha1_handle = LoadLibraryW(alpha1_path.c_str()); // load modloader
    const auto alpha1_init_proc = reinterpret_cast<modloader_init>(GetProcAddress(alpha1_handle, "modloader_init"));
    alpha1_init_proc(); // initialise
}
