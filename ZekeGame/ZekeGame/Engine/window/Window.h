#pragma once
extern HWND g_hwnd;
extern GraphicsEngine* g_graphicsEngine;
void InitWindow(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName);
bool DispatchWindowMessage();
LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern int notch;
extern bool mEve[10];


extern int g_Key;
extern bool g_isPressShift;