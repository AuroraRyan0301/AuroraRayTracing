#ifndef PROGRESSBARH
#define PROGRESSBARH

#include "mingw.thread.h"
#include "mingw.mutex.h"

std::mutex mtx;  // 互斥量用于保护打印操作

void printProgress(int threadId, int progress)
{
    std::lock_guard<std::mutex> lock(mtx);  // 锁定互斥量

    std::cout << "Thread " << threadId << " progress: " << progress << "%" << std::endl;
}

#endif
