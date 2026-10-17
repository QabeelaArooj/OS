#include <iostream>
#include <windows.h>

int main()
{
    HANDLE hFile = CreateFileA(
        "async.bin",
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_FLAG_OVERLAPPED,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE)
        return 1;

    OVERLAPPED ol;
    ZeroMemory(&ol, sizeof(ol));

    ol.hEvent = CreateEventA(
        NULL, TRUE, FALSE, NULL
    );

    char buffer[1024] =
        "Asynchronous file write data packet.";

    WriteFile(
        hFile, buffer, sizeof(buffer),
        NULL, &ol
    );

    std::cout
        << "I/O initiated. Doing computation in parallel..."
        << std::endl;

    WaitForSingleObject(
        ol.hEvent, INFINITE
    );

    std::cout
        << "Asynchronous write fully committed."
        << std::endl;

    CloseHandle(ol.hEvent);
    CloseHandle(hFile);

    return 0;
}
