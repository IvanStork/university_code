#include <iostream>
#include <pthread.h>
#include <time.h>

#define CYCLES 1000

timespec beginTimeArray[CYCLES];
pthread_t timingThread;

timespec timePeriod = {0, 1000000}; //1000000 nanoseconds (1 ms)
timespec sleep;
timespec beginTime;
timespec endTime;

double cycleTime;

void* timerFunction(void *arg) {
    for (int i = 0; i < CYCLES; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &beginTime); //get the current time
        beginTimeArray[i] = beginTime;
        for (int j = 0; j < 100000; j++)    //bogus function to take time
        {
            int a = j * j;
        }
        clock_gettime(CLOCK_MONOTONIC, &endTime);
        if(endTime.tv_nsec >= beginTime.tv_nsec){   //calculate how long to sleep for
            sleep.tv_nsec = timePeriod.tv_nsec - (endTime.tv_nsec - beginTime.tv_nsec);
        }
        else{
            sleep.tv_nsec = timePeriod.tv_nsec - (beginTime.tv_nsec - endTime.tv_nsec);
        }
        clock_nanosleep(CLOCK_MONOTONIC, 0, &sleep, NULL); 
    }
    return NULL;
}

int main() {
    std::cout << "Thread start." << std::endl;
    pthread_create(&timingThread, NULL, &timerFunction, NULL);

    pthread_join(timingThread, NULL);
    std::cout << "Back in the main thread." << std::endl;

    double sum = 0;
    for (size_t i = 0; i < CYCLES -1; ++i)  //run the loop and calculate the runtime
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
