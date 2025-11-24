#pragma once
#include "BaseWindow.h"
class CoreWindow : public BaseWindow
{
public:
	CoreWindow();
	~CoreWindow() override;
public:
	int Run(HINSTANCE hInstance, int nCmdShow) override;
private:
	ATOM MyRegisterClass() override;
	void createWindow() override;
	void showWindow(int nCmdShow) override;
	static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	int MessageLoop() override;
};

