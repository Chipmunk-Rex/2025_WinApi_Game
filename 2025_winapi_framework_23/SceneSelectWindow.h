#pragma once
#include "BaseWindow.h"
#include <vector>
#include <string>
#include <windows.h>

class SceneSelectWindow : public BaseWindow
{
public:
	SceneSelectWindow();
	~SceneSelectWindow() override;
public:
	int Run(HINSTANCE hInstance, int nCmdShow) override;
	ATOM MyRegisterClass() override;
	void createWindow() override;
	void showWindow(int nCmdShow) override;
	int MessageLoop() override;

	// after Run, caller can get the chosen scene name
	std::wstring GetSelectedSceneName() const;

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnCreate();
	void OnCommand(int id, int code);

private:
	HWND m_hListBox;
	HWND m_hBtnOk;
	HWND m_hBtnCancel;
	std::vector<std::wstring> m_sceneNames;
	int m_selectedIndex; // -1 = none

	static constexpr int IDC_SCENE_LIST = 2001;
	static constexpr int IDC_BTN_OK = 2002;
	static constexpr int IDC_BTN_CANCEL = 2003;
};

