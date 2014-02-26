#include <windows.h>
#include <stdlib.h>
#include <tchar.h>

//Defining the ID values of the windows
#define IDC_CAT_BUTTON      100
#define IDC_DOG_BUTTON      101
#define IDC_BUY_BUTTON      102
#define IDC_ADD_BUTTON      103
#define IDC_CLEAR_BUTTON    104
#define IDC_INPUT_TEXT      105
#define IDC_OUTPUT_TEXT     106

//  Declare Windows procedure
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

//  Make the class name into a global variable
char szClassName[ ] = "Lab1WindowsApp";

//  Create a global handle to an instance variable to be used across different functions
HINSTANCE hInst;
int items, focused = 0;

int WINAPI WinMain(HINSTANCE hThisInstance,
	               HINSTANCE hPrevInstance,
				   LPSTR lpszArgument,
				   int nCmdShow)
{
    hInst=hThisInstance;
    HWND hwnd;               // This is the handle for our window
    MSG messages;            // Here messages to the application are saved
    WNDCLASSEX wincl;        // Data structure for the windowclass

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      // This function is called by windows
    wincl.style = CS_HREDRAW | CS_VREDRAW ;
    wincl.cbSize = sizeof (WNDCLASSEX);

    // Use default icon and mouse-pointer
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                       // No menu
    wincl.cbClsExtra = 0;                            // No extra bytes after the window class
    wincl.cbWndExtra = 0;                            // structure or the window instance

    // Use Windows's white colour as the background of the window
    wincl.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(102,102,102));

    // Register the window class, and if it fails quit the program
    if (!RegisterClassEx (&wincl))
    {
        MessageBox(NULL,"Error: Something went wrong when registering window",szClassName,MB_ICONERROR);
        return 0;
    }

    // The class is registered, let's create the program
    hwnd = CreateWindowEx (
           0,                               // Extended possibilites for variation
           szClassName,                     // Classname
           "Lab_1 Window's program",        // Title Text
           WS_OVERLAPPEDWINDOW,             // default window
           CW_USEDEFAULT,                   // Windows decides the position
           CW_USEDEFAULT,                   // where the window ends up on the screen
           590,                             // The programs width
           330,                             // and height in pixels
           HWND_DESKTOP,                    // The window is a child-window to desktop
           NULL,                            // No menu
           hThisInstance,                   // Program Instance handler
           NULL                             // No Window Creation data
           );

    // Make the window visible on the screen
    ShowWindow (hwnd, nCmdShow);

    // Run the message loop. It will run until GetMessage() returns 0
    while (GetMessage (&messages, NULL, 0, 0))
    {
        // Translate virtual-key messages into character messages
        TranslateMessage(&messages);
        // Send message to WindowProcedure
        DispatchMessage(&messages);
    }

    // The program return-value is 0 - The value that PostQuitMessage() gave

    return messages.wParam;
}

