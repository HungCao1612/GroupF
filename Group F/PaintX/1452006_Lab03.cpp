// 1452006_Lab02.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1452006_Lab03.h"
#include "Windowsx.h"
#include <CommCtrl.h>
void errhandler(LPCTSTR sz, HWND hwnd);

#define MAX_LOADSTRING 100
#define ID_TIMER1	123123
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
POINT p1, p2, p2_ancien;
HBITMAP hBitmap;
BOOL enTrainDessin;
DWORD rgbCurrent2;
HBRUSH      NewBrush;
char AppCaption[40];

const int NUMBUTTONS = 7;

int mode; //mode de dessin==> 0 pour ligne, 1 pour libre
// Global Variables:

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
VOID				DrawLine(HDC hdc);
VOID				FreeDraw(HDC hdc);
VOID				DrawRec(HDC hdc);
VOID				DrawSqua(HDC hdc);
VOID				DrawRound(HDC hdc);
VOID				DrawEll(HDC hdc);
VOID				DrawLineProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
VOID				FreeDrawProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
VOID				DrawRecProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
VOID				DrawSquaProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
VOID				DrawRoundProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
VOID				DrawEllProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
VOID BackgroudColorDialog(HWND hWnd);
VOID PenBrushDemo(HDC hdc);
VOID Pen(HDC hdc, int size, int R, int G, int B);
int size, R, G, B, Size, color;
VOID FontChooseFont(HWND hwnd, HDC hdc);
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY1452006_LAB03, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1452006_LAB03));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}
void Brush_Color(HWND hWnd)
{
	CHOOSECOLOR cc1;
	static COLORREF acrCustClr1[16];
	HBRUSH hbrush1;
	ZeroMemory(&cc1, sizeof(cc1));
	cc1.lStructSize = sizeof(cc1);
	cc1.hwndOwner = hWnd;
	cc1.lpCustColors = (LPDWORD)acrCustClr1;
	cc1.rgbResult = rgbCurrent2;
	cc1.Flags = CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&cc1) == TRUE)
	{
		hbrush1 = CreateSolidBrush(cc1.rgbResult);
		rgbCurrent2 = cc1.rgbResult;
	}
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1452006_LAB03));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MY1452006_LAB03);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	INITCOMMONCONTROLSEX InitCtrlEx;

	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrlEx.dwICC = ICC_BAR_CLASSES;
	InitCommonControlsEx(&InitCtrlEx);

	TBBUTTON tbrButtons[7];
	tbrButtons[0].iBitmap = 0;
	tbrButtons[0].idCommand = ID_FILE_SAVE;
	tbrButtons[0].fsState = TBSTATE_ENABLED;
	tbrButtons[0].fsStyle = TBSTYLE_BUTTON;
	tbrButtons[0].dwData = 0L;
	tbrButtons[0].iBitmap = 0;
	tbrButtons[0].iString = 0;

	tbrButtons[1].iBitmap = 1;
	tbrButtons[1].idCommand = ID_LINE_STRAIGHTLINE;
	tbrButtons[1].fsState = TBSTATE_ENABLED;
	tbrButtons[1].fsStyle = TBSTYLE_BUTTON;
	tbrButtons[1].dwData = 0L;
	tbrButtons[1].iString = 0;

	tbrButtons[2].iBitmap = 2;
	tbrButtons[2].idCommand = ID_SHAPE_RECTANGLE;
	tbrButtons[2].fsState = TBSTATE_ENABLED;
	tbrButtons[2].fsStyle = TBSTYLE_SEP;
	tbrButtons[2].dwData = 0L;
	tbrButtons[2].iString = 0;

	tbrButtons[3].iBitmap = 3;
	tbrButtons[3].idCommand = ID_SHAPE_ELLIPSE;
	tbrButtons[3].fsState = TBSTATE_ENABLED;
	tbrButtons[3].fsStyle = TBSTYLE_BUTTON;
	tbrButtons[3].dwData = 0L;
	tbrButtons[3].iString = 0;

	tbrButtons[4].iBitmap = 4;
	tbrButtons[4].idCommand = ID_SHAPE_SQUARE;
	tbrButtons[4].fsState = TBSTATE_ENABLED;
	tbrButtons[4].fsStyle = TBSTYLE_BUTTON;
	tbrButtons[4].dwData = 0L;
	tbrButtons[4].iString = 0;

	tbrButtons[5].iBitmap = 5;
	tbrButtons[5].idCommand = ID_LINE_FREESTYLE;
	tbrButtons[5].fsState = TBSTATE_ENABLED;
	tbrButtons[5].fsStyle = TBSTYLE_BUTTON;
	tbrButtons[5].dwData = 0L;
	tbrButtons[5].iString = 0;

	tbrButtons[6].iBitmap = 6;
	tbrButtons[6].idCommand = ID_SHAPE_RECTANGLE;
	tbrButtons[6].fsState = TBSTATE_ENABLED;
	tbrButtons[6].fsStyle = TBSTYLE_BUTTON;
	tbrButtons[6].dwData = 0L;
	tbrButtons[6].iString = 0;


	HWND hWndToolbar;
	hWndToolbar = CreateToolbarEx(hWnd,
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		IDB_BITMAP1,
		NUMBUTTONS,
		hInst,
		IDB_BITMAP1,
		tbrButtons,
		NUMBUTTONS,
		16, 16, 16, 16,
		sizeof(TBBUTTON));

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp)
{
	BITMAP bmp;
	PBITMAPINFO pbmi;
	WORD    cClrBits;
	// Retrieve the bitmap color format, width, and height.  
	if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
		errhandler(TEXT("GetObject"), hwnd);
	// Convert the color format to a count of bits.  
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
	if (cClrBits == 1)
		cClrBits = 1;
	else if (cClrBits <= 4)
		cClrBits = 4;
	else if (cClrBits <= 8)
		cClrBits = 8;
	else if (cClrBits <= 16)
		cClrBits = 16;
	else if (cClrBits <= 24)
		cClrBits = 24;
	else cClrBits = 32;
	// Allocate memory for the BITMAPINFO structure. (This structure  
	// contains a BITMAPINFOHEADER structure and an array of RGBQUAD  
	// data structures.)  
	if (cClrBits < 24)
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
		sizeof(BITMAPINFOHEADER)+
		sizeof(RGBQUAD)* (1 << cClrBits));
	// There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel 
	else
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
		sizeof(BITMAPINFOHEADER));
	// Initialize the fields in the BITMAPINFO structure.  
	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits);
	// If the bitmap is not compressed, set the BI_RGB flag.  
	pbmi->bmiHeader.biCompression = BI_RGB;
	// Compute the number of bytes in the array of color  
	// indices and store the result in biSizeImage.  
	// The width must be DWORD aligned unless the bitmap is RLE 
	// compressed. 
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits + 31) & ~31) / 8
		* pbmi->bmiHeader.biHeight;
	// Set biClrImportant to 0, indicating that all of the  
	// device colors are important.  
	pbmi->bmiHeader.biClrImportant = 0;
	return pbmi;
}
void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi,
	HBITMAP hBMP, HDC hDC)
{
	HANDLE hf;                 // file handle  
	BITMAPFILEHEADER hdr;       // bitmap file-header  
	PBITMAPINFOHEADER pbih;     // bitmap info-header  
	LPBYTE lpBits;              // memory pointer  
	DWORD dwTotal;              // total count of bytes  
	DWORD cb;                   // incremental count of bytes  
	BYTE *hp;                   // byte pointer  
	DWORD dwTmp;
	pbih = (PBITMAPINFOHEADER)pbi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);
	if (!lpBits)
		errhandler(_T("GlobalAlloc"), hwnd);
	// Retrieve the color table (RGBQUAD array) and the bits  
	// (array of palette indices) from the DIB.  
	if (!GetDIBits(hDC, hBMP, 0, (WORD)pbih->biHeight, lpBits, pbi,
		DIB_RGB_COLORS))
	{
		errhandler(_T("GetDIBits"), hwnd);
	}
	// Create the .BMP file.  
	hf = CreateFile(pszFile,
		GENERIC_READ | GENERIC_WRITE,
		(DWORD)0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);
	if (hf == INVALID_HANDLE_VALUE)
		errhandler(_T("CreateFile"), hwnd);
	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
	// Compute the size of the entire file.  
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER)+
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD)+pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	// Compute the offset to the array of color indices.  
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER)+
		pbih->biSize + pbih->biClrUsed
		* sizeof (RGBQUAD);
	// Copy the BITMAPFILEHEADER into the .BMP file.  
	if (!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL))
	{
		errhandler(_T("WriteFile"), hwnd);
	}
	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file.  
	if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
		+pbih->biClrUsed * sizeof (RGBQUAD),
		(LPDWORD)&dwTmp, (NULL)))
		errhandler(_T("WriteFile"), hwnd);
	// Copy the array of color indices into the .BMP file.  
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL))
		errhandler(_T("WriteFile"), hwnd);
	// Close the .BMP file.  
	if (!CloseHandle(hf))
		errhandler(_T("CloseHandle"), hwnd);
	// Free memory.  
	GlobalFree((HGLOBAL)lpBits);
}
void errhandler(LPCTSTR sz, HWND hwnd)
{
	MessageBox(hwnd, sz, _T("Error"), MB_ICONERROR);
	PostQuitMessage(0);
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
INT_PTR CALLBACK Brush_Style(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		switch (LOWORD(wParam))
		{
		case IDC_RADIO1: // ID nút Brush Color
			Brush_Color(hDlg);
			NewBrush = CreateSolidBrush(rgbCurrent2);
			break;

		case IDC_RADIO2: // ID nút Delete Brush vẽ lại bình thường
			DeleteObject(NewBrush);
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	//HDC hdc;
	WCHAR  bu[1024]; cin.get();
	char name[100];


	fstream f;
	f.open("input.txt", ios::in);

	// 3. Đọc dữ liệu từ file vào string data
	string data;
	getline(f, data);
	//name = (string)data;
	// 4. Đóng file
	f.close();
	strcpy_s(name, data.c_str());
	cin.get();
	string name1;
	HDC hdc = GetDC(hWnd);
	RECT rect;
	GetClientRect(hWnd, &rect);
	switch (mode)
	{
	case 0:
		FreeDrawProc(hWnd, message, wParam, lParam);
		break;
	case 1:
		DrawLineProc(hWnd, message, wParam, lParam);
		break;
	case 3:
		DrawRecProc(hWnd, message, wParam, lParam);
		break;
	case 4:
		DrawEllProc(hWnd, message, wParam, lParam);
		break;
	case 5:
		DrawSquaProc(hWnd, message, wParam, lParam);
		break;
	case 6:
		DrawRoundProc(hWnd, message, wParam, lParam);
		break;
	}

	switch (message)
	{
	case WM_CREATE:
	{
		p1.x = p1.y = 0;
		p2 = p1;
		mode = 1;
		size = PS_SOLID;
		R = 0;
		G = 0;
		B = 0;
		enTrainDessin = FALSE;

		//Tạo bitmap
		HDC hdc = GetDC(hWnd);
		RECT rect;
		GetClientRect(hWnd, &rect);
		//Tạo ra một bitmap tương thích với DC màn hình
		hBitmap = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);

		//Tô background cho bitmap
		//Tạo memory dc để tương tác với Bitmap
		HDC memDC = CreateCompatibleDC(hdc);
		SelectObject(memDC, hBitmap);
		HBRUSH hBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
		FillRect(memDC, &rect, hBrush);
		DeleteObject(hBrush);
		DeleteDC(memDC);
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_DRAW_PEN:
			mode = 2;
			RECT rect;
			GetWindowRect(hWnd, &rect);
			InvalidateRect(hWnd, &rect, true);
			UpdateWindow(hWnd);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_FORMAT_FONT:
			cin >> name1;
			SelectObject(hdc, hBitmap);
			IsWindowEnabled(hWnd);

			LPCTSTR lpStrings;
			lpStrings = (LPCTSTR)name;
			TextOut(hdc, 50, 32, lpStrings, 11);
			//FontChooseFont ( hWnd);


			FontChooseFont(hWnd, hdc);
			break;
		case ID_FILE_EXIT:
			if (MessageBox(hWnd, _T("Are you sure to close?"), _T("Confirm close"), MB_OKCANCEL | MB_ICONQUESTION) == 1)
			{
				DestroyWindow(hWnd);
			}
			break;
		case ID_FORMAT_BRUSH:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DLGFIRST), hWnd, Brush_Style);
			break;
		case ID_LINE_FREESTYLE:
			mode = 0;
			break;
		case ID_LINE_STRAIGHTLINE:
			mode = 1;
			break;
		case ID_SHAPE_RECTANGLE:
			mode = 3;
			break;
		case ID_SHAPE_ELLIPSE:
			mode = 4;
			break;
		case ID_SHAPE_SQUARE:
			mode = 5;
			break;
		case ID_FILE_SAVE:
			mode = 8;
			{
				HDC hdc = GetDC(hWnd);
			OPENFILENAME ofn1;
			ZeroMemory(&ofn1, sizeof(ofn1));
			char szFileName[MAX_PATH];
			ZeroMemory(szFileName, MAX_PATH);
			ofn1.lStructSize = sizeof(ofn1);
			ofn1.hwndOwner = NULL;
			ofn1.lpstrFilter = _T("Bmp Files(*.bmp)\0 * .bmp\0Text Files(*.txt)\0 * .txt\0All Files(*.*)\0 * .*\0");
			ofn1.lpstrFile = (LPWSTR)szFileName;
			ofn1.nMaxFile = MAX_PATH;
			ofn1.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			ofn1.lpstrDefExt = (LPCWSTR)L"bmp";
			GetSaveFileName(&ofn1);
			PBITMAPINFO pbi = CreateBitmapInfoStruct(hWnd, hBitmap);
			CreateBMPFile(hWnd, ofn1.lpstrFile, pbi, hBitmap, hdc);
			}
			break;
		case ID_FILE_OPEN:
			mode = 7;
			OPENFILENAME ofn;
			TCHAR szFile[260];

			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;

			ofn.lpstrFile = szFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = _T("All Files *.*\0*.*\0Text Files *.txt\0*.TXT\0 Doc Files\0*.TXT;*.DOC;*.BAK\0");
			ofn.nFilterIndex = 1;
			ofn.lpstrInitialDir = _T("C:\\");
			ofn.lpstrTitle = _T("My Application - Open file");
			ofn.lpstrDefExt = _T("txt");
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			// Display the Open dialog box. 
			if (GetOpenFileName(&ofn) == TRUE)
			{
				hBitmap = (HBITMAP)LoadImage(NULL, ofn.lpstrFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				HDC hdc = GetDC(hWnd);
				HDC memDC = CreateCompatibleDC(hdc);

				// Select the new bitmap
				SelectObject(memDC, hBitmap);
				RECT rect;
				GetClientRect(hWnd, &rect);
				BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, memDC, 0, 0, SRCCOPY);

				DeleteObject(memDC);
			}
			break;
		case ID_SHAPE_ROUND:
			mode = 6;
			break;
		case ID_WIDTH_X1:
		{
			Size = 1;
			break;
		}
		case ID_WIDTH_X3:
		{
			Size = 2;
			break;
		}
		case ID_WIDTH_X6:
		{
			Size = 3;
			break;
		}
		case ID_COLOR_RED:
		{
			color = 1;
			break;
		}
		case ID_COLOR_GREEN:
		{
			color = 2;
			break;
		}
		case ID_COLOR_BLUE:
		{
			color = 3;
			break;
		}
		case ID_COLOR_ORIGINAL:
		{
			color = 4;
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
		break;
	case WM_RBUTTONDOWN:
		SetTimer(hWnd, ID_TIMER1, 1000, NULL);

		break;
	case WM_RBUTTONDBLCLK:
		KillTimer(hWnd, ID_TIMER1);
		//effacer l'ecran
		SendMessage(hWnd, WM_ERASEBKGND, (WPARAM)GetDC(hWnd), (LPARAM) nullptr);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case ID_TIMER1:
			KillTimer(hWnd, ID_TIMER1);
			mode = (mode + 1) % 2;
			MessageBox(hWnd, _T("Mode de dessin change"), _T("Notifcation"), MB_OK);
			break;
		}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		// TODO: Add any drawing code that uses hdc here...
		HDC hdc = BeginPaint(hWnd, &ps);
		//Vẽ bitmap ra màn hình trước
		HDC memDC = CreateCompatibleDC(hdc);
		SelectObject(memDC, hBitmap);
		RECT rect;
		GetClientRect(hWnd, &rect);
		BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, memDC, 0, 0, SRCCOPY);
		switch (mode)
		{
		case 0:
			//Vẽ tự do thì ta vẽ luôn trên màn hình và bitmap
			FreeDraw(memDC);
			FreeDraw(hdc);
			break;
		case 1:
			//Vẽ đường thẳng thì ta chỉ vẽ lên màn hình
			DrawLine(hdc);
			break;
		case 2:
			PenBrushDemo(memDC);
			PenBrushDemo(hdc);
			break;
		case 3:
			DrawRec(hdc);
			break;
		case 4:
			DrawEll(hdc);
			break;
		case 5:
			DrawSqua(hdc);
			break;
		case 6:
			DrawRound(hdc);
			break;
		}

		DeleteObject(memDC);
		//SelectObject(hdc, oldPen);

		EndPaint(hWnd, &ps);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

VOID DrawLine(HDC hdc)
{
	Pen(hdc, size, R, G, B);
	if (enTrainDessin == TRUE)
	{

		MoveToEx(hdc, p1.x, p1.y, NULL);
		LineTo(hdc, p2.x, p2.y);


	}
}

VOID FreeDraw(HDC hdc)
{
	Pen(hdc, size, R, G, B);
	if (enTrainDessin == TRUE)
	{
		MoveToEx(hdc, p1.x, p1.y, NULL);
		LineTo(hdc, p2.x, p2.y);
		p1 = p2;
	}
}
VOID DrawRec(HDC hdc)
{
	Pen(hdc, size, R, G, B);
	if (enTrainDessin == TRUE)
	{

		MoveToEx(hdc, p1.x, p1.y, NULL);
		//LineTo(hdc, p2.x, p2.y);
		Rectangle(hdc, p1.x, p1.y, p2.x, p2.y);
		HRGN hRegion = CreateRectRgn(p1.x, p1.y, p2.x, p2.y);
		FillRgn(hdc, hRegion, NewBrush);
	}
}
VOID DrawEll(HDC hdc)
{
	Pen(hdc, size, R, G, B);
	if (enTrainDessin == TRUE)
	{

		MoveToEx(hdc, p1.x, p1.y, NULL);
		Ellipse(hdc, p1.x, p1.y, p2.x, p2.y);
		HRGN hRegion = CreateRectRgn(p1.x, p1.y, p2.x, p2.y);
		FillRgn(hdc, hRegion, NewBrush);
	}
}
VOID DrawRound(HDC hdc)
{
	Pen(hdc, size, R, G, B);
	if (enTrainDessin == TRUE)
	{

		MoveToEx(hdc, p1.x, p1.y, NULL);
		int left = min(p1.x, p2.x);
		int right = max(p1.x, p2.x);
		int top = min(p1.y, p2.y);
		int botton = max(p1.y, p2.y);
		int length = min(abs(p1.x - p2.x), abs(p1.y - p2.y));
		if (p2.x < p1.x)
			p1.x = right - length;
		if (p2.x >= p1.x)
			p2.x = left + length;
		if (p2.y < p1.y)
			p1.y = botton - length;
		if (p2.y >= p1.y)
			p2.y = top + length;
		Ellipse(hdc, p1.x, p1.y, p2.x, p2.y);
		HRGN hRegion = CreateRectRgn(p1.x, p1.y, p2.x, p2.y);
		FillRgn(hdc, hRegion, NewBrush);
	}
}
VOID DrawSqua(HDC hdc)
{
	Pen(hdc, size, R, G, B);
	if (enTrainDessin == TRUE)
	{

		MoveToEx(hdc, p1.x, p1.y, NULL);
		int left = min(p1.x, p2.x);
		int right = max(p1.x, p2.x);
		int top = min(p1.y, p2.y);
		int botton = max(p1.y, p2.y);
		int length = min(abs(p1.x - p2.x), abs(p1.y - p2.y));
		if (p2.x < p1.x)
			p1.x = right - length;
		if (p2.x >= p1.x)
			p2.x = left + length;
		if (p2.y < p1.y)
			p1.y = botton - length;
		if (p2.y >= p1.y)
			p2.y = top + length;
		Rectangle(hdc, p1.x, p1.y, p2.x, p2.y);
		HRGN hRegion = CreateRectRgn(p1.x, p1.y, p2.x, p2.y);
		FillRgn(hdc, hRegion, NewBrush);
	}
}
VOID DrawLineProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT windowRect;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		p1.x = GET_X_LPARAM(lParam);
		p1.y = GET_Y_LPARAM(lParam);
		p2_ancien = p2 = p1;
		enTrainDessin = TRUE;
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (wParam&MK_LBUTTON)
		{
			p2.x = GET_X_LPARAM(lParam);
			p2.y = GET_Y_LPARAM(lParam);
			GetWindowRect(hWnd, &windowRect);
			InvalidateRect(hWnd, &windowRect, FALSE);
			UpdateWindow(hWnd);
		}
		break;
	}
	case WM_LBUTTONUP:

		//Tiến hành cho vẽ lên bitmap
		HDC hdc = GetDC(hWnd);
		HDC memDC = CreateCompatibleDC(hdc);
		SelectObject(memDC, hBitmap);
		DrawLine(memDC);
		DeleteObject(memDC);
		ReleaseDC(hWnd, hdc);

		enTrainDessin = FALSE;
		break;
	}
}

