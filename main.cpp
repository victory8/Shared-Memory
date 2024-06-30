#include <iostream>
#include <thread>

#include "shared_memory.h"

void writer(mySharedMemory& shm) {
  const char* message = "Hello, World!";
  while (true) {
    shm.write(message, std::strlen(message) + 1);
    std::cout << "writeIndex= " << shm.writeIndex << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void reader(mySharedMemory& shm) {
  char buffer[1500];
  while (true) {
    int bytesRead = shm.read(buffer, sizeof(buffer));
    if (bytesRead > 0) {
      std::cout << "readIndex= " << shm.readIndex << std::endl;
      std::cout << "Read message: " << buffer << " (" << bytesRead << " bytes)" << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

int main() {
  mySharedMemory shm(1500,50);
  std::thread writerThread(writer, std::ref(shm));  //shared object
  std::thread readerThread(reader, std::ref(shm));  //shared object

  writerThread.detach();
  readerThread.detach();

  while(true) {}

  return 0;
}