//  This function is called by the Windows function DispatchMessage()
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND  hwndAddButton, hwndClearButton, hwndOutputText, hwndInputText, hwndCatButton, hwndDogButton, hwndBuyButton ;    //all the handles to different controls
    PAINTSTRUCT ps;
    RECT rect;
    HDC hdc;                                                                                                                     //device context handle
    LRESULT textSize;
    char * message = new char[100];                                                                                              //Text buffer
    char * placeholder = new char[26];
    placeholder = "Type here...";
    HFONT textFont,hFontOld;                                                                                                     //Font handles
	int screenW;                                                                                                                 //characters ave width of string
    int screenH;                                                                                                                 //characters ave height of string                                                                                                                
    HBRUSH color;

    switch(msg)                       // handle the messages 
    {
	case WM_CREATE:

		//Getting information about the average height and width of a letter
		screenW = GetSystemMetrics(SM_CXSCREEN);
        screenH = GetSystemMetrics(SM_CYSCREEN);

		//Getting the dimensions of the window area
		GetClientRect(hwnd, &rect);
            SetWindowPos(
                    hwnd, 0,
                    (screenW - rect.right)/2,
                    (screenH - rect.bottom)/2,
                    0, 0,
					SWP_NOZORDER|SWP_NOSIZE);

			hwndAddButton = CreateWindowEx(
                (DWORD)WS_EX_CLIENTEDGE,
                TEXT("button"),                                                 // The class name required is button
                TEXT("Add"),                                                    // the caption of the button
                WS_CHILD |WS_VISIBLE | BS_PUSHBUTTON,                           // the styles
                480, 100,                                                       // the left and top co-ordinates
                70, 40,                                                         // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_ADD_BUTTON,                                          // the ID of your button
                hInst,                                                          // the instance of your application
                NULL);

			 hwndClearButton = CreateWindowEx(
                (DWORD)WS_EX_CLIENTEDGE,
                TEXT("button"),                                                 // The class name required is button
                TEXT("Clear"),                                                  // the caption of the button
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,                          // the styles
                480, 150,                                                       // the left and top co-ordinates
                70, 40,                                                         // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_CLEAR_BUTTON,                                        // the ID of your button
                hInst,                                                          // the instance of your application
                NULL);                                                          // extra bits you dont really need

            hwndOutputText = CreateWindowEx(
                (DWORD)NULL,
                TEXT("edit"),                                                   // The class name required is edit
                TEXT(""),                                                       // Default text.
                WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL |
                ES_AUTOVSCROLL | ES_MULTILINE | ES_READONLY,                    // Textbox styles
                80, 60,                                                         // the left and top co-ordinates
                390, 150,                                                       // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_OUTPUT_TEXT,                                         // the ID of your editbox
                hInst,                                                          // the instance of your application
                NULL);                                                          // extra bits you dont really need

            hwndInputText = CreateWindowEx(
                (DWORD)NULL,
                TEXT("edit"),                                                   // The class name required is edit
                TEXT(placeholder),                                              // Default text.
                WS_VISIBLE | WS_CHILD | WS_EX_CLIENTEDGE | ES_MULTILINE,        // Textbox styles
                80, 230,                                                        // the left and top co-ordinates
                30, 25,                                                        // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_INPUT_TEXT,                                          // the ID of your editbox
                hInst,                                                          // the instance of your application
                NULL);                                                          // extra bits you dont really need

			 hwndCatButton = CreateWindowEx(
                (DWORD)WS_EX_DLGMODALFRAME,                                                
                TEXT("button"),                                                 // The class name required is button
                TEXT("Cat"),                                                    // the caption of the button
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW,           // the styles
                20, 70,                                                         // the left and top co-ordinates
                48, 48,                                                         // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_CAT_BUTTON,                                          // the ID of your button
                hInst,                                                          // the instance of your application
                NULL);

            hwndDogButton = CreateWindowEx(
                (DWORD)WS_EX_DLGMODALFRAME,
                TEXT("button"),                                                 // The class name required is button
                TEXT("Dog"),                                                    // the caption of the button
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW,           // the styles
                20, 130,                                                        // the left and top co-ordinates
                48, 48,                                                         // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_DOG_BUTTON,                                          // the ID of your button
                hInst,                                                          // the instance of your application
                NULL);

			hwndBuyButton = CreateWindowEx(
                (DWORD)WS_EX_DLGMODALFRAME,
                TEXT("button"),                                                 // The class name required is button
                TEXT("Buy"),                                                    // the caption of the button
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW,           // the styles
                20, 190,                                                        // the left and top co-ordinates
                48, 48,                                                         // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_BUY_BUTTON,                                          // the ID of your button
                hInst,                                                          // the instance of your application
                NULL);
			break;

		 case WM_SIZE:

        //Setting up the display window size
        GetClientRect(hwnd,&rect);
        rect.left  =80;
        rect.top   =60;
        rect.bottom-=80;
        rect.right -=100;

        //Moving the buttons and other windows according to the resize
         MoveWindow(hwndAddButton,rect.right+10,rect.top+30,70,40,FALSE);

         MoveWindow(hwndClearButton,rect.right+10,rect.top+80,70,40,FALSE);

         MoveWindow(hwndOutputText,rect.left+1,1+rect.top,rect.right-rect.left-1,rect.bottom-rect.top-1,FALSE);

	     MoveWindow(hwndInputText,rect.left+1,20+rect.bottom,rect.right-rect.left-2,25,FALSE);

         MoveWindow(hwndCatButton,rect.left-60,rect.top+10,48,48,FALSE);

         MoveWindow(hwndDogButton,rect.left-60,rect.top+70,48,48,FALSE);

	     MoveWindow(hwndBuyButton,rect.left-60,rect.top+130,48,48,FALSE);

            return 0;

		 case WM_GETMINMAXINFO:

        //Setting the minimal size for the window
        MINMAXINFO *ptMinMax;
        ptMinMax=(MINMAXINFO*)lParam;

        ptMinMax->ptMinTrackSize.x=590;
        ptMinMax->ptMinTrackSize.y=330;
        break;

		case WM_COMMAND:

			//Handling button presses
            switch(LOWORD(wParam))
			{
              case IDC_ADD_BUTTON:

				  //sending the message from the edit box to the list box
                    textSize = SendMessage(hwndInputText, WM_GETTEXT, 100, (LPARAM)message);
                    message[textSize] = _T('\0');

                    if(strlen(message) && strcmp(message, placeholder))
                    {
                        char *item = new char[200];
                        if(items)
							strcpy(item, "\r\n > ");
                        else
							strcpy(item, " > ");                                     // Managing the new string
                        strcat(item, message);
                        SendMessage(hwndOutputText, EM_REPLACESEL,
                            TRUE, (LPARAM)item);                                     // Appending a new item in the list
                        SendMessage(hwndInputText, WM_SETTEXT, TRUE,(LPARAM)"");     // Clearing the text input
                        delete [] item;                                              // Managing the memory
                        items += 1;                                                  // Incrementing the number of items
                        SendMessage(
                            hwndInputText,
                            WM_SETTEXT,
                            TRUE,
                            (LPARAM)placeholder);                                    // Recovering the placeholder
                        focused = 0;
                    }
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                    break;

		      case IDC_CLEAR_BUTTON:
                    SendMessage(hwndOutputText, WM_SETTEXT, 0, (LPARAM)"");
                    break;

			case IDC_INPUT_TEXT:
                    if(HIWORD(wParam) == EN_SETFOCUS)
                    {
                        textSize = SendMessage(hwndInputText, WM_GETTEXT, 100, (LPARAM)message);
                        message[textSize] = _T('\0');

                        if(!strcmp(message, placeholder))
                        {
                            SendMessage(hwndInputText, WM_SETTEXT, TRUE,(LPARAM)"");             // Clearing the text input
                            focused = 1;
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                        }
                    }
                    else if(HIWORD(wParam) == EN_KILLFOCUS)
                    {
                        textSize = SendMessage(hwndInputText, WM_GETTEXT, 100, (LPARAM)message);
                        message[textSize] = _T('\0');

                        if(!strcmp(message, ""))
                        {
                            SendMessage(
                                hwndInputText,
                                WM_SETTEXT,
                                TRUE,
                                (LPARAM)placeholder);                                              // Recovering the placeholder
                            focused = 0;
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                        }
                    }
                    break;

            case IDC_CAT_BUTTON:
                    SendMessage(hwndOutputText, WM_SETTEXT, 0, (LPARAM)" Domestic cats, no matter their breed, are all members of one species."
                                                                       " Felis catus has had a very long relationship with humans."
                                                                       " Ancient Egyptians may have first domesticated cats as early as 4,000 years ago."
                                                                       " Plentiful rodents probably drew wild felines to human communities."
                                                                       " The cats' skill in killing them may have first earned the affectionate attention of humans."
                                                                       " Early Egyptians worshipped a cat goddess and even mummified their beloved pets for their journey to the next world—accompanied by mummified mice!"
                                                                       " Cultures around the world later adopted cats as their own companions."
                                                                       " Like their wild relatives, domestic cats are natural hunters able to stalk prey and pounce with sharp claws and teeth."
                                                                       " They are particularly effective at night, when their light-reflecting eyes allow them to see better than much of their prey."
                                                                       " Cats also enjoy acute hearing."
                                                                       " All cats are nimble and agile, and their long tails aid their outstanding balance."
                                                                       " Cats communicate by marking trees, fence posts, or furniture with their claws or their waste. "
                                                                       " These scent posts are meant to inform others of a cat's home range."
                                                                       " House cats employ a vocal repertoire that extends from a purr to a screech."
                                                                       " Domestic cats remain largely carnivorous, and have evolved a simple gut appropriate for raw meat."
                                                                       " They also retain the rough tongue that can help them clean every last morsel from an animal bone (and groom themselves)."
                                                                       " Their diets vary with the whims of humans, however, and can be supplemented by the cat's own hunting successes.");

            break;

            case IDC_DOG_BUTTON:

                    SendMessage(hwndOutputText, WM_SETTEXT, 0, (LPARAM)" Dogs are one of our most popular domestic pet."
                                                                       " Most people acquire a dog out of choice, so if you make this decision you should think carefully before going ahead."
                                                                       " A dog needs lots of love and care, including regular worming, vaccinations and dental care;"
                                                                       " you will also need to keep an eye out for ticks, fleas and ear mites."
                                                                       " If your new puppy or dog hasn't been neutered you will also need to make arrangements for your pet to be neutered with your vet."
                                                                       " In the unlikely event that your dog goes missing it is going to be very difficult for anyone to know who it belongs to,"
                                                                       " unless your dog carries some form of permanent identification."
                                                                       " It is wise to get your dog microchipped, this will avoid heartache in the long run, should your dog go missing or is stolen."
                                                                       " Dogs love human company and, unlike cats, love constant human contact. "
                                                                       " Don't forget that dogs need somewhere warm to sleep, a constant supply of water, feeding daily, toys to play with and regular exercise."
                                                                       " It can cost up to £80 a month to care for a dog, including food, veterinary care and pet insurance; "
                                                                       " there will be other costs, including buying toys and kennel charges when you go on holiday."
                                                                       " Dogs can live up to 10 years old and longer, over this time your dog will expect lots of care, companionship, time for play and grooming."
                                                                       " Being able to provide all of this will ensure you and your dog make the most of your time together.");




            break;


				case IDC_BUY_BUTTON:
                    if (MessageBox(NULL, TEXT("Which one would you choose to buy? Cat YES?"), TEXT("Buy a Kitten"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) == IDYES) {
                        return MessageBox(NULL, TEXT("Great Decision !!!"), TEXT("Congratulations!"), MB_OK | MB_ICONASTERISK);
                    };
                   break;
            }
            break;



	case WM_CTLCOLOREDIT:
            if(GetDlgCtrlID((HWND)lParam) == IDC_INPUT_TEXT)
            {
                hdc = (HDC)wParam;                                              //Get handles
                if(focused)
                {
                    color = CreateSolidBrush(RGB(255, 255, 255));
                    SetTextColor(hdc, RGB(0,0,0));                              // Text color
                    SetBkMode(hdc, TRANSPARENT);                                // EditBox Backround Mode
                    SetBkColor(hdc,(LONG)color);                                // Backround color for EditBox
                }
                else
                {
                    color = CreateSolidBrush(RGB(255, 255, 255));
                    SetTextColor(hdc, RGB(110,123,139));                        // Text color
                    SetBkMode(hdc, TRANSPARENT);                                // EditBox Backround Mode
                    SetBkColor(hdc,(LONG)color);                                // Backround color for EditBox
                }
                return (LONG)color;                                             // Paint it
            }
            break;

	    case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rect);                                                                        // Getting coordinates of window client area
            SetBkMode(hdc, TRANSPARENT);                                                                       // Set the background to be transparent
            SetTextColor(hdc, RGB(255,231,186));                                                               // Setting the text color to a pale orange
			DrawText(hdc, "\nIANA Bancila", -1, &rect, DT_CENTER | DT_TOP);                                    // Drawing the text on top aligning it to center
            textFont  = CreateFont(0, 0, 0, 0, FW_SEMIBOLD, TRUE, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");     // Creating the text font to semibold, italic, choosing Times New Roman font
            hFontOld  = (HFONT)SelectObject(hdc,textFont);                                                     // Setting the text font 
            SetTextColor(hdc,RGB(238,173,14));                                                                 // Setting the text color to a dark orange
            SetBkMode(hdc, TRANSPARENT);                                                                       // Set the background to be transparent
            DrawText(hdc, "\n\nLAB1_WindowsProgramming", -1, &rect, DT_CENTER | DT_TOP);                        // Drawing the text on top aligning it to center
            SetTextColor(hdc, RGB(0, 100, 0));                                                                 // Resetting the color to black
			EndPaint(hwnd, &ps);
            break;

        case WM_DRAWITEM:
            if ((UINT)wParam == IDC_DOG_BUTTON) {
                LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                SIZE size;
                char szDogBtnText[5];
                strcpy(szDogBtnText, "Dog");
                GetTextExtentPoint32(lpdis->hDC, szDogBtnText, strlen(szDogBtnText), &size);
                SetTextColor(lpdis->hDC, RGB(245,245,220));
                SetBkColor(lpdis->hDC, RGB(133,99,99));

                ExtTextOut(
                    lpdis->hDC,
                    ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
                    ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
                    ETO_OPAQUE | ETO_CLIPPED,
                    &lpdis->rcItem,
                    szDogBtnText,
                    strlen(szDogBtnText),
                    NULL);

                DrawEdge(
                    lpdis->hDC,
                    &lpdis->rcItem,
                    (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                    BF_RECT);
                return TRUE;
			}

			else if ((UINT)wParam == IDC_CAT_BUTTON) {
                LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                SIZE size;
                char szCatBtnText[5];
                strcpy(szCatBtnText, "Cat");
                GetTextExtentPoint32(lpdis->hDC, szCatBtnText, strlen(szCatBtnText), &size);
                SetTextColor(lpdis->hDC, RGB(245,245,220));
                SetBkColor(lpdis->hDC, RGB(238,118,33));

                ExtTextOut(
                    lpdis->hDC,
                    ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
                    ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
                    ETO_OPAQUE | ETO_CLIPPED,
                    &lpdis->rcItem,
                    szCatBtnText,
                    strlen(szCatBtnText),
                    NULL);

                DrawEdge(
                    lpdis->hDC,
                    &lpdis->rcItem,
                    (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                    BF_RECT);

                return TRUE;

			}

			else if ((UINT)wParam == IDC_BUY_BUTTON) {
                LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                SIZE size;
                char szBuyBtnText[5];
                strcpy(szBuyBtnText, "BUY");
                GetTextExtentPoint32(lpdis->hDC, szBuyBtnText, strlen(szBuyBtnText), &size);
                SetTextColor(lpdis->hDC, RGB(245,245,220));
                SetBkColor(lpdis->hDC, RGB(153,204,50));

                ExtTextOut(
                    lpdis->hDC,
                    ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
                    ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
                    ETO_OPAQUE | ETO_CLIPPED,
                    &lpdis->rcItem,
                    szBuyBtnText,
                    strlen(szBuyBtnText),
                    NULL);

                DrawEdge(
                    lpdis->hDC,
                    &lpdis->rcItem,
                    (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                    BF_RECT);

                return TRUE;

			}

             break;

	case WM_SYSCOMMAND:
            switch(wParam) {

                case SC_MINIMIZE:
                    return MessageBox(NULL, TEXT("STOP! Do not do it!"), TEXT("Minimize Button Clicked!"), MB_OK | MB_ICONSTOP);

                case SC_MAXIMIZE:
                    return MessageBox(NULL, TEXT("Hey! You just clicked Maximize button"), TEXT("Maximize Button Clicked!"), MB_OK | MB_ICONEXCLAMATION);

                case SC_CLOSE:
            if(MessageBox(hwnd, "Are you sure that you want to close this window?", "Lab_1", MB_OKCANCEL) == IDOK)
                DestroyWindow(hwnd);
			break;
                    
                default:
                    return DefWindowProc(hwnd, msg, wParam, lParam);
            }
            break;

	case WM_DESTROY: 

		// User closed the window
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
   }
