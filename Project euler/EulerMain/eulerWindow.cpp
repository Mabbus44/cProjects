#include <tchar.h>
#include <windows.h>
#include <commctrl.h>
#include <string>
#include "eulerWindow.h"

#include <sstream>
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


EulerWindow::EulerWindow()
{
  title = "Euler";
  variable = NULL;
  initialized = false;
}

bool EulerWindow::createEulerWindow (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
  HWND hwnd;               /* This is the handle for our window */
  WNDCLASSEX wincl;        /* Data structure for the windowclass */

  /* The Window structure */
  wincl.hInstance = hThisInstance;
  wincl.lpszClassName = title.c_str();
  wincl.lpfnWndProc = windowProcedure;      /* This function is called by windows */
  wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
  wincl.cbSize = sizeof (WNDCLASSEX);

  /* Use default icon and mouse-pointer */
  wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
  wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
  wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
  wincl.lpszMenuName = NULL;                 /* No menu */
  wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
  wincl.cbWndExtra = 0;                      /* structure or the window instance */
  /* Use Windows's default color as the background of the window */
  wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

  /* Register the window class, and if it fails quit the program */
  if (!RegisterClassEx (&wincl)){
    MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  /* The class is registered, let's create the program*/

  hwnd = CreateWindowEx (
          0,                   /* Extended possibilites for variation */
          title.c_str(),         /* Classname */
          title.c_str(),       /* Title Text */
          WS_OVERLAPPEDWINDOW, /* default window */
          CW_USEDEFAULT,       /* Windows decides the position */
          CW_USEDEFAULT,       /* where the window ends up on the screen */
          544,                 /* The programs width */
          375,                 /* and height in pixels */
          HWND_DESKTOP,        /* The window is a child-window to desktop */
          NULL,                /* No menu */
          hThisInstance,       /* Program Instance handler */
          NULL                 /* No Window Creation data */
          );

  SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG>(this));

  // Create menu
  HMENU hMenu = CreateMenu();
  HMENU hSubMenu = CreatePopupMenu();
  AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");
  AppendMenu(hSubMenu, MF_STRING, ID_FILE_RUN, "&Run\tF5");
  AppendMenu(hSubMenu, MF_STRING, ID_FILE_QUIT, "&Quit\tAlt+F4");
  SetMenu(hwnd, hMenu);

  // Create edit box
  RECT rect;
  int width;
  int height;
  if(GetWindowRect(hwnd, &rect))
  {
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;
  }
  hEdit=CreateWindowEx(WS_EX_CLIENTEDGE,
        "EDIT",
        "",
        WS_CHILD|WS_VISIBLE|
        ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,
        0,
        0,
        width/2,
        height,
        hwnd,
        (HMENU)IDC_MAIN_EDIT,
        GetModuleHandle(NULL),
        NULL);
    HGDIOBJ hfDefault=GetStockObject(DEFAULT_GUI_FONT);
    SendMessage(hEdit,
        WM_SETFONT,
        (WPARAM)hfDefault,
        MAKELPARAM(FALSE,0));
    SendMessage(hEdit,
        WM_SETTEXT,
        NULL,
        (LPARAM)"Insert text here...");

  // Create variable list
  hVariableList=CreateWindowEx(WS_EX_CLIENTEDGE,
        WC_LISTVIEW,
        "",
        WS_CHILD|WS_VISIBLE|LVS_REPORT|LVS_EDITLABELS,
        width/2,
        0,
        width/2,
        height,
        hwnd,
        (HMENU)IDC_VARIABLE_LIST,
        GetModuleHandle(NULL),
        NULL);
    SendMessage(hVariableList,
        WM_SETFONT,
        (WPARAM)hfDefault,
        MAKELPARAM(FALSE,0));

        LVCOLUMN lvcName;
        LVCOLUMN lvcValue;

        lvcName.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvcName.iSubItem = 0;
        lvcName.pszText = "Name";
        lvcName.cx = 100;               // Width of column in pixels.
        lvcName.fmt = LVCFMT_LEFT;      // Left-aligned column.

        lvcValue.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvcValue.iSubItem = 1;
        lvcValue.pszText = "Value";
        lvcValue.cx = 100;               // Width of column in pixels.
        lvcValue.fmt = LVCFMT_LEFT;      // Left-aligned column.

        // Insert the columns into the list view.
        ListView_InsertColumn(hVariableList, 0, &lvcName);
        ListView_InsertColumn(hVariableList, 1, &lvcValue);



        SendMessage(hVariableList,
            LB_ADDSTRING,
            NULL,
            (LPARAM)"Variable A");
        SendMessage(hVariableList,
            LB_ADDSTRING,
        NULL,
        (LPARAM)"Superduper");


  /* Make the window visible on the screen */
  initialized = true;
  ShowWindow (hwnd, nCmdShow);

  return true;
}



LRESULT CALLBACK EulerWindow::windowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  EulerWindow* me = reinterpret_cast<EulerWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
  if (me)
    return me->realWindowProcedure(hwnd, message, wParam, lParam);
//  MessageBox(NULL, "Failed to get pointer to class!", "Error!", MB_ICONEXCLAMATION | MB_OK);
  return DefWindowProc(hwnd, message, wParam, lParam);
}



/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK EulerWindow::realWindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int width;
  switch (message)                  /* handle the messages */
  {
  case WM_DESTROY:
    PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
    break;
  case WM_SIZE:
    if(initialized){
      MoveWindow(hEdit, 0, 0, LOWORD(lParam)/2, HIWORD(lParam), true);
      width = ListView_GetColumnWidth(hVariableList, 0) + ListView_GetColumnWidth(hVariableList, 1) + 4;
      MoveWindow(hVariableList, LOWORD(lParam)/2, 0, width, HIWORD(lParam), true);
    }
    break;
  case WM_COMMAND:
    if(LOWORD(wParam)==ID_FILE_QUIT)
      PostQuitMessage(0);
    break;
  default:                      /* for messages that we don't deal with */
    return DefWindowProc (hwnd, message, wParam, lParam);
  }

  return 0;
}

