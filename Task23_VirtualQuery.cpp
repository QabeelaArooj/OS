#include <iostream>
#include <windows.h>

int main()
{
    int x = 10;
    MEMORY_BASIC_INFORMATION mbi;

    if (VirtualQuery(&x, &mbi, sizeof(mbi)) != 0)
    {
        std::cout << "Address: "
                  << mbi.BaseAddress << std::endl;

        std::cout << "Region Size: "
                  << mbi.RegionSize
                  << " bytes" << std::endl;

        std::cout << "State: ";

        if (mbi.State == MEM_COMMIT)
            std::cout << "MEM_COMMIT";
        else
            std::cout << "OTHER";

        std::cout << std::endl;
    }

    return 0;
}
