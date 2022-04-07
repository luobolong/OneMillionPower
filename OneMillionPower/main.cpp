#include <iostream>
#include "LargeInt.h"
#define MAX_DIGITS 0x400000 // 512 KB

int main()
{
    const size_t s = 10;
    std::bitset<MAX_DIGITS> base = std::bitset<MAX_DIGITS>{ 10 };
    LargeInt<MAX_DIGITS> li = LargeInt<MAX_DIGITS>(base, 4);
    try {
        li.pow(1000000);
    }
    catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
    size_t len = li.get_len();
    //for (size_t i = 0; i < len; ++i)
    //{
    //    std::cout << li.get_dta()[len - i - 1];
    //}
    //std::cout << std::endl;
    std::cout << "Length: " << len;
    return 0;
}
