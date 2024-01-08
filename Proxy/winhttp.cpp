#include "winhttp.hpp"

#include <windows.h>
#include <filesystem>

// This stuff only works on AMD64 (x86-64)
// I figured it wasn't really worth supporting/preprocessing for other architectures since I cant exactly test if it works

#define W_STRINGIFY(k) #k
#define STRINGIFY(k) W_STRINGIFY(k)

#define EXPORT_PRAGMA comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)

// we do not need to pass arguments or return a value since the contents of registers do not change
// may not work with all calling conventions
#define PROXY_FUNCTION(name)                                                        \
    FARPROC o##name;                                                                \
    __declspec(dllexport) void WINAPI _##name() {                                   \
        __pragma(STRINGIFY(EXPORT_PRAGMA));                                         \
        o##name();                                                                  \
    }

#ifndef _M_AMD64
#error Architecture supported. Supported architectures: AMD64 (x86-64)
#endif

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
PROXY_FUNCTION(WinHttpGetIEProxyConfigForCurrentUser)
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
PROXY_FUNCTION(WinHttpReceiveResponse)
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
PROXY_FUNCTION(WinHttpWebSocketQueryCloseStatus)
PROXY_FUNCTION(WinHttpWebSocketReceive)
PROXY_FUNCTION(WinHttpWebSocketSend)
PROXY_FUNCTION(WinHttpWebSocketShutdown)
PROXY_FUNCTION(WinHttpWriteData)
PROXY_FUNCTION(WinHttpWriteProxySettings)


#define LOAD_ORIG_FUNC(name) o##name = GetProcAddress(winhttp, #name)

void load_winhttp(const HMODULE winhttp) {
    LOAD_ORIG_FUNC(WinHttpAddRequestHeaders);
    LOAD_ORIG_FUNC(WinHttpAddRequestHeadersEx);
    LOAD_ORIG_FUNC(WinHttpAutoProxySvcMain);
    LOAD_ORIG_FUNC(WinHttpCloseHandle);
    LOAD_ORIG_FUNC(WinHttpConnect);
    LOAD_ORIG_FUNC(WinHttpConnectionDeletePolicyEntries);
    LOAD_ORIG_FUNC(WinHttpConnectionDeleteProxyInfo);
    LOAD_ORIG_FUNC(WinHttpConnectionFreeNameList);
    LOAD_ORIG_FUNC(WinHttpConnectionFreeProxyInfo);
    LOAD_ORIG_FUNC(WinHttpConnectionFreeProxyList);
    LOAD_ORIG_FUNC(WinHttpConnectionGetNameList);
    LOAD_ORIG_FUNC(WinHttpConnectionGetProxyInfo);
    LOAD_ORIG_FUNC(WinHttpConnectionGetProxyList);
    LOAD_ORIG_FUNC(WinHttpConnectionSetPolicyEntries);
    LOAD_ORIG_FUNC(WinHttpConnectionSetProxyInfo);
    LOAD_ORIG_FUNC(WinHttpConnectionUpdateIfIndexTable);
    LOAD_ORIG_FUNC(WinHttpCrackUrl);
    LOAD_ORIG_FUNC(WinHttpCreateProxyResolver);
    LOAD_ORIG_FUNC(WinHttpCreateUrl);
    LOAD_ORIG_FUNC(WinHttpDetectAutoProxyConfigUrl);
    LOAD_ORIG_FUNC(WinHttpFreeProxyResult);
    LOAD_ORIG_FUNC(WinHttpFreeProxyResultEx);
    LOAD_ORIG_FUNC(WinHttpFreeProxySettings);
    LOAD_ORIG_FUNC(WinHttpGetDefaultProxyConfiguration);
    LOAD_ORIG_FUNC(WinHttpGetIEProxyConfigForCurrentUser);
    LOAD_ORIG_FUNC(WinHttpGetProxyForUrl);
    LOAD_ORIG_FUNC(WinHttpGetProxyForUrlEx);
    LOAD_ORIG_FUNC(WinHttpGetProxyForUrlEx2);
    LOAD_ORIG_FUNC(WinHttpGetProxyForUrlHvsi);
    LOAD_ORIG_FUNC(WinHttpGetProxyResult);
    LOAD_ORIG_FUNC(WinHttpGetProxyResultEx);
    LOAD_ORIG_FUNC(WinHttpGetProxySettingsVersion);
    LOAD_ORIG_FUNC(WinHttpGetTunnelSocket);
    LOAD_ORIG_FUNC(WinHttpOpen);
    LOAD_ORIG_FUNC(WinHttpOpenRequest);
    LOAD_ORIG_FUNC(WinHttpPacJsWorkerMain);
    LOAD_ORIG_FUNC(WinHttpProbeConnectivity);
    LOAD_ORIG_FUNC(WinHttpQueryAuthSchemes);
    LOAD_ORIG_FUNC(WinHttpQueryDataAvailable);
    LOAD_ORIG_FUNC(WinHttpQueryHeaders);
    LOAD_ORIG_FUNC(WinHttpQueryOption);
    LOAD_ORIG_FUNC(WinHttpReadData);
    LOAD_ORIG_FUNC(WinHttpReadProxySettings);
    LOAD_ORIG_FUNC(WinHttpReadProxySettingsHvsi);
    LOAD_ORIG_FUNC(WinHttpReceiveResponse);
    LOAD_ORIG_FUNC(WinHttpResetAutoProxy);
    LOAD_ORIG_FUNC(WinHttpSaveProxyCredentials);
    LOAD_ORIG_FUNC(WinHttpSendRequest);
    LOAD_ORIG_FUNC(WinHttpSetCredentials);
    LOAD_ORIG_FUNC(WinHttpSetDefaultProxyConfiguration);
    LOAD_ORIG_FUNC(WinHttpSetOption);
    LOAD_ORIG_FUNC(WinHttpSetProxySettingsPerUser);
    LOAD_ORIG_FUNC(WinHttpSetSecureLegacyServersAppCompat);
    LOAD_ORIG_FUNC(WinHttpSetStatusCallback);
    LOAD_ORIG_FUNC(WinHttpSetTimeouts);
    LOAD_ORIG_FUNC(WinHttpTimeFromSystemTime);
    LOAD_ORIG_FUNC(WinHttpTimeToSystemTime);
    LOAD_ORIG_FUNC(WinHttpWebSocketClose);
    LOAD_ORIG_FUNC(WinHttpWebSocketCompleteUpgrade);
    LOAD_ORIG_FUNC(WinHttpWebSocketQueryCloseStatus);
    LOAD_ORIG_FUNC(WinHttpWebSocketReceive);
    LOAD_ORIG_FUNC(WinHttpWebSocketSend);
    LOAD_ORIG_FUNC(WinHttpWebSocketShutdown);
    LOAD_ORIG_FUNC(WinHttpWriteData);
    LOAD_ORIG_FUNC(WinHttpWriteProxySettings);
}

void init_proxy() {
    char system_path[MAX_PATH];
    GetSystemDirectoryA(system_path, MAX_PATH);

    const std::filesystem::path system32_path = system_path;
    const std::filesystem::path winhttp_path = system32_path / "winhttp.dll";
    // load original dll
    const HMODULE winhttp_dll = LoadLibraryW(winhttp_path.c_str());
    load_winhttp(winhttp_dll); // provide a handle so our methods call the original methods
}