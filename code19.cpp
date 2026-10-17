#include <iostream>
#include <windows.h>
#include <cstring>

int main()
{
    const char* pipeName = "\\\\.\\pipe\\MyNamedPipe";

    HANDLE pipe = CreateNamedPipeA(
        pipeName,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE |
        PIPE_READMODE_MESSAGE |
        PIPE_WAIT,
        1,
        1024,
        1024,
        0,
        NULL
    );

    if (pipe == INVALID_HANDLE_VALUE)
    {
        std::cout << "CreateNamedPipe failed." << std::endl;
        return 1;
    }

    std::cout << "Waiting for client..." << std::endl;

    BOOL connected = ConnectNamedPipe(pipe, NULL);

    if (connected || GetLastError() == ERROR_PIPE_CONNECTED)
    {
        const char* message = "Hello from Named Pipe!";
        DWORD bytesWritten;

        WriteFile(
            pipe,
            message,
            strlen(message) + 1,
            &bytesWritten,
            NULL
        );

        std::cout << "Message sent through named pipe."
                  << std::endl;
    }

    DisconnectNamedPipe(pipe);
    CloseHandle(pipe);

    return 0;
}
