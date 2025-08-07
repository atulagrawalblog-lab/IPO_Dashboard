#include "Settings.h"
#include <windows.h>

const wchar_t* REG_PATH = L"Software\\IPO_Dashboard";

void SaveSetting(const std::wstring& key, const std::wstring& value) {
    HKEY hKey;
    if (RegCreateKeyExW(HKEY_CURRENT_USER, REG_PATH, 0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
        RegSetValueExW(hKey, key.c_str(), 0, REG_SZ,
            (const BYTE*)value.c_str(), (DWORD)((value.size() + 1) * sizeof(wchar_t)));
        RegCloseKey(hKey);
    }
}

std::wstring LoadSetting(const std::wstring& key, const std::wstring& def) {
    HKEY hKey;
    wchar_t buf[512];
    DWORD size = sizeof(buf);
    if (RegOpenKeyExW(HKEY_CURRENT_USER, REG_PATH, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        if (RegGetValueW(hKey, NULL, key.c_str(), RRF_RT_REG_SZ, NULL, buf, &size) == ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return std::wstring(buf);
        }
        RegCloseKey(hKey);
    }
    return def;
}