VOID FreeDrawProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT windowRect;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		p1.x = GET_X_LPARAM(lParam);
		p1.y = GET_Y_LPARAM(lParam);
		p2 = p1;
		enTrainDessin = TRUE;
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (wParam&MK_LBUTTON)
		{

			p2.x = GET_X_LPARAM(lParam);
			p2.y = GET_Y_LPARAM(lParam);
			GetWindowRect(hWnd, &windowRect);
			InvalidateRect(hWnd, &windowRect, FALSE);
			UpdateWindow(hWnd);
		}
		break;
	}
	case WM_LBUTTONUP:
		enTrainDessin = FALSE;
		break;


	}
}
VOID DrawRecProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT windowRect;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		p1.x = GET_X_LPARAM(lParam);
		p1.y = GET_Y_LPARAM(lParam);
		p2_ancien = p2 = p1;
		enTrainDessin = TRUE;
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (wParam&MK_LBUTTON)
		{
			p2.x = GET_X_LPARAM(lParam);
			p2.y = GET_Y_LPARAM(lParam);
			GetWindowRect(hWnd, &windowRect);
			InvalidateRect(hWnd, &windowRect, FALSE);
			UpdateWindow(hWnd);
		}
		break;
	}
	case WM_LBUTTONUP:

		//Tiến hành cho vẽ lên bitmap
		HDC hdc = GetDC(hWnd);
		HDC memDC = CreateCompatibleDC(hdc);
		SelectObject(memDC, hBitmap);
		DrawRec(memDC);
		DeleteObject(memDC);
		ReleaseDC(hWnd, hdc);

		enTrainDessin = FALSE;
		break;
	}
}
VOID DrawRoundProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT windowRect;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		p1.x = GET_X_LPARAM(lParam);
		p1.y = GET_Y_LPARAM(lParam);
		p2_ancien = p2 = p1;
		enTrainDessin = TRUE;
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (wParam&MK_LBUTTON)
		{
			p2.x = GET_X_LPARAM(lParam);
			p2.y = GET_Y_LPARAM(lParam);
			GetWindowRect(hWnd, &windowRect);
			InvalidateRect(hWnd, &windowRect, FALSE);
			UpdateWindow(hWnd);
		}
		break;
	}
	case WM_LBUTTONUP:

		//Tiến hành cho vẽ lên bitmap
		HDC hdc = GetDC(hWnd);
		HDC memDC = CreateCompatibleDC(hdc);
		SelectObject(memDC, hBitmap);
		DrawRound(memDC);
		DeleteObject(memDC);
		ReleaseDC(hWnd, hdc);

		enTrainDessin = FALSE;
		break;
	}
}

