#pragma once
class BaseWindow
{
public:
	BaseWindow();
	virtual ~BaseWindow() {};
public:
	virtual int Run(HINSTANCE hInstance, int nCmdShow) = 0;
private:
	virtual ATOM MyRegisterClass() = 0;
	virtual void createWindow() = 0;
	virtual void showWindow(int nCmdShow) = 0;
	virtual int MessageLoop() = 0;
protected:
	HINSTANCE m_hInst;
	HWND	  m_hWnd;
};

