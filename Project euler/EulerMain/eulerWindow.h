#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <string>
#include <commctrl.h>
#include "variable.h"

#ifndef EULERWINDOW
#define EULERWINDOW

enum
{
    ID_FILE_RUN,
    ID_FILE_QUIT,
    IDC_MAIN_EDIT,
    IDC_VARIABLE_LIST
};

class EulerWindow{
private:
  std::string title;
  Variable* variable;
  LRESULT CALLBACK realWindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
  HWND hEdit;
  HWND hVariableList;
  bool initialized;
public:
  EulerWindow();
  static LRESULT CALLBACK windowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
  bool createEulerWindow (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow);
};

#endif // EULERWINDOW
