#include "cache.h"
#include <iostream>
#include <cmath>

Cache::Cache(int cacheSizeBytes, int blockSizeBytes) {
    numLines = cacheSizeBytes / blockSizeBytes;
    blockBits = std::log2(blockSizeBytes);
    indexBits = std::log2(numLines);
    lines.resize(numLines);
}

bool Cache::access(uint64_t address) {
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

void Cache::printStats() {
    std::cout << "\n--- Cache Stats ---" << std::endl;
    std::cout << "Total Accesses:    " << totalAccesses << std::endl;
    std::cout << "Hits:              " << totalHits << std::endl;
    std::cout << "Misses:            " << totalMisses << std::endl;
    std::cout << "Hit Rate:          " << (100.0 * totalHits / totalAccesses) << "%" << std::endl;
    std::cout << "Compulsory Misses: " << compulsoryMisses << std::endl;
    std::cout << "Conflict Misses:   " << conflictMisses << std::endl;
}