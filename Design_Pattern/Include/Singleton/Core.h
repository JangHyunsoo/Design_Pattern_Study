#pragma once
#include "../Common.h"

class CCore
{
private:
	CCore() {}
	~CCore() {
		// other single destroy

		ReleaseDC(m_hWnd, m_hDC);
	}

private:
	static CCore* m_pInst;
public:
	static CCore* GetInst() {
		if (m_pInst == nullptr) {
			m_pInst = new CCore;
		}
		return m_pInst;
	}
	static void DestroyInst() {
			SAFE_DELETE(m_pInst); 
	}

private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	HDC m_hDC;
	POSITION m_tRS;
	const wchar_t* m_strName;

private:
	static bool m_bLoop;

public:
	bool Init(HINSTANCE hInst, const wchar_t* strName, int iWidth, int iHeight) {
		this->m_hInst = hInst;

		m_strName = strName;
		m_tRS.x = iWidth;
		m_tRS.y = iHeight;

		MyRegisterClass();

		Create();

		m_hDC = GetDC(m_hWnd);

		// Init Singleton

		return true;
	}

	int Run() {
		MSG msg;

		while (m_bLoop)
		{

			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				Logic();
			}
		}

		return (int)msg.wParam;
	}

private:
	BOOL Create()
	{
		m_hWnd = CreateWindowW(m_strName, m_strName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

		if (!m_hWnd) {
			return FALSE;
		}


		RECT rc = { 0, 0, m_tRS.x, m_tRS.y };

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

		ShowWindow(m_hWnd, SW_SHOW);
		UpdateWindow(m_hWnd);

		return 0;
	}

	void Logic() {

	}

private:
	ATOM MyRegisterClass() {
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW || CS_VREDRAW;
		wcex.lpfnWndProc = CCore::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = m_hInst;
		wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = m_strName;
		wcex.hIconSm = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));

		return RegisterClassExW(&wcex);
	}

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_DESTROY:
			m_bLoop = false;
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		return 0;
	}
};