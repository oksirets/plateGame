// API2.cpp: Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "resource.h"
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
// створення кнопок
#define ID_BUTTON1 1002
#define ID_BUTTON2 1005
#define ID_BUTTON3 1001

static TCHAR szWindowClass[] = _T("winClass"); 
static TCHAR ClassA[] = "winClassA";
static TCHAR szTitle[] = _T("My First Window-program!     URA!!");

HINSTANCE hInst;
HWND hWndM;
HWND** hBtns;
int size = 500;

BOOL CALLBACK DlgProcA(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProcP(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProcGame(HWND, UINT, WPARAM, LPARAM);
BOOL NewWindowClass(WNDPROC Proc, TCHAR szName[], UINT brBackground, UINT icon, UINT cursor, UINT menu);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void createButton(HWND hWnd, int num);
//LRESULT CALLBACK WndProcP(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable
	if (!NewWindowClass(WndProc, szWindowClass, COLOR_WINDOW, IDI_ICON1, IDC_CURSOR1, IDR_MENU1)) return FALSE;
	//if (!NewWindowClass(WndProcP, ClassP, COLOR_WINDOW + 1, IDI_ICON1, IDC_CURSOR2, NULL)) return FALSE;

	

	 hWndM = CreateWindow(szWindowClass,"Way of Ninja",WS_OVERLAPPEDWINDOW|WS_VISIBLE,	60, 60,	648, 527,NULL,	NULL,hInst,	NULL);

	if (!hWndM)
	{
		MessageBox(NULL,_T("Call to CreateWindow failed!"),	_T("Win32 Guided Tour"),NULL);
		return 1;
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) //обробник вікна
{
	static HWND hbutton1, hbutton2, hbutton3;
	COLORREF col;
	switch (message)
	{
	case WM_CREATE:
		hbutton1 = CreateWindow("button", "Рекорди", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 40, 100, 100, 40, hWnd, (HMENU)ID_BUTTON1, hInst, NULL);
		hbutton2 = CreateWindow("button", "Стиль", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,180, 180, 100, 40,hWnd, (HMENU)ID_BUTTON2,hInst, NULL);
		hbutton3 = CreateWindow("button", "Грати",WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,320, 260, 100, 40,hWnd, (HMENU)ID_BUTTON3,hInst, NULL);
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			RECT r;
			GetClientRect(hWnd, &r);
			//SetTextAlign(hdc, TA_CENTER);
			SetBkMode(hdc, TRANSPARENT);
			
			HDC hCompDC;
			HANDLE hBitmap;
			BITMAP bitmap;
			hBitmap = LoadImage(NULL, "bit.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			GetObject(hBitmap, sizeof(BITMAP), &bitmap);
			hCompDC = CreateCompatibleDC(hdc);
			SelectObject(hCompDC, hBitmap);
			StretchBlt(hdc, r.left, r.top, r.right, r.bottom, 
			hCompDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
			DeleteObject(hBitmap);
			DeleteDC(hCompDC);
			EndPaint(hWnd, &ps);
		break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	/*case WM_SIZE:
		int cx = LOWORD(lParam);
		int cy = HIWORD(lParam);
		RECT r;
		GetWindowRect(hWnd, &r);
		MessageBox(hWnd, "Hello", "Hello", MB_OK);
		break;*/
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_QUIT:
			if (MessageBox(hWnd, "Do you want quit?", "Quit", MB_YESNO | MB_ICONHAND)==IDYES)
			PostQuitMessage(0);
			break;
		case ID_INFO_AUTOR:
			/*RECT r;
			//GetWindowRect(hWnd, &r);
			//if (!IsWindow(hWndA))*/
			//hWndA = CreateWindow(ClassA, "Oksana Kukharets", WS_OVERLAPPEDWINDOW | WS_VISIBLE, r.left+20, r.top+105, (r.right-r.left)/2, (r.bottom-r.top)/2, NULL, NULL, hInst, NULL); */
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProcA);
			
			break;
		case ID_INFO_ABOUTPROGRAM:
			/*RECT p;
			GetWindowRect(hWnd, &p);
			if (!IsWindow(hWndP))
				hWndP = CreateWindow(ClassP, "Oksana Kukharets", WS_OVERLAPPEDWINDOW | WS_VISIBLE, p.left + 20, p.top + 105, (p.right - p.left) , (p.bottom - p.top) , NULL, NULL, hInst, NULL);*/
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, DlgProcP);
			break;
		case ID_BUTTON2:
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			if (lParam == -1)
			{
				RECT r;
				GetWindowRect(hWnd, &r);
				pt.x = r.left;
				pt.y = r.top;
			}
			HMENU hMenu, hPopupMenu;
			hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU2));
			hPopupMenu = GetSubMenu(hMenu, 0);
			TrackPopupMenu(hPopupMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
			break;
		case ID_BUTTON3:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, DlgProcGame);
			break;
		case ID_RED:
			col = RGB(255, 0, 0);
			return 1;
			break;
		case ID_GREEN:
			col = RGB(0, 255, 0);
			return 1;
			break;
		case ID_BLACK:
			col = RGB(0, 0, 0);
			return 1;
			break;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}

//LRESULT CALLBACK WndProcA(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//	case WM_DESTROY:
//		//PostQuitMessage(0);
//		break;
//	case WM_LBUTTONDOWN:
//	{
//		int mx = LOWORD(lParam);
//		int my = HIWORD(lParam);
//		RECT r;
//		GetWindowRect(hWnd, &r);
//		MoveWindow(hWnd, r.left + mx, r.top + my, r.right - r.left, r.bottom - r.top, TRUE);
//		break;
//	}
//	
//	case WM_PAINT:
//	{
//		PAINTSTRUCT ps;
//		HDC hdc = BeginPaint(hWnd, &ps);
//		RECT r;
//		GetClientRect(hWnd, &r);
//		//SetTextAlign(hdc, TA_CENTER);
//		SetBkMode(hdc, TRANSPARENT);
//		
//		HDC hCompDC;
//	HANDLE hBitmap;
//	BITMAP bitmap;
//	hBitmap = LoadImage(NULL, "DSC_2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
//		hCompDC = CreateCompatibleDC(hdc);
//		SelectObject(hCompDC, hBitmap);
//		StretchBlt(hdc, r.left, r.top, r.right/2, r.bottom, 
//			hCompDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight,
//			SRCCOPY);
//		DeleteObject(hBitmap);
//		DeleteDC(hCompDC);
//		char* String = "Кухарець Оксана Володимирівна створила гру Шлях Ніндзя у 2018 році. Після виходу гри в маси Оксану запросили працювати в компанію Google, де вона працює фахівцем з інформаційної безпеки.";
//		r.left=r.right /2;
//		DrawText(hdc, String, strlen(String), &r, DT_CENTER | DT_VCENTER| DT_WORDBREAK | DT_EDITCONTROL);
//		EndPaint(hWnd, &ps);
//		break;
//	}
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//		break;
//	}
//
//	return 0;
//}

//LRESULT CALLBACK WndProcP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//	case WM_DESTROY:
//		//PostQuitMessage(0);
//		break;
//	case WM_LBUTTONDOWN:
//	{
//		int mx = LOWORD(lParam);
//		int my = HIWORD(lParam);
//		RECT p;
//		GetWindowRect(hWnd, &p);
//		MoveWindow(hWnd, p.left + mx, p.top + my, p.right - p.left, p.bottom - p.top, TRUE);
//		break;
//	}
//	case WM_PAINT:
//	{
//		PAINTSTRUCT ps;
//		HDC hdc = BeginPaint(hWnd, &ps);
//		RECT p;
//		GetClientRect(hWnd, &p);
//		//SetTextAlign(hdc, TA_CENTER);
//		SetBkMode(hdc, TRANSPARENT);
//
//		HDC hCompDC;
//		HANDLE hBitmap;
//		BITMAP bitmap;
//		hBitmap = LoadImage(NULL, "Kot.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
//		hCompDC = CreateCompatibleDC(hdc);
//		SelectObject(hCompDC, hBitmap);
//		StretchBlt(hdc, p.left, p.bottom/2, p.right, p.bottom,
//			hCompDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight,
//			SRCCOPY);
//		DeleteObject(hBitmap);
//		DeleteDC(hCompDC);
//		char* String = "Необхідно запам'ятати розташування світлих плиточок. Через декілька секунд плитки перевертаються, а гравець по черзі вказує їх. Помилки не допускаються. На подальших рівнях розмір поля збільшується і кількість клітинок, які треба запам'ятати, також.";
//		p.bottom = p.bottom / 2;
//		DrawText(hdc, String, strlen(String), &p, DT_CENTER | DT_VCENTER | DT_WORDBREAK | DT_EDITCONTROL);
//		EndPaint(hWnd, &ps);
//		break;
//	}
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//		break;
//	}
//
//	return 0;
//}



BOOL CALLBACK DlgProcA(HWND hWnd, UINT mess, WPARAM wp, LPARAM lp) //вікно з інформацією про автора
{
	switch (mess)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case IDC_BUTTON1:
			EndDialog(hWnd, 1);
			break;
		}
		return 1;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return 1;
	}
	return 0;
}

