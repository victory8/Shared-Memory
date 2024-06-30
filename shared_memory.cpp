//
// Created by utkugokce on 26.06.2024.
//

#include "shared_memory.h"

mySharedMemory::mySharedMemory(size_t blockSize, size_t blockCount) : blockSize(blockSize), blockCount(blockCount),
                                                                      memory(blockCount, std::vector<char>(blockSize)),
                                                                      dataSize(blockCount, 0),
                                                                      writeIndex(0), readIndex(0) {}

int mySharedMemory::write(const char* data, size_t size) {
  std::lock_guard<std::mutex> lock(mutex);

  if (size > blockSize) {
    return -1;
  }

  std::memcpy(memory[writeIndex].data(), data, size);
  dataSize[writeIndex] = size;
  writeIndex = (writeIndex + 1) % blockCount;
  return static_cast<int>(size);
}

int mySharedMemory::read(char* buffer, size_t bufferSize) {
  std::lock_guard<std::mutex> lock(mutex);

  if (readIndex == writeIndex) {
    return 0;
  }

  if (bufferSize < dataSize[readIndex]) {
    return -1;
  }

  std::memcpy(buffer, memory[readIndex].data(), dataSize[readIndex]);
  int bytesRead = dataSize[readIndex];
  dataSize[readIndex] = 0;
  readIndex = (readIndex + 1) % blockCount;
  return bytesRead;
}

