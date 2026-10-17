#include <iostream>
#include <thread>
#include <windows.h>

void pinnedWorker()
{
    DWORD_PTR mask = 1;

    DWORD_PTR previous =
        SetThreadAffinityMask(
            GetCurrentThread(), mask
        );

    if (previous != 0)
        std::cout << "Thread successfully bound to Core 0." << std::endl;
    else
        std::cout << "Failed to set CPU affinity." << std::endl;
}

int main()
{
    std::cout << "Available hardware cores: "
              << std::thread::hardware_concurrency()
              << std::endl;

    std::thread t(pinnedWorker);
    t.join();

    return 0;
}