BOOL CALLBACK DlgProcP(HWND hWnd, UINT mess, WPARAM wp, LPARAM lp) // вікно з інформацією про програму
{
	switch (mess)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case IDC_BUTTON2:
			EndDialog(hWnd, 1);
			break;
		}
		return 1;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return 1;
	}
	return 0;
}

BOOL CALLBACK DlgProcGame(HWND hWnd, UINT mess, WPARAM wp, LPARAM lp) //вікно з грою
{
	switch (mess)
	{
	case WM_CREATE:
		createButton(hWnd, 2);
		break;
	case WM_COMMAND:
		switch (wp)
		{
		case IDC_BUTTON1:
			
			break;
		}
		return 1;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return 1;
	}
	return 0;
}

void createButton(HWND hWnd, int num)
{
	hBtns = new HWND*[num];
	for (int i = 0; i < num; i++)
	{
		hBtns[i]=new HWND [num];
	}

	int x = 0;
	int y = 0;
	int flag = 0;
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			hBtns [i] [j]=CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, x, y, size/num, size / num, hWnd, (HMENU)flag, hInst, NULL);
			x += size / num;
			flag + 1;
		}
		y += size / num;
		x = 0;
		flag = 0;
		flag = (i + 1) * 10;
	}
}

BOOL NewWindowClass(WNDPROC Proc, TCHAR szName[], UINT brBackground, UINT icon, UINT cursor, UINT menu)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Proc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = LoadIcon(hInst, (LPCSTR)icon);
	wcex.hCursor = LoadCursor(hInst, (LPCSTR)cursor);
	wcex.hbrBackground = (HBRUSH)(brBackground + 1);
	wcex.lpszMenuName = (LPCSTR)menu;
	wcex.lpszClassName = szName;
	wcex.hIconSm = LoadIcon(hInst, (LPCSTR)icon);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, ("Call to RegisterClassEx failed!"), szName, NULL);
		return 0;
	}
	else return 1;
}