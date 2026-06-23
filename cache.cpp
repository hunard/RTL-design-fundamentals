#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <set>

struct CacheLine {
    bool valid = false;
    uint64_t tag = 0;
};

class Cache {
public:
    int totalAccesses = 0;
    int totalHits = 0;
    int totalMisses = 0;
    int compulsoryMisses = 0;
int conflictMisses = 0;

    Cache(int cacheSizeBytes, int blockSizeBytes) {
        numLines = cacheSizeBytes / blockSizeBytes;
        blockBits = std::log2(blockSizeBytes);
        indexBits = std::log2(numLines);
        lines.resize(numLines);
    }

    bool access(uint64_t address) {
        uint64_t offset = address & ((1 << blockBits) - 1);
        uint64_t index  = (address >> blockBits) & ((1 << indexBits) - 1);
        uint64_t tag    = address >> (blockBits + indexBits);

        totalAccesses++;

        if (lines[index].valid && lines[index].tag == tag) {
            totalHits++;
            return true;
        }
        totalMisses++;
uint64_t blockNumber = address >> blockBits;
if (seenBlocks.find(blockNumber) == seenBlocks.end()) {
    compulsoryMisses++;
} else {
    conflictMisses++;
}
seenBlocks.insert(blockNumber);
        lines[index] = {true, tag};
        return false;
    }

    void printStats() {
        std::cout << "\n--- Cache Stats ---" << std::endl;
        std::cout << "Total Accesses: " << totalAccesses << std::endl;
        std::cout << "Hits:           " << totalHits << std::endl;
        std::cout << "Misses:         " << totalMisses << std::endl;
        std::cout << "Hit Rate:       " << (100.0 * totalHits / totalAccesses) << "%" << std::endl;
        std::cout << "Compulsory Misses: " << compulsoryMisses << std::endl;
std::cout << "Conflict Misses:   " << conflictMisses << std::endl;
    }

private:
    int numLines, blockBits, indexBits;
    std::vector<CacheLine> lines;
    std::set<uint64_t> seenBlocks;
};

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