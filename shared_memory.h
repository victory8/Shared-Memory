//
// Created by utkugokce on 26.06.2024.
//

#ifndef MYSHAREDMEMORY_SHARED_MEMORY_H
#define MYSHAREDMEMORY_SHARED_MEMORY_H

#include <vector>
#include <mutex>
#include <cstring>
#include <iostream>
#include <thread>
#include <chrono>

class mySharedMemory {
public:
  mySharedMemory(size_t blockSize, size_t blockCount);

  int read(char* buffer, size_t bufferSize);
  int write(const char* data, size_t size);
  size_t writeIndex;
  size_t readIndex;

private:
  size_t blockSize;
  size_t blockCount;
  std::vector<std::vector<char>> memory;
  std::vector<size_t> dataSize;

  std::mutex mutex;
};

#endif //MYSHAREDMEMORY_SHARED_MEMORY_H
