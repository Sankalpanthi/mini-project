#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <tchar.h>
#include <windows.h>
#include <ctime>
#include<string>
using namespace std;
string password="space for random pass generation";
int length=password.length();
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
HWND textfield , button1, button2; //handle to the text and button respectively
/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
int getKey(int x)
{
    static int u=0;// to generate unique characters at every character generation
    int t=static_cast<int> (time(NULL)); // type casting the time_t type variable to integer type
    int key = (t+u++) % x;
    return key;
}
void generate_password()
{
    password="";
    length=12+getKey(21); //will generate random numbers from 0 to 20 and addition of 12 will give random numbers in range 12 to 32
    //String whose characters will be used to build password
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string s_symbol = "!@#$%&";
    string number = "0123456789";
    //initializing local variables
    int key, count_alphabet = 0, count_ALPHABET = 0, count_number = 0, count_s_symbol = 0;
    //Count will store the length of the password being created,
    //initially this will be zero
    int count = 0;
    while (count < length) {
        // getKey() function will return a number 1 to 4 and will use to select one of the above defined string (i.e alphabet or ALPHABET or s_symbol or number )
        // 0 is for string alphabet
        // 1 is for string ALPHABET
        // 2 is for string number
        // 3 is for string s_symbol
        int k = getKey(4);

        //for the first character of password it is mentioned that, it should be a lowercase letter
        if (count == 0)
            k=0;
        //for the last character of password it is mentioned that, it should be an uppercase letter
        else if (count == length-1)
            k=1;
        switch (k)
        {
        case 0:
            // following if condition will check if minimum requirement of alphabet character has been fulfilled or not
            if ((count_alphabet == 2) && (count_number == 0 || count_ALPHABET == 0 || count_ALPHABET == 1 || count_s_symbol == 0))
                break;
            key = getKey(26);
            password = password + alphabet[key];
            count_alphabet++;
            count++;
            break;

        case 1:
            // following if condition will check if minimum requirement of ALPHABET character has been fulfilled or not
            if ((count_ALPHABET == 2) && (count_number == 0 || count_alphabet == 0 || count_alphabet == 1 || count_s_symbol == 0))
                break;
            key = getKey(26);
            password = password + ALPHABET[key];
            count_ALPHABET++;
            count++;
            break;

        case 2:
            // following if condition will check if minimum requirement of Numbers  has been fulfilled or not
            if ((count_number == 1) && (count_alphabet == 0 || count_alphabet == 1 || count_ALPHABET == 1 || count_ALPHABET == 0 || count_s_symbol == 0))
                break;
            key = getKey(10);
            password = password + number[key];
            count_number++;
            count++;
            break;

        case 3:
            // following if condition will check if minimum requirement of special symbol character has been fulfilled or not
            if ((count_s_symbol == 1) && (count_alphabet == 0 || count_alphabet == 1 || count_ALPHABET == 0 || count_ALPHABET == 1 || count_number == 0))
                break;
            key = getKey(6);
            password = password + s_symbol[key];
            count_s_symbol++;
            count++;
            break;
        }
    }

}
int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("RANDOM PASSWORD GENERATOR"),       /* Title Text */
           WS_MINIMIZEBOX | WS_SYSMENU, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           400,                 /* The programs width */
           200,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    char temp[33];
    for(int i=0;i<length;i++)
        temp[i]=password.at(i);
    temp[length]='\0';
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:                   // to add buttons,text etc to your window
            textfield = CreateWindow("STATIC",temp,
                                     WS_VISIBLE | WS_CHILD | WS_BORDER, //its a child window and is visible
                                     20 ,20,   //window will be 20 pixels right and 20 down to main window
                                     300 ,20,  //300 wide and 20 height
                                     hwnd ,NULL, NULL, NULL
                                     );
            button1 = CreateWindow("BUTTON","Generate password",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER, //its a child window,has border and is visible
                                  70 ,50, //window will be 70 pixels right and 50 down to main window
                                  200, 20, //200 wide and 20 height
                                  hwnd,
                                  (HMENU) 1 ,  // for executing a sequence when the button is clicked
                                  NULL, NULL);
            button2 = CreateWindow("BUTTON","Exit",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER, //its a child window,has border and is visible
                                  300 ,120, //window will be 20 pixels right and 50 down to main window
                                  80, 20, //80 wide and 20 height
                                  hwnd,
                                  (HMENU) 2 ,  // for executing a sequence when the button is clicked
                                  NULL, NULL);
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
            case 1:
                generate_password();
                for(int i=0;i<length;i++)
                      temp[i]=password.at(i);
                temp[length]='\0';
                DestroyWindow(textfield);
                textfield = CreateWindow("EDIT",temp,
                                     WS_VISIBLE | WS_CHILD , //its a child window and is visible
                                     20 ,20,   //window will be 20 pixels right and 20 down to main window
                                     300 ,20,  //300 wide and 20 height
                                     hwnd ,NULL, NULL, NULL
                                     );
                ::MessageBeep(MB_OK); //to play a beep sound when button is clicked
                ::MessageBox(hwnd,"You may copy the generated password from the textbox","PASSWORD GENERATED!",MB_OK); //displays a message box with message "Button was clicked"
                break;
            case 2:
                PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
                break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }


    return 0;
}
