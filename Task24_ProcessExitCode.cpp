#include <iostream>
#include <windows.h>

int main()
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    si.cb = sizeof(si);

    char command[] = "cmd.exe /C exit 42";

    if (CreateProcessA(
        NULL, command, NULL, NULL,
        FALSE, 0, NULL, NULL, &si, &pi))
    {
        WaitForSingleObject(
            pi.hProcess, INFINITE
        );

        DWORD exitCode = 0;

        GetExitCodeProcess(
            pi.hProcess, &exitCode
        );

        std::cout
            << "Child process exited with code: "
            << exitCode << std::endl;

        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }

    return 0;
}