VOID DrawSquaProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT windowRect;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		p1.x = GET_X_LPARAM(lParam);
		p1.y = GET_Y_LPARAM(lParam);
		p2_ancien = p2 = p1;
		enTrainDessin = TRUE;
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (wParam&MK_LBUTTON)
		{
			p2.x = GET_X_LPARAM(lParam);
			p2.y = GET_Y_LPARAM(lParam);
			GetWindowRect(hWnd, &windowRect);
			InvalidateRect(hWnd, &windowRect, FALSE);
			UpdateWindow(hWnd);
		}
		break;
	}
	case WM_LBUTTONUP:

		//Tiến hành cho vẽ lên bitmap
		HDC hdc = GetDC(hWnd);
		HDC memDC = CreateCompatibleDC(hdc);
		SelectObject(memDC, hBitmap);
		DrawSqua(memDC);
		DeleteObject(memDC);
		ReleaseDC(hWnd, hdc);

		enTrainDessin = FALSE;
		break;
	}
}

VOID DrawEllProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT windowRect;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		p1.x = GET_X_LPARAM(lParam);
		p1.y = GET_Y_LPARAM(lParam);
		p2_ancien = p2 = p1;
		enTrainDessin = TRUE;
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (wParam&MK_LBUTTON)
		{
			p2.x = GET_X_LPARAM(lParam);
			p2.y = GET_Y_LPARAM(lParam);
			GetWindowRect(hWnd, &windowRect);
			InvalidateRect(hWnd, &windowRect, FALSE);
			UpdateWindow(hWnd);
		}
		break;
	}
	case WM_LBUTTONUP:

		//Tiến hành cho vẽ lên bitmap
		HDC hdc = GetDC(hWnd);
		HDC memDC = CreateCompatibleDC(hdc);
		SelectObject(memDC, hBitmap);
		DrawEll(memDC);
		DeleteObject(memDC);
		ReleaseDC(hWnd, hdc);

		enTrainDessin = FALSE;
		break;
	}
}

