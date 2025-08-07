#include "Theme.h"
#include <winreg.h>

Theme GetSystemTheme() {
    Theme t{};
    DWORD value = 1;
    DWORD size = sizeof(value);
    LSTATUS st = RegGetValueW(HKEY_CURRENT_USER,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        L"AppsUseLightTheme", RRF_RT_REG_DWORD, NULL, &value, &size);
    if (st != ERROR_SUCCESS) value = 1;

    if (value == 0) {
        // Dark mode
        t.background = RGB(30, 30, 30);
        t.surface = RGB(45, 45, 45);
        t.text = RGB(230, 230, 230);
        t.primary = RGB(33, 128, 141);
        t.border = RGB(70, 70, 70);
    } else {
        // Light mode
        t.background = RGB(252, 252, 249);
        t.surface = RGB(255, 255, 253);
        t.text = RGB(19, 52, 59);
        t.primary = RGB(33, 128, 141);
        t.border = RGB(94, 82, 64);
    }
    return t;
}
