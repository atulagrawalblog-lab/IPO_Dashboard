#include "UI.h"
#include "Logic.h"
#include "Theme.h"
#include "Settings.h"

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <gdiplus.h>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace Gdiplus;

static HWND hPriceInput = nullptr;
static HWND hLotInput = nullptr;
static HWND hSMERadio = nullptr;
static HWND hMainRadio = nullptr;
static HWND hChartBtn = nullptr;
static HWND hExportBtn = nullptr;

static std::vector<IPOResult> g_results;
static Theme g_theme;
static bool g_chartView = false;

static int g_hoverIndex = -1;
static int g_chartHover = -1;
static std::vector<RectF> g_chartBars;

static float animProgress = 1.0f;
static UINT_PTR animTimer = 0;

//
// Animation handling
//
static void StartAnimation(HWND hwnd) {
    animProgress = 0.0f;
    if (animTimer) KillTimer(hwnd, animTimer);
    animTimer = SetTimer(hwnd, 1, 16, NULL); // ~60fps
}

void UI_HandleTimer(HWND hwnd) {
    animProgress += 0.06f;
    if (animProgress >= 1.0f) {
        animProgress = 1.0f;
        if (animTimer) {
            KillTimer(hwnd, animTimer);
            animTimer = 0;
        }
    }
    InvalidateRect(hwnd, NULL, TRUE);
}

//
// Theme update
//
void UI_UpdateTheme() {
    g_theme = GetSystemTheme();
}

//
// UI Initialization
//
void UI_Init(HWND hwnd, HINSTANCE hInstance) {
    g_theme = GetSystemTheme();

    CreateWindowW(L"STATIC", L"IPO Price:",
        WS_CHILD | WS_VISIBLE, 20, 20, 80, 20,
        hwnd, NULL, hInstance, NULL);
    hPriceInput = CreateWindowW(L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
        100, 20, 100, 20, hwnd, (HMENU)101, hInstance, NULL);

    CreateWindowW(L"STATIC", L"Lot Size:",
        WS_CHILD | WS_VISIBLE, 20, 50, 80, 20,
        hwnd, NULL, hInstance, NULL);
    hLotInput = CreateWindowW(L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
        100, 50, 100, 20, hwnd, (HMENU)102, hInstance, NULL);

    hSMERadio = CreateWindowW(L"BUTTON", L"SME IPO",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        220, 20, 100, 20, hwnd, (HMENU)201, hInstance, NULL);
    hMainRadio = CreateWindowW(L"BUTTON", L"Mainboard IPO",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        220, 50, 150, 20, hwnd, (HMENU)202, hInstance, NULL);

    SendMessage(hSMERadio, BM_SETCHECK, BST_CHECKED, 0);

    hChartBtn = CreateWindowW(L"BUTTON", L"Show Chart",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        400, 20, 120, 25, hwnd, (HMENU)301, hInstance, NULL);

    hExportBtn = CreateWindowW(L"BUTTON", L"Export",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        400, 50, 120, 25, hwnd, (HMENU)302, hInstance, NULL);
}

//
// Handle button clicks and other commands
//
void UI_HandleCommand(HWND hwnd, WPARAM wParam, LPARAM) {
    switch (LOWORD(wParam)) {
    case 301: { // Show Chart
        wchar_t bufPrice[32], bufLot[32];
        GetWindowTextW(hPriceInput, bufPrice, 32);
        GetWindowTextW(hLotInput, bufLot, 32);

        double price = _wtof(bufPrice);
        int lotSize = _wtoi(bufLot);

        bool isSME = (SendMessage(hSMERadio, BM_GETCHECK, 0, 0) == BST_CHECKED);
        g_results = CalculateIPO(isSME ? L"SME" : L"MAIN", price, lotSize);

        g_chartView = true;
        StartAnimation(hwnd);
        break;
    }
    case 302: { // Export (basic CSV export to file)
        FILE* f;
        _wfopen_s(&f, L"ipo_results.csv", L"w, ccs=UTF-8");
        if (f) {
            fwprintf(f, L"Category,Lots,Shares,Amount,Description\n");
            for (auto& r : g_results) {
                fwprintf(f, L"%ls,%d,%d,%.2f,%ls\n",
                    r.category.c_str(), r.lots, r.shares, r.amount, r.description.c_str());
            }
            fclose(f);
        }
        MessageBoxW(hwnd, L"Results exported to ipo_results.csv", L"Export", MB_OK);
        break;
    }
    }
}

//
// Rendering
//
void UI_Render(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    Graphics g(hdc);
    g.Clear(Color(GetRValue(g_theme.background),
                  GetGValue(g_theme.background),
                  GetBValue(g_theme.background)));

    if (g_chartView && !g_results.empty()) {
        int y = 120;
        SolidBrush textBrush(Color(GetRValue(g_theme.text),
                                   GetGValue(g_theme.text),
                                   GetBValue(g_theme.text)));
        FontFamily fontFamily(L"Segoe UI");
        Font font(&fontFamily, 14, FontStyleRegular, UnitPixel);

        for (size_t i = 0; i < g_results.size(); i++) {
            std::wstring line = g_results[i].category + L": " +
                std::to_wstring(g_results[i].lots) + L" lots";
            g.DrawString(line.c_str(), -1, &font,
                         PointF(20, (REAL)y), &textBrush);
            y += 30;
        }
    }

    EndPaint(hwnd, &ps);
}

//
// Handle mouse move (optional hover effect placeholder)
//
void UI_HandleMouseMove(HWND, int, int) {
    // Can be expanded later for hover tooltips
}

//
// Handle resize (future use)
//
void UI_HandleResize(HWND) {
    // Layout updates could be added here
}
