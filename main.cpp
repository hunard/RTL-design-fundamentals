#include <iostream>
#include "cache.h"

int main() {
    Cache c(1024, 32);

    uint64_t testAddresses[] = {0x0, 0x400, 0x0};
    for (auto addr : testAddresses) {
        bool hit = c.access(addr);
        std::cout << "Address 0x" << std::hex << addr
                  << " -> " << (hit ? "HIT" : "MISS") << std::endl;
    }

    c.printStats();
}