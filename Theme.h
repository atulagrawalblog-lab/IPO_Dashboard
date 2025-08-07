#pragma once
#include <windows.h>
struct Theme {
    COLORREF background;
    COLORREF surface;
    COLORREF text;
    COLORREF primary;
    COLORREF border;
};
Theme GetSystemTheme();
