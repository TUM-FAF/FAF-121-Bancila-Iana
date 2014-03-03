#include <windows.h>
#include "resource.h"

#define IDC_LIST_BOX            100
#define IDC_NEW_ITEM            101

#define IDC_ADD_BUTTON          102
#define IDC_REMOVE_BUTTON       103
#define IDC_CLEAR_BUTTON        104
#define IDC_CAT_BUTTON          105
#define IDC_DOG_BUTTON          106

#define IDC_FILE_EXIT           107
#define IDC_VIEW_CAT            108
#define IDC_VIEW_DOG            109
#define IDC_HELP_ABOUT          110

#define IDC_HEIGHT_SCROLL       111
#define IDC_WIDTH_SCROLL        112

#define IDC_LABEL1              113
#define IDC_LABEL2              114



int MinWindowHeight = 530;
int MinWindowWidth  = 590;

BOOL CALLBACK DialogProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

char szClassName[ ] = "Lab2Class";
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow) {
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_INFORMATION);
    wincl.hIconSm = LoadIcon (NULL, NULL);
    wincl.hCursor = LoadCursor (NULL, IDC_HAND);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

    if(!RegisterClassEx(&wincl))
    {
        MessageBox(NULL, "Error: Something went wrong when registering window", szClassName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowEx (
        0,
        szClassName,
        "Laboratory Work #2",
        WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
        CW_USEDEFAULT, CW_USEDEFAULT,
        MinWindowWidth, MinWindowHeight,
        HWND_DESKTOP,
        NULL,
        hThisInstance,
        NULL);

    ShowWindow (hwnd, nCmdShow);

    while (GetMessage (&messages, NULL, 0, 0)) {
      TranslateMessage(&messages);
      DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // Child windows' handles
    static HWND hwndListBox;
    static HWND hwndNewItem;
    static HWND hwndAddButton;
    static HWND hwndRemoveButton;
    static HWND hwndClearButton;
    static HWND hwndCatButton;
    static HWND hwndDogButton;
    static HWND hwndHeightScroll;
    static HWND hwndWidthScroll;
    static HWND hwndLabel1;
    static HWND hwndLabel2;
    static HWND hwndLabel3;
    static int bgColor=2;
    PAINTSTRUCT ps;
    // Size and position variables
    int SysWidth;
    int SysHeight;
    int WinWidth;
    int WinHeight;
    int index;

    int Width  = 60;   // Button width
    int Height = 30;   // Button height
    int x;
    int y;

    int i;

    // ListBox size and initial position
    int xListBox       = 80;
    int yListBox       = 20;
    int ListBoxWidth  = 400;
    int ListBoxHeight = 300;

    // Menu & menu items
    HMENU hMenu;
    HMENU hSubMenu;

    // Text size
    int cxChar;
    int cyChar;

    // String
    char* szText;
    int TextLength;

    // Paint and size structs
    TEXTMETRIC tm;
    SCROLLINFO si;
    HBRUSH brush;
    RECT rect;
    int color;
    HDC hdc;


    hdc = GetDC(hwnd);
    GetTextMetrics(hdc, &tm);
    cxChar = tm.tmAveCharWidth;
    cyChar = tm.tmHeight;
    ReleaseDC(hwnd, hdc);

    switch(message) {

        case WM_CREATE:
            hwndListBox = CreateWindowEx(
                (DWORD)NULL,
                TEXT("ListBox"),
                NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | LBS_WANTKEYBOARDINPUT,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_LIST_BOX,
                hInst,
                NULL);

            hwndNewItem = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Edit"),
                TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_NEW_ITEM,
                hInst,
                NULL);


            hwndLabel1 = CreateWindowEx(
                (DWORD)NULL,
                TEXT("static"),
                TEXT("Window Width"),
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_LABEL1,
                hInst,
                NULL);

            hwndLabel2 = CreateWindowEx(
                (DWORD)NULL,
                TEXT("static"),
                TEXT("Window Height"),
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                0, 0, 0, 0,
                hwnd,
                (HMENU)IDC_LABEL2,
                hInst,
                NULL);

            hwndWidthScroll = CreateWindow(
                "Scrollbar",
                NULL,
                WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_WIDTH_SCROLL,
                hInst,
                NULL);
            SetScrollRange(hwndWidthScroll, SB_CTL, 0, 100, TRUE);

            hwndHeightScroll = CreateWindow(
                "Scrollbar",
                NULL,
                WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_HEIGHT_SCROLL,
                hInst,
                NULL);
            SetScrollRange(hwndHeightScroll, SB_CTL, 0, 100, TRUE);

            hwndAddButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Add"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_ADD_BUTTON,
                hInst,
                NULL);

            hwndRemoveButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Remove"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_REMOVE_BUTTON,
                hInst,
                NULL);

            hwndClearButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Clear"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_CLEAR_BUTTON,
                hInst,
                NULL);

            hwndCatButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Cat"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_CAT_BUTTON,
                hInst,
                NULL);

            hwndDogButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Dog"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_DOG_BUTTON,
                hInst,
                NULL);

            // Create menu
            hMenu = CreateMenu();

            // Add "File" menu, with "Exit" submenu
            hSubMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");
            AppendMenu(hSubMenu, MF_STRING, IDC_FILE_EXIT, "&Exit");

            // Add "View" menu, with "Day" and "Night" submenus
            hSubMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&View");
            AppendMenu(hSubMenu, MF_STRING, IDC_VIEW_CAT, "&Cat");
            AppendMenu(hSubMenu, MF_STRING, IDC_VIEW_DOG, "&Dog");

            // Add "Help" menu, with "About" submenu
            hSubMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Help");
            AppendMenu(hSubMenu, MF_STRING, IDC_HELP_ABOUT, "&About");

            // Set the menu
            SetMenu(hwnd, hMenu);
            break;

        case WM_SIZE:
            Width  = LOWORD(lParam);
            Height = HIWORD(lParam);

            // Set vertical scroll bar range and page size
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ((MinWindowHeight - 80) / cyChar);
            si.nPage = Height / cyChar;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

            // Set horizontal scroll bar range and page size
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ((MinWindowWidth - 20) / cxChar);
            si.nPage = Width / cxChar;
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

            // CHILD WINDOWS REPOSITION BEGIN
            x = xListBox;
            y = yListBox;
            Width = 60;
            Height = 30;
            MoveWindow(hwndListBox, x, y, ListBoxWidth, ListBoxHeight, TRUE);
            y = yListBox + ListBoxHeight + 5;
            MoveWindow(hwndNewItem, x, y, (ListBoxWidth - Width - 5), Height, TRUE);
            y = y + Height + 10;
            MoveWindow(hwndLabel1, x, y, ListBoxWidth, 20, TRUE);
            y = y + 20;
            MoveWindow(hwndWidthScroll, x, y, ListBoxWidth, 10, TRUE);
            y = y + 10 + 10;
            MoveWindow(hwndLabel2, x, y, ListBoxWidth, 20, TRUE);
            y = y + 20;
            MoveWindow(hwndHeightScroll, x, y, ListBoxWidth, 10, TRUE);
            x = xListBox + ListBoxWidth - Width;
            y = yListBox + ListBoxHeight + 5;
            MoveWindow(hwndAddButton, x, y, Width, Height, TRUE);
            x = xListBox + ListBoxWidth + 10;
            y = yListBox + 60;
            MoveWindow(hwndRemoveButton, x, y, Width, Height, TRUE);
            y = y + Height + 30;
            MoveWindow(hwndClearButton, x, y, Width, Height, TRUE);
            x = xListBox + ListBoxWidth - Width * 8 + 10;
            y = yListBox + ListBoxHeight - Width * 3;
            MoveWindow(hwndCatButton, x, y, Width, Height, TRUE);
            x = xListBox + ListBoxWidth - Width * 8 + 10;
            y = yListBox + ListBoxHeight - Width * 4;
            MoveWindow(hwndDogButton, x, y, Width, Height, TRUE);
            // CHILD WINDOWS REPOSITION END

            GetWindowRect(hwnd, &rect);
            WinWidth = rect.right - rect.left;
            WinHeight = rect.bottom - rect.top;
            SysWidth = GetSystemMetrics(SM_CXSCREEN);
            SysHeight = GetSystemMetrics(SM_CYSCREEN);

            // Set width scrollbar position
            SetScrollPos(hwndWidthScroll, SB_CTL, (WinWidth * 100 / SysWidth), TRUE);

            // Set height scrollbar position
            SetScrollPos(hwndHeightScroll, SB_CTL, (WinHeight * 100 / SysHeight), TRUE);
            break;

        case WM_VSCROLL:
            // Get all the vertical scroll bar information
            si.cbSize = sizeof(si);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_VERT, &si);

            // Save the position for later comparison
            y = si.nPos;

            switch(LOWORD(wParam)) {
                case SB_TOP:
                    si.nPos = si.nMin;
                    break;

                case SB_BOTTOM:
                    si.nPos = si.nMax;
                    break;

                case SB_LINEUP:
                    si.nPos -= 1;
                    break;

                case SB_LINEDOWN:
                    si.nPos += 1;
                    break;

                case SB_PAGEUP:
                    si.nPos -= si.nPage;
                    break;

                case SB_PAGEDOWN:
                    si.nPos += si.nPage;
                    break;

                case SB_THUMBTRACK:
                    si.nPos = si.nTrackPos;
                    break;

                default:
                    break;
            }

            // Set the position and then retrieve it
            si.fMask = SIF_POS;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
            GetScrollInfo(hwnd, SB_VERT, &si);

            // If the position has changed, scroll the window and update it
            if(si.nPos != y) {
                ScrollWindow(hwnd, 0, cyChar * (y - si.nPos), NULL, NULL);
                UpdateWindow(hwnd);
            }
            break;

        case WM_HSCROLL:
            GetWindowRect(hwnd, &rect);
            WinWidth = rect.right - rect.left;
            WinHeight = rect.bottom - rect.top;
            SysWidth = GetSystemMetrics(SM_CXSCREEN);
            SysHeight = GetSystemMetrics(SM_CYSCREEN);
            if(GetWindowLong((HWND)lParam, GWL_ID) == IDC_WIDTH_SCROLL) {
                si.cbSize = sizeof(si);
                si.fMask = SIF_ALL;
                GetScrollInfo(hwndWidthScroll, SB_CTL, &si);
                x = si.nPos;
                switch(LOWORD(wParam)) {
                    case SB_LINELEFT:
                        si.nPos -= 1;
                        break;
                    case SB_LINERIGHT:
                        si.nPos += 1;
                        break;
                    case SB_THUMBPOSITION:
                        si.nPos = si.nTrackPos;
                        break;
                    default:
                        break;
                }
                si.fMask = SIF_POS;
                SetScrollInfo(hwndWidthScroll, SB_CTL, &si, TRUE);
                GetScrollInfo(hwndWidthScroll, SB_CTL, &si);
                if(si.nPos != x) {
                    SetScrollPos(hwndWidthScroll, SB_CTL, si.nPos, TRUE);
                }
                // Set window width
                MoveWindow(hwnd, rect.left, rect.top, (si.nPos * SysWidth / 100), WinHeight, TRUE);
                break;
            }

            if(GetWindowLong((HWND)lParam, GWL_ID) == IDC_HEIGHT_SCROLL) {
                si.cbSize = sizeof(si);
                si.fMask = SIF_ALL;
                GetScrollInfo(hwndHeightScroll, SB_CTL, &si);
                x = si.nPos;
                switch(LOWORD(wParam)) {
                    case SB_LINELEFT:
                        si.nPos -= 1;
                        break;
                    case SB_LINERIGHT:
                        si.nPos += 1;
                        break;
                    case SB_THUMBPOSITION:
                        si.nPos = si.nTrackPos;
                        break;
                    default:
                        break;
                }
                si.fMask = SIF_POS;
                SetScrollInfo(hwndHeightScroll, SB_CTL, &si, TRUE);
                GetScrollInfo(hwndHeightScroll, SB_CTL, &si);
                if(si.nPos != x) {
                    SetScrollPos(hwndHeightScroll, SB_CTL, si.nPos, TRUE);
                }
                // Set window height
                MoveWindow(hwnd, rect.left, rect.top, WinWidth, (si.nPos * SysHeight / 100), TRUE);
                break;
            }

            // Get all the vertical scroll bar information
            si.cbSize = sizeof(si);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_HORZ, &si);

            // Save the position for later comparison
            x = si.nPos;
            switch(LOWORD(wParam)) {
                case SB_LINELEFT:
                    si.nPos -= 1;
                    break;

                case SB_LINERIGHT:
                    si.nPos += 1;
                    break;

                case SB_PAGELEFT:
                    si.nPos -= si.nPage;
                    break;

                case SB_PAGERIGHT:
                    si.nPos += si.nPage;
                    break;

                case SB_THUMBPOSITION:
                    si.nPos = si.nTrackPos;
                    break;

                default:
                    break;
            }
            // Set the position and then retrieve it
            si.fMask = SIF_POS;
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
            GetScrollInfo(hwnd, SB_HORZ, &si);

            // If the position has changed, scroll the window and update it
            if(si.nPos != x) {
                ScrollWindow(hwnd, cxChar * (x - si.nPos), 0, NULL, 0);
                UpdateWindow(hwnd);
            }
            break;

        case WM_COMMAND:

            switch (LOWORD(wParam)) {

                case IDC_CAT_BUTTON:

                        bgColor = 1;
                    InvalidateRect(hwnd, NULL, TRUE);
                    break;

                case IDC_DOG_BUTTON:

                        bgColor = 0;
                    InvalidateRect(hwnd, NULL, TRUE);
                    break;

                case IDC_LIST_BOX:
                    switch (HIWORD(wParam)) {
                        case LBN_DBLCLK:
                            index = SendMessage(hwndListBox, LB_GETCURSEL, 0, 0);
                            SendMessage(hwndListBox, LB_DELETESTRING, (WPARAM)index, 0);
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                            break;
                    }
                    break;

                case IDC_ADD_BUTTON:
                    TextLength = SendMessage(hwndNewItem, WM_GETTEXTLENGTH, 0, 0);
                    szText = (char*)malloc(TextLength+1);
                    SendMessage(hwndNewItem, WM_GETTEXT, TextLength+1, (LPARAM)szText);
                    SendMessage(hwndListBox, LB_ADDSTRING, 0, (LPARAM)szText);
                    SendMessage(hwndNewItem, WM_SETTEXT, 0, (LPARAM)"");
                    free(szText);
                    break;

                case IDC_REMOVE_BUTTON:
                    i = SendMessage(hwndListBox, LB_GETCURSEL, 0, 0);
                    if(i != LB_ERR) {
                        SendMessage(hwndListBox, LB_DELETESTRING, i, 0);
                    }
                    break;

                case IDC_CLEAR_BUTTON:
                    SendMessage(hwndListBox, LB_RESETCONTENT, 0, 0);
                    break;

                case IDC_FILE_EXIT:
                    SendMessage(hwnd, WM_DESTROY, 0, 0);
                    break;

                case IDC_VIEW_CAT:
                    SendMessage(hwnd, WM_COMMAND, IDC_CAT_BUTTON, lParam);
                    break;

                case IDC_VIEW_DOG:
                    SendMessage(hwnd, WM_COMMAND, IDC_DOG_BUTTON, lParam);
                    break;

                case IDC_HELP_ABOUT:
                    return DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT), NULL, (DLGPROC)DialogProcedure);
                    break;


            }
            break;

        case WM_KEYDOWN:
            GetWindowRect(hwnd, &rect);
            WinWidth = rect.right - rect.left;
            WinHeight = rect.bottom - rect.top;
            SysWidth = GetSystemMetrics(SM_CXSCREEN);
            SysHeight = GetSystemMetrics(SM_CYSCREEN);

            // Color window in white on Shift + "/?" for US
            if((wParam == VK_OEM_2)&&(HIBYTE(GetKeyState(VK_SHIFT)) > 1)) {
                brush = CreateSolidBrush(RGB(255,255,255));
                    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
                    si.cbSize = sizeof(si);
                    si.fMask = SIF_POS;
                    si.nPos = 0;
                    SendMessage(hwnd, WM_SIZE, 0, 0);
                    break;
            }
            // Color window in green on Shift + "'"" for US
            if((wParam == VK_OEM_7)&&(HIBYTE(GetKeyState(VK_SHIFT)) > 1)) {
                brush = CreateSolidBrush(RGB(0,205,0));
                    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
                    si.cbSize = sizeof(si);
                    si.fMask = SIF_POS;
                    si.nPos = 0;
                    SendMessage(hwnd, WM_SIZE, 0, 0);
                    break;
            }
            // Color window in blue on Shift + ";:" for US
            if((wParam == VK_OEM_1)&&(HIBYTE(GetKeyState(VK_SHIFT)) > 1)) {
                brush = CreateSolidBrush(RGB(32,178,170));
                    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
                    si.cbSize = sizeof(si);
                    si.fMask = SIF_POS;
                    si.nPos = 0;
                    SendMessage(hwnd, WM_SIZE, 0, 0);
                    break;
            }
            // Color window in red on Shift + "]}" for US
            if((wParam == VK_OEM_6)&&(HIBYTE(GetKeyState(VK_SHIFT)) > 1)) {
                brush = CreateSolidBrush(RGB(238,59,59));
                    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
                    si.cbSize = sizeof(si);
                    si.fMask = SIF_POS;
                    si.nPos = 0;
                    SendMessage(hwnd, WM_SIZE, 0, 0);
                    break;
            }
            return DefWindowProc (hwnd, WM_PAINT, wParam, lParam);

        case WM_PAINT:
                hdc = BeginPaint(hwnd, &ps);
                HBITMAP hBackgroundImg;

				if (bgColor == 0)
				{
					hBackgroundImg = (HBITMAP)LoadImage(NULL, "two_dogs.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				}
				if (bgColor == 1)
				{
					hBackgroundImg = (HBITMAP)LoadImage(NULL, "orange_cat.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				}
				if (bgColor == 2)
				{
                    hBackgroundImg = (HBITMAP) CreateSolidBrush;
				}
				if (!hBackgroundImg)
				{
					MessageBox(hwnd,"Err","Err",MB_OK);
				}
				HBITMAP hOldBm;
				HDC hMemDC = CreateCompatibleDC(hdc);
				hOldBm = (HBITMAP)SelectObject(hMemDC, hBackgroundImg);
				RECT rct;
				GetClientRect(hwnd, &rct);

				LONG width = rct.right - rct.left;
				LONG height = rct.bottom - rct.top;
				LONG x = width/500;
				while (x < width)
				{
					LONG y = 0;
					while (y < height)
					{
						BitBlt(hdc, x, y, 600,600, hMemDC, 0, 0, SRCCOPY);
						y += 600;
					}
					x += 600;
				}

				SelectObject(hMemDC, hOldBm);
				DeleteObject(hBackgroundImg);

				DeleteDC(hMemDC);
                EndPaint(hwnd, &ps);

            break;

        case WM_DESTROY:
            PostQuitMessage (0);
            break;

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

BOOL CALLBACK DialogProcedure(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg) {
        case WM_INITDIALOG:
            return TRUE;


        case WM_CLOSE:
            EndDialog(hwndDlg, 0);
            return TRUE;

        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case IDOK:
                case IDCANCEL:
                    EndDialog(hwndDlg, 0);
                    return TRUE;
            }
            break;
    }
    return FALSE;
}
