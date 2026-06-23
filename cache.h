#pragma once
#include <vector>
#include <set>
#include <cstdint>

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

    Cache(int cacheSizeBytes, int blockSizeBytes);
    bool access(uint64_t address);
    void printStats();

private:
    int numLines, blockBits, indexBits;
    std::vector<CacheLine> lines;
    std::set<uint64_t> seenBlocks;
};