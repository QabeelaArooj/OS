#include <iostream>
#include <thread>
#include <windows.h>

SRWLOCK rw_lock = SRWLOCK_INIT;
int sharedData = 100;

void reader(int id)
{
    AcquireSRWLockShared(&rw_lock);

    std::cout
        << "Reader " << id
        << " read value: "
        << sharedData << std::endl;

    ReleaseSRWLockShared(&rw_lock);
}

void writer(int val)
{
    AcquireSRWLockExclusive(&rw_lock);

    sharedData = val;

    std::cout
        << "Writer updated value to: "
        << sharedData << std::endl;

    ReleaseSRWLockExclusive(&rw_lock);
}

int main()
{
    std::thread r1(reader, 1);
    std::thread r2(reader, 2);
    std::thread w1(writer, 200);
    std::thread r3(reader, 3);

    r1.join();
    r2.join();
    w1.join();
    r3.join();

    return 0;
}
