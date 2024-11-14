#include <iostream>
#include <pthread.h>
#include <time.h>
#include <evl/evl.h>
#include <evl/clock.h>
#include <error.h>
#include <errno.h>
#include <evl/sched.h>
#include <evl/thread.h>

#define CYCLES 10
#define BILLION 1000000000
#define MILLION 1000000

timespec beginTimeArray[CYCLES];
pthread_t timingThread;

timespec timePeriod = {0, 1000000}; //1000000 nanoseconds (1 ms)
timespec beginTime;
timespec nextBeginTime;
timespec endTime;

double cycleTime;

void* timerFunction(void *arg) {
    evl_attach_self("timingThread:%d"); //Create evl thread from POSIX threaf
    for (int i = 0; i < CYCLES; i++)
    {
        evl_read_clock(EVL_CLOCK_MONOTONIC, &beginTime); //Read off current time
        beginTimeArray[i] = beginTime;
        for (int j = 0; j < 10000; j++)    //bogus function to take time
        {
            int a = j * j;
        }
        if((beginTime.tv_nsec + timePeriod.tv_nsec) > BILLION){ //prevent storing more than 1 second of nanoseconds in case of rollover
            nextBeginTime.tv_sec = beginTime.tv_sec + 1;
            nextBeginTime.tv_nsec = timePeriod.tv_nsec - (BILLION - beginTime.tv_nsec);
        }
        else{
            nextBeginTime.tv_sec = beginTime.tv_sec;
            nextBeginTime.tv_nsec = beginTime.tv_nsec + timePeriod.tv_nsec;
        }

        evl_printf("%d %d %d %d \n", beginTime.tv_sec , beginTime.tv_nsec, nextBeginTime.tv_sec, nextBeginTime.tv_nsec); //DEBUG
        int b = evl_sleep_until(EVL_CLOCK_MONOTONIC, &nextBeginTime);   //Wait until a millisecond has passed
       
    return NULL;
}

int main() {
    std::cout << "Thread start." << std::endl;
    pthread_create(&timingThread, NULL, &timerFunction, NULL);

    pthread_join(timingThread, NULL);
    std::cout << "Back in the main thread." << std::endl;

    double sum = 0;
    for (size_t i = 0; i < CYCLES -1; ++i)  //run the loop and calculate how long it took
    {
        if(beginTimeArray[i+1].tv_nsec >= beginTimeArray[i].tv_nsec){
            cycleTime = (beginTimeArray[i + 1].tv_nsec - beginTimeArray[i].tv_nsec) / 1000000.0;
        }
        else{
            cycleTime = (1000000000 - (beginTimeArray[i].tv_nsec - beginTimeArray[i+1].tv_nsec)) / 1000000.0;
        }
        std::cout << "Iteration " << i + 1 << " - ";
        std::cout << "Time between iterations: " << cycleTime << "ms " << std::endl;
        sum += cycleTime;
    }

    double averageTime = sum / CYCLES;
    std::cout << "Average cycle Time over " << CYCLES << " iterations: " << averageTime << "ms" << std::endl;
    
    return 0;
}
