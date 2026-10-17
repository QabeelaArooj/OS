#include <iostream>
#include <windows.h>

int main()
{
    HANDLE hFile = CreateFileA(
        "guard_test.txt",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        0,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE)
        return 1;

    if (LockFile(hFile, 0, 0, 100, 0))
    {
        std::cout
            << "Byte range [0-100] locked successfully."
            << std::endl;

        UnlockFile(hFile, 0, 0, 100, 0);

        std::cout
            << "Byte range unlocked."
            << std::endl;
    }

    CloseHandle(hFile);

    return 0;
}
