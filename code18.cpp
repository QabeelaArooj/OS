#include <iostream>
#include <windows.h>
#include <cstring>

int main()
{
    const char* name = "Local\\MySharedMemory";

    HANDLE hMapFile = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        1024,
        name
    );

    if (hMapFile == NULL)
    {
        std::cout << "CreateFileMapping failed." << std::endl;
        return 1;
    }

    char* sharedMemory = (char*)MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        1024
    );

    if (sharedMemory == NULL)
    {
        std::cout << "MapViewOfFile failed." << std::endl;
        CloseHandle(hMapFile);
        return 1;
    }

    strcpy(sharedMemory, "Hello from shared memory!");

    std::cout << "Message written to shared memory:"
              << std::endl;

    std::cout << sharedMemory << std::endl;

    UnmapViewOfFile(sharedMemory);
    CloseHandle(hMapFile);

    return 0;
}
