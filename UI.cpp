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

static HWND hPriceInput = nullptr, hLotInput = nullptr, hSMERadio = nullptr, hMainRadio = nullptr, hChartBtn = nullptr, hExportBtn = nullptr;
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
void StartAnimation(HWND hwnd) {
    animProgress = 0.0f;
    if (animTimer) KillTimer(hwnd, animTimer);
    animTimer = SetTimer(hwnd, 1, 16, NULL); // ~60fps
}

void UI_HandleTimer(HWND hwnd) {
    animProgress += 0.06f;
    if (animProgress >= 1.0f) {
        animProgress = 1.0f;
        if (animTimer) { KillTimer(hwnd, animTimer); animTimer = 0; }
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
// Drawing helpers
//
void FillRoundedRect(Graphics& g, RectF rect, Color color, float radius) {
    GraphicsPath path;
    path.AddArc(rect.X, rect.Y, radius, radius, 180, 90);
    path.AddArc(rect.GetRight() - radius, rect.Y, radius, radius, 270, 90);
    path.AddArc(rect.GetRight() - radius, rect.GetBottom() - radius, radius, radius, 0, 90);
    path.AddArc(rect.X, rect.GetBottom() - radius, radius, radius, 90, 90);
    path.CloseFigure();
    SolidBrush b(color);
    g.FillPath(&b, &path);
}

def_placeholder = "DO_NOT_USE"  # placeholder to avoid accidental python eval issues
