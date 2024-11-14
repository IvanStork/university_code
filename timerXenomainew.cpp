#include <iostream>
#include <pthread.h>
#include <time.h>
#include <vector>
#include <evl/clock.h>


std::vector<timespec> beginTimeArray;
std::vector<timespec> endTimeArray;
std::vector<long> averageTimeArray;
pthread_t timingThread;

struct timespec timePeriod = {0, 1000000}; //1000000 nanoseconds (1 ms)
struct timespec sleep;
struct timespec beginTime;
struct timespec endTime;
long timeTaken;
int sum = 0;

long averageTime;

void* timerFunction(void *arg) {
    sleep.tv_sec = 0;
    for (int i = 0; i < 11; i++)
    {
        evl_read_clock(EVL_CLOCK_MONOTONIC, &beginTime);
        for (int j = 0; j < 10000; j++) {
            int a = j * j;
        }

        beginTimeArray.push_back(beginTime);
        evl_read_clock(EVL_CLOCK_MONOTONIC, &endTime);
        endTimeArray.push_back(endTime);

        std::cout << beginTime.tv_nsec << std::endl;
        std::cout << endTime.tv_nsec << std::endl;
        sleep.tv_nsec = (timePeriod.tv_nsec - 1000 * (endTime.tv_nsec - beginTime.tv_nsec)) / 1000;
        std::cout << sleep.tv_nsec << std::endl;
        evl_usleep(sleep.tv_nsec);
    }
    return NULL;
}

int main() {
    std::cout << "Thread start." << std::endl;
    pthread_create(&timingThread, NULL, &timerFunction, NULL);

    pthread_join(timingThread, NULL);

    for (size_t i = 0; i < beginTimeArray.size()-1; ++i) {
        timeTaken = beginTimeArray[i + 1].tv_nsec - beginTimeArray[i].tv_nsec;
        std::cout << "Iteration " << i + 1 << " - ";
        std::cout << "Time between iterations: " << timeTaken << "ns " << std::endl;
        averageTimeArray.push_back(timeTaken);
    }
    for (int i = 0; i < averageTimeArray.size(); ++i){
        sum += averageTimeArray[i];
    }
    averageTime = sum / averageTimeArray.size();

    std::cout << "Average time between iterations: " << averageTime << "ns" << std::endl;

    std::cout << "Back in the main thread." << std::endl;
    return 0;
}