VOID PenBrushDemo(HDC hdc)
{
	HPEN hPen = CreatePen(PS_DASHDOT, 3, RGB(255, 0, 255));
	SelectObject(hdc, hPen);
	MoveToEx(hdc, 100, 100, NULL);
	LineTo(hdc, 200, 200);
	Rectangle(hdc, 100, 200, 300, 300);
	Ellipse(hdc, 100, 200, 300, 300);
	HRGN hRegion = CreateEllipticRgn(100, 200, 300, 300);
	HBRUSH hbrush = CreateSolidBrush(RGB(23, 100, 40));
	FillRgn(hdc, hRegion, hbrush);
	Ellipse(hdc, 100, 200, 300, 300);
}
//
//
//
//
//Pen Size & Color
VOID Pen(HDC hdc, int size, int R, int G, int B)
{
	switch (Size)
	{
	case 1:
		size = PS_DASH;
		break;
	case 2:
		size = 3;
		break;
	case 3:
		size = 6;
		break;
	}
	switch (color)
	{
	case 1:
		R = 255;
		G = 0;
		B = 0;
		break;
	case 2:
		R = 0;
		G = 255;
		B = 0;
		break;
	case 3:
		R = 0;
		G = 0;
		B = 255;
		break;
	case 4:
		R = 0;
		G = 0;
		B = 0;
		break;
	}
	HPEN hPen = CreatePen(PS_SOLID, size, RGB(R, G, B));
	SelectObject(hdc, hPen);
}
//
//
//
//Chọn Font

