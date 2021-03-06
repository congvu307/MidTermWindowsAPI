// DoAnGK.cpp : Defines the entry point for the application.
#include<iostream>
#include "stdafx.h"
#include <string>
#include "DoAnGK.h"
#include <commctrl.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
using namespace std;
#define MAX_LOADSTRING 100
//hàm kiểm tra nếu 2 chuổi bằng nhau thì thêm vào vector
void addNum(wchar_t *temp1, wchar_t *temp2,int temp,int &sum) {
	if (_wcsicmp(temp1, temp2) == 0) {
		sum += temp;
	}
}

bool IsNumber(WCHAR *a) {
	for (int i = 0; i < wcslen(a); i++) {
		if ((a[i] < 48) || (a[i] > 57)) return false;
	}
	return true;
}
class Cdata {
public:
	wchar_t *TypeOfData;
	wchar_t *ContentOfData;
	wchar_t *PriceOfData;
};
class Cdata_Temp {
public:
	wstring x;
	wstring y;
	wstring z;
};


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DOANGK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DOANGK));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DOANGK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DOANGK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
     50, 50, 500, 700, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;
int AllPrice = 0, Sum[6] = { 0 };
wchar_t temp22[200];
int NumberOfData;
wchar_t temp_Num[30];
WCHAR* bufferKQ2 =  new WCHAR[255];
string string_temp;
wifstream fileinput;
wofstream fileoutput;
vector<Cdata> AllOfData;
Cdata temp_data;
int tempPrice = 0;
bool check = TRUE;
std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
HWND type,content,price, temp,listview, button,Tongtien ;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
    switch (message)
    {
	case WM_CREATE:
		{
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		fileinput.open("save.txt");
		fileinput.imbue(loc);
		fileinput >>temp_Num;
		NumberOfData = _wtoi(temp_Num);//tổng số chi tiêu
		
		Cdata_Temp *temp_wstring = new Cdata_Temp[NumberOfData];
		for (int i = 0; i < NumberOfData; i++) {
			getline(fileinput, temp_wstring[i].x);
			temp_data.TypeOfData  = const_cast<wchar_t*>(temp_wstring[i].x.c_str());
			getline(fileinput, temp_wstring[i].y);
			temp_data.ContentOfData = const_cast<wchar_t*>(temp_wstring[i].y.c_str());
			getline(fileinput, temp_wstring[i].z);
			temp_data.PriceOfData = const_cast<wchar_t*>(temp_wstring[i].z.c_str());
			AllOfData.push_back(temp_data);
			
		}	

		for (int i = 0; i < wcslen(AllOfData[0].TypeOfData) - 1 ; i++) {
			AllOfData[0].TypeOfData[i] = AllOfData[0].TypeOfData[i + 1];
		}
		AllOfData[0].TypeOfData[wcslen(AllOfData[0].TypeOfData) - 1] = '\0';
		for (int i = 0; i < NumberOfData; i++) {
			tempPrice = _wtoi(AllOfData[i].PriceOfData)	;
			AllPrice += tempPrice;
			addNum(AllOfData[i].TypeOfData, L"Ăn Uống", tempPrice,Sum[0]);
			addNum(AllOfData[i].TypeOfData, L"Di Chuyển",  tempPrice, Sum[1]);
			addNum(AllOfData[i].TypeOfData, L"Nhà Cửa", tempPrice, Sum[2]);
			addNum(AllOfData[i].TypeOfData, L"Xe Cộ",  tempPrice, Sum[3]);
			addNum(AllOfData[i].TypeOfData, L"Nhu Yếu Phẩm",  tempPrice, Sum[4]);
			addNum(AllOfData[i].TypeOfData, L"Dịch Vụ",  tempPrice, Sum[5]);
		}
		
		INITCOMMONCONTROLSEX icex;
		WCHAR *x[] = { L"Ăn Uống", L"Di Chuyển", L"Nhà Cửa",L"Xe Cộ", L"Nhu Yếu Phẩm",L"Dịch Vụ" };
			LOGFONT lf;
			GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);

			HFONT hFont1 = CreateFont(40,20,
				lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
				lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
				lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
				lf.lfPitchAndFamily, lf.lfFaceName);

			HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
			lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
			lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
			lf.lfPitchAndFamily, lf.lfFaceName);

			temp = CreateWindowEx(0, L"STATIC", L"Quản lý chi tiêu", WS_CHILD | WS_VISIBLE | SS_CENTER
				, 70, 30,350,40, hWnd, NULL, hInst, NULL);
			SendMessage(temp, WM_SETFONT, WPARAM(hFont1), TRUE);

			temp = CreateWindowEx(0, L"STATIC", L"Loại chi tiêu: ", WS_CHILD | WS_VISIBLE | SS_CENTER
				,30, 110, 120, 24, hWnd, NULL, hInst, NULL);
			SendMessage(temp, WM_SETFONT, WPARAM(hFont), TRUE);


			//COMBOBOX
			type = CreateWindowEx(0, L"COMBOBOX", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST
			, 180, 110, 200, 100, hWnd, NULL, hInst, NULL);

			//THem chuoi vao combobox
			for (int i = 0; i < 5; i++) {
				SendMessage(type, CB_ADDSTRING, 0, (LPARAM)x[i]);
			}
			SendMessage(type, WM_SETFONT, WPARAM(hFont), TRUE);

			temp = CreateWindowEx(0, L"STATIC", L"Nội Dung: ", WS_CHILD | WS_VISIBLE | SS_CENTER
				, 30, 150, 120, 24, hWnd, NULL, hInst, NULL);
			SendMessage(temp, WM_SETFONT, WPARAM(hFont), TRUE);

			temp = CreateWindowEx(0, L"STATIC", L"VNĐ ", WS_CHILD | WS_VISIBLE | SS_CENTER
				, 380, 190, 40, 24, hWnd, NULL, hInst, NULL);
			SendMessage(temp, WM_SETFONT, WPARAM(hFont), TRUE);

			content = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER 
				, 180, 150, 200, 24, hWnd, NULL, hInst, NULL);
			SendMessage(content, WM_SETFONT, WPARAM(hFont), TRUE);

			temp = CreateWindowEx(0, L"STATIC", L"Số tiền: ", WS_CHILD | WS_VISIBLE | SS_CENTER
				, 30, 190, 120, 24, hWnd, NULL, hInst, NULL);
			SendMessage(temp, WM_SETFONT, WPARAM(hFont), TRUE);

			temp = CreateWindowEx(0, L"STATIC", L"Ăn Uống ", WS_CHILD | WS_VISIBLE | SS_CENTER
				, 55, 472, 50, 24, hWnd, NULL, hInst, NULL);
			SendMessage(temp, WM_SETFONT, WPARAM(hFont), TRUE);

			temp = CreateWindowEx(0, L"STATIC", L"Di Chuyển ", WS_CHILD | WS_VISIBLE | SS_CENTER
				, 215, 472, 50, 24, hWnd, NULL, hInst, NULL);
			SendMessage(temp, WM_SETFONT, WPARAM(hFont), TRUE);

			temp = CreateWindowEx(0, L"STATIC", L"Nhà Cửa", WS_CHILD | WS_VISIBLE | SS_CENTER
				, 375, 472, 50, 24, hWnd, NULL, hInst, NULL);
			SendMessage(temp, WM_SETFONT, WPARAM(hFont), TRUE);

			temp = CreateWindowEx(0, L"STATIC", L"Xe Cộ ", WS_CHILD | WS_VISIBLE | SS_CENTER
				, 55, 512, 50, 24, hWnd, NULL, hInst, NULL);
			SendMessage(temp, WM_SETFONT, WPARAM(hFont), TRUE);

			temp = CreateWindowEx(0, L"STATIC", L"Nhu Yếu Phẩm ", WS_CHILD | WS_VISIBLE | SS_CENTER
				, 215, 512, 50, 24, hWnd, NULL, hInst, NULL);
			SendMessage(temp, WM_SETFONT, WPARAM(hFont), TRUE);

			temp = CreateWindowEx(0, L"STATIC", L"Dịch Vụ", WS_CHILD | WS_VISIBLE | SS_CENTER
				, 375, 512, 50, 24, hWnd, NULL, hInst, NULL);
			SendMessage(temp, WM_SETFONT, WPARAM(hFont), TRUE);

			price = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER 
				, 180, 190, 200, 24, hWnd, NULL, hInst, NULL);
			SendMessage(price, WM_SETFONT, WPARAM(hFont), TRUE);
			button = CreateWindowEx(0, L"BUTTON", L"Thêm", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON
				, 200, 230, 70, 25, hWnd, (HMENU)IDC_BUTTON1, hInst, NULL);

			icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
			icex.dwICC = ICC_LISTVIEW_CLASSES | ICC_TREEVIEW_CLASSES;
			InitCommonControlsEx(&icex);
			listview = CreateWindowEx(0,WC_LISTVIEWW, L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | LVS_REPORT | WS_BORDER
				, 20, 270, 440, 170, hWnd, (HMENU)IDC_LISTVIEW, hInst, NULL);

			temp = CreateWindowEx(0, L"STATIC", L"Tổng tiền:", WS_CHILD | WS_VISIBLE | SS_CENTER
				, 300, 250, 50, 24, hWnd, NULL, hInst, NULL);
			SendMessage(temp, WM_SETFONT, WPARAM(hFont), TRUE);

			Tongtien = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER
				, 360, 240, 100, 24, hWnd, NULL, hInst, NULL);
			SendMessage(price, WM_SETFONT, WPARAM(hFont), TRUE);
			wsprintf(bufferKQ2, L"%d", AllPrice);
			SetWindowText(Tongtien, bufferKQ2);

			LVCOLUMN lvCol;
			lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
			lvCol.fmt = LVCFMT_LEFT;
			lvCol.pszText = L"Loại chi tiêu";
			lvCol.cx = 140;
			ListView_InsertColumn(listview, 0, &lvCol);

			lvCol.fmt = LVCFMT_RIGHT;
			lvCol.fmt = LVCFMT_LEFT;
			lvCol.cx = 180;
			lvCol.pszText = L"Nội Dung";
			ListView_InsertColumn(listview, 1, &lvCol);

			lvCol.cx = 120;
			lvCol.pszText = L"Số tiền";
			ListView_InsertColumn(listview, 2, &lvCol);

			for (int i = 0; i < NumberOfData; i++) {
				LV_ITEM lv;
				lv.mask = LVIF_TEXT;
				lv.iItem = i;
				lv.iSubItem = 0;
				lv.pszText = AllOfData[i].TypeOfData;
				ListView_InsertItem(listview, &lv);

				lv.iSubItem = 1;
				lv.pszText = AllOfData[i].ContentOfData;
				ListView_SetItem(listview, &lv);

				lv.iSubItem = 2;
				lv.pszText = AllOfData[i].PriceOfData;
				ListView_SetItem(listview, &lv);
			}
		}
	case WM_CTLCOLORSTATIC:
		SetTextColor((HDC)wParam, RGB(0, 0, 0));
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (LRESULT)GetStockObject(NULL_BRUSH);
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case IDC_BUTTON1:
			{
				wchar_t* buffer1 = NULL;
				wchar_t* buffer2 = NULL;
				wchar_t* buffer3 = NULL;
				int sizebuffer1;
				int sizebuffer2;
				int sizebuffer3;
				int temp_xx;
				sizebuffer1 = GetWindowTextLength(type);
				sizebuffer2 = GetWindowTextLength(content);
				sizebuffer3 = GetWindowTextLength(price);
				buffer1 = new wchar_t[sizebuffer1 + 1];
				buffer2 = new wchar_t[sizebuffer2 + 1];
				buffer3 = new wchar_t[sizebuffer3 + 1];
				GetWindowText(type, buffer1, sizebuffer1 + 1);
				GetWindowText(content, buffer2, sizebuffer2 + 1);
				GetWindowText(price, buffer3, sizebuffer3 + 1);
				temp_xx = _wtoi(buffer3);
				AllPrice += temp_xx;
				if ((IsNumber(buffer3) == false) || (sizebuffer1 == 0)) {
					MessageBox(hWnd, L"Bạn nhập sai định dạng! Vui lòng nhập lại", L"Cảnh Báo", MB_OK);
					break;
				}
				
				LV_ITEM lv;
				lv.mask = LVIF_TEXT;
				lv.iItem = NumberOfData;
				lv.iSubItem = 0;
				lv.pszText = buffer1;
				ListView_InsertItem(listview, &lv);

				lv.iSubItem = 1;
				lv.pszText = buffer2;
				ListView_SetItem(listview, &lv);

				lv.iSubItem = 2;
				lv.pszText = buffer3;
				ListView_SetItem(listview, &lv);

				temp_data.TypeOfData = buffer1;
				temp_data.ContentOfData = buffer2;
				temp_data.PriceOfData = buffer3;
				AllOfData.push_back(temp_data);
				NumberOfData++;
				
				for (int i = 0; i < NumberOfData; i++) {
					tempPrice = _wtoi(AllOfData[i].PriceOfData);
					addNum(AllOfData[i].TypeOfData, L"Ăn Uống", tempPrice, Sum[0]);
					addNum(AllOfData[i].TypeOfData, L"Di Chuyển", tempPrice, Sum[1]);
					addNum(AllOfData[i].TypeOfData, L"Nhà Cửa", tempPrice, Sum[2]);
					addNum(AllOfData[i].TypeOfData, L"Xe Cộ", tempPrice, Sum[3]);
					addNum(AllOfData[i].TypeOfData, L"Nhu Yếu Phẩm", tempPrice, Sum[4]);
					addNum(AllOfData[i].TypeOfData, L"Dịch Vụ", tempPrice, Sum[5]);
				}
				wsprintf(bufferKQ2, L"%d", AllPrice);
				SetWindowText(Tongtien, bufferKQ2);
				break;
			}
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			Graphics* graphics = new Graphics(hdc);
			Pen *pen[6];
			pen[0]= new Pen(Color(255, 200, 100, 0), 0);
			pen[1] = new Pen(Color(255, 0, 100, 0), 0);
			pen[2] = new Pen(Color(255, 200, 00, 0), 0);
			pen[3] = new Pen(Color(255, 70, 70, 70), 0);
			pen[4] = new Pen(Color(255, 10, 70, 70), 0);
			pen[5] = new Pen(Color(255, 10, 0, 90), 0);
			for (int i = 0; i < 6; i++) {
				pen[i]->SetWidth(20);
			}
			
			graphics->DrawLine(pen[0], 25, 480, 45, 480);
			graphics->DrawLine(pen[1],185, 480, 205, 480);
			graphics->DrawLine(pen[2], 345, 480, 365, 480);
			graphics->DrawLine(pen[3], 25, 520, 45, 520);
			graphics->DrawLine(pen[4], 185, 520, 205, 520);
			graphics->DrawLine(pen[5], 345, 520, 365, 520);
            // TODO: Add any drawing code that uses hdc here...
			int colortemp = 25;
			if (check == TRUE){
				for (int i = 0; i < 6; i++) {
					if (Sum[i] != 0) {
						int debugtemp = (Sum[i] * 4 * 100) / AllPrice;
						graphics->DrawLine(pen[i], colortemp, 580, debugtemp + colortemp, 580);
						colortemp += debugtemp;
					}
				}
			}
			
			for (int i = 0; i < 6; i++) {
				delete pen[i];
			}
			delete graphics;
			
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		fileinput.close();
		fileoutput.open("save.txt", ios::trunc);
		fileoutput << NumberOfData <<L" ";
		fileoutput.imbue(loc);
		for (int i = 0; i < NumberOfData; i++) {
			
			fileoutput << AllOfData[i].TypeOfData <<"\n";
			fileoutput << AllOfData[i].ContentOfData << "\n";
			fileoutput << AllOfData[i].PriceOfData << "\n";
		}
		fileoutput.close();
        PostQuitMessage(0);
		GdiplusShutdown(gdiplusToken);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
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
