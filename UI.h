#pragma once
#include <windows.h>

void UI_Init(HWND hwnd, HINSTANCE hInstance);
void UI_HandleCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);
void UI_Render(HWND hwnd);
void UI_HandleMouseMove(HWND hwnd, int x, int y);
void UI_HandleResize(HWND hwnd);
void UI_HandleTimer(HWND hwnd);
void UI_UpdateTheme();