VOID FontChooseFont(HWND hwnd, HDC hdc)
{
	//HDC hdc = GetDC(hwnd);                 // display device context of owner window

	CHOOSEFONT cf;            // common dialog box structure
	static LOGFONT lf;        // logical font structure
	static DWORD rgbCurrent;  // current text color
	HFONT hfont = nullptr, hfontPrev;
	DWORD rgbPrev;
	HWND hwndActiveEdit = nullptr, hwndEdit = nullptr;
	HFONT hFontNew;
	RECT rect;
	SelectObject(hdc, hfont);
	// Initialize CHOOSEFONT
	ZeroMemory(&cf, sizeof(cf));
	cf.lStructSize = sizeof (cf);
	cf.hwndOwner = hwnd;
	cf.lpLogFont = &lf;
	cf.rgbColors = rgbCurrent;
	cf.Flags = CF_SCREENFONTS | CF_EFFECTS;


	rgbCurrent = cf.rgbColors;
	if (ChooseFont(&cf) == TRUE){
		hfont = CreateFontIndirect(cf.lpLogFont);
		SelectObject(hdc, hfont);
		rgbCurrent = cf.rgbColors;
		rgbPrev = SetTextColor(hdc, rgbCurrent);
	}

	//   return ChooseFont (&cf);
}
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

