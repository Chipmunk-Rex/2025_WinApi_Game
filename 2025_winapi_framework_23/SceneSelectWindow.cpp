#include "pch.h"
#include "SceneSelectWindow.h"
#include "SceneManager.h"

SceneSelectWindow::SceneSelectWindow()
	: m_hListBox(nullptr)
	, m_hBtnOk(nullptr)
	, m_hBtnCancel(nullptr)
	, m_selectedIndex(-1)
{
}

SceneSelectWindow::~SceneSelectWindow()
{
}

int SceneSelectWindow::Run(HINSTANCE hInstance, int nCmdShow)
{
	this->m_hInst = hInstance;
	this->MyRegisterClass();
	this->createWindow();
	this->showWindow(nCmdShow);

	// populate scene names from SceneManager
	m_sceneNames.clear();
	const auto& scenes = GET_SINGLE(SceneManager)->GetAllScenes();
	for (const auto& kv : scenes)
	{
		m_sceneNames.push_back(kv.first);
	}

	// fill listbox
	if (m_hListBox)
	{
		for (size_t i = 0; i < m_sceneNames.size(); ++i)
		{
			::SendMessageW(m_hListBox, LB_ADDSTRING, 0, (LPARAM)m_sceneNames[i].c_str());
		}
		if (!m_sceneNames.empty())
			::SendMessageW(m_hListBox, LB_SETCURSEL, 0, 0);
	}

	int result = this->MessageLoop();
	// store selected index for caller
	m_selectedIndex = result;
	if (m_selectedIndex >= 0)
		GET_SINGLE(SceneManager)->LoadScene(this->GetSelectedSceneName());

	return result;
}

ATOM SceneSelectWindow::MyRegisterClass()
{
	WNDCLASSEXW wcex = {};

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = SceneSelectWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"SceneSelectWin";
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	return ::RegisterClassExW(&wcex);
}

void SceneSelectWindow::createWindow()
{
	const int winW = 400;
	const int winH = 200;
	int screenX = ::GetSystemMetrics(SM_CXSCREEN);
	int screenY = ::GetSystemMetrics(SM_CYSCREEN);
	int winposx = (screenX - winW) / 2;
	int winposy = (screenY - winH) / 2;

	m_hWnd = ::CreateWindowW(L"SceneSelectWin", L"Select Scene", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		winposx, winposy, winW, winH, nullptr, nullptr, m_hInst, nullptr);

	// 인스턴스 포인터를 GWLP_USERDATA에 저장해서 WndProc에서 인스턴스 접근 가능하게 함
	SetWindowLongPtrW(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

	m_hListBox = CreateWindowW(L"LISTBOX", nullptr, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_BORDER,
		10, 10, 260, 150, m_hWnd, (HMENU)IDC_SCENE_LIST, m_hInst, nullptr);

	m_hBtnOk = CreateWindowW(L"BUTTON", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		280, 30, 100, 30, m_hWnd, (HMENU)IDC_BTN_OK, m_hInst, nullptr);

	m_hBtnCancel = CreateWindowW(L"BUTTON", L"Cancel", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		280, 70, 100, 30, m_hWnd, (HMENU)IDC_BTN_CANCEL, m_hInst, nullptr);
}

void SceneSelectWindow::showWindow(int nCmdShow)
{
	::ShowWindow(m_hWnd, nCmdShow);
	::UpdateWindow(m_hWnd);
}

int SceneSelectWindow::MessageLoop()
{
	MSG msg;
	// 윈도우가 파괴될 때까지 루프 (WM_QUIT 사용하지 않음)
	while (IsWindow(m_hWnd))
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// CPU 낭비 방지용 아주 짧은 대기
			Sleep(1);
		}
	}

	// 창이 닫히면 m_selectedIndex를 반환
	return m_selectedIndex;
}

std::wstring SceneSelectWindow::GetSelectedSceneName() const
{
	if (m_selectedIndex >= 0 && m_selectedIndex < (int)m_sceneNames.size())
		return m_sceneNames[m_selectedIndex];
	return L"";
}

LRESULT CALLBACK SceneSelectWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 인스턴스 포인터 얻기
	SceneSelectWindow* pThis = (SceneSelectWindow*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);

	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDC_BTN_OK:
		{
			HWND list = GetDlgItem(hWnd, IDC_SCENE_LIST);
			int idx = (int)::SendMessageW(list, LB_GETCURSEL, 0, 0);
			if (pThis)
			{
				pThis->m_selectedIndex = (idx != LB_ERR) ? idx : -1;
			}
			// 창만 닫음. PostQuitMessage 절대 사용하지 않음.
			DestroyWindow(hWnd);
			return 0;
		}
		case IDC_BTN_CANCEL:
			if (pThis) pThis->m_selectedIndex = -1;
			DestroyWindow(hWnd);
			return 0;
		}
	}
	break;
	case WM_DESTROY:
		// 아무것도 하지 않음: MessageLoop의 IsWindow 결과로 루프 종료
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}