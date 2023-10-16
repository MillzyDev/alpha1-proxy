#include "winhttp.h"

#include <windows.h>
#include <filesystem>

// This stuff only works on AMD64 (x86-64)
// I figured it wasn't really worth supporting/preprocessing for other architectures since I cant exactly test if it works

#define W_STRINGIFY(k) #k
#define STRINGIFY(k) W_STRINGIFY(k)

#define EXPORT_PRAGMA comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)

#define PROXY_FUNCTION(name)                                                        \
    FARPROC o##name;                                                                \
    __declspec(dllexport) void WINAPI _##name() {                                   \
        _Pragma(STRINGIFY(EXPORT_PRAGMA));                                          \
        o##name();                                                                  \
    }


PROXY_FUNCTION(WinHttpAddRequestHeaders)
PROXY_FUNCTION(WinHttpAddRequestHeadersEx)
PROXY_FUNCTION(WinHttpAutoProxySvcMain)
PROXY_FUNCTION(WinHttpCloseHandle)
PROXY_FUNCTION(WinHttpConnect)
PROXY_FUNCTION(WinHttpConnectionDeletePolicyEntries)
PROXY_FUNCTION(WinHttpConnectionDeleteProxyInfo)
PROXY_FUNCTION(WinHttpConnectionFreeNameList)
PROXY_FUNCTION(WinHttpConnectionFreeProxyInfo)
PROXY_FUNCTION(WinHttpConnectionFreeProxyList)
PROXY_FUNCTION(WinHttpConnectionGetNameList)
PROXY_FUNCTION(WinHttpConnectionGetProxyInfo)
PROXY_FUNCTION(WinHttpConnectionGetProxyList)
PROXY_FUNCTION(WinHttpConnectionSetPolicyEntries)
PROXY_FUNCTION(WinHttpConnectionSetProxyInfo)
PROXY_FUNCTION(WinHttpConnectionUpdateIfIndexTable)
PROXY_FUNCTION(WinHttpCrackUrl)
PROXY_FUNCTION(WinHttpCreateProxyResolver)
PROXY_FUNCTION(WinHttpCreateUrl)
PROXY_FUNCTION(WinHttpDetectAutoProxyConfigUrl)
PROXY_FUNCTION(WinHttpFreeProxyResult)
PROXY_FUNCTION(WinHttpFreeProxyResultEx)
PROXY_FUNCTION(WinHttpFreeProxySettings)
PROXY_FUNCTION(WinHttpGetDefaultProxyConfiguration)
PROXY_FUNCTION(WinHttpGetIProxyConfigForCurrentUser)
PROXY_FUNCTION(WinHttpGetProxyForUrl)
PROXY_FUNCTION(WinHttpGetProxyForUrlEx)
PROXY_FUNCTION(WinHttpGetProxyForUrlEx2)
PROXY_FUNCTION(WinHttpGetProxyForUrlHvsi)
PROXY_FUNCTION(WinHttpGetProxyResult)
PROXY_FUNCTION(WinHttpGetProxyResultEx)
PROXY_FUNCTION(WinHttpGetProxySettingsVersion)
PROXY_FUNCTION(WinHttpGetTunnelSocket)
PROXY_FUNCTION(WinHttpOpen)
PROXY_FUNCTION(WinHttpOpenRequest)
PROXY_FUNCTION(WinHttpPacJsWorkerMain)
PROXY_FUNCTION(WinHttpProbeConnectivity)
PROXY_FUNCTION(WinHttpQueryAuthSchemes)
PROXY_FUNCTION(WinHttpQueryDataAvailable)
PROXY_FUNCTION(WinHttpQueryHeaders)
PROXY_FUNCTION(WinHttpQueryOption)
PROXY_FUNCTION(WinHttpReadData)
PROXY_FUNCTION(WinHttpReadProxySettings)
PROXY_FUNCTION(WinHttpReadProxySettingsHvsi)
PROXY_FUNCTION(WinHttpRecieveResponse)
PROXY_FUNCTION(WinHttpResetAutoProxy)
PROXY_FUNCTION(WinHttpSaveProxyCredentials)
PROXY_FUNCTION(WinHttpSendRequest)
PROXY_FUNCTION(WinHttpSetCredentials)
PROXY_FUNCTION(WinHttpSetDefaultProxyConfiguration)
PROXY_FUNCTION(WinHttpSetOption)
PROXY_FUNCTION(WinHttpSetProxySettingsPerUser)
PROXY_FUNCTION(WinHttpSetSecureLegacyServersAppCompat)
PROXY_FUNCTION(WinHttpSetStatusCallback)
PROXY_FUNCTION(WinHttpSetTimeouts)
PROXY_FUNCTION(WinHttpTimeFromSystemTime)
PROXY_FUNCTION(WinHttpTimeToSystemTime)
PROXY_FUNCTION(WinHttpWebSocketClose)
PROXY_FUNCTION(WinHttpWebSocketCompleteUpgrade)
PROXY_FUNCTION(WinHttpWebsocketQueryCloseStatus)
PROXY_FUNCTION(WinHttpWebSocket_Recieve)
PROXY_FUNCTION(WinHttpWebSocketSend)
PROXY_FUNCTION(WinHttpWebSocketShutdown)
PROXY_FUNCTION(WinHttpWriteData)
PROXY_FUNCTION(WinHttpWriteProxySettings)


#define LOAD_ORIG_FUNC(name) o##name = GetProcAddress(winhttp, ###name)

void load_winhttp(HMODULE winhttp) {

}

void init_proxy() {
    char systemPath[MAX_PATH];
    GetSystemDirectoryA(systemPath, MAX_PATH);

    std::filesystem::path system32_path = systemPath;
    std::filesystem::path winhttp_path = system32_path / "winhttp.dll";

    HMODULE winhttp_dll = LoadLibraryW(winhttp_path.c_str());
    load_winhttp(winhttp_dll);
}