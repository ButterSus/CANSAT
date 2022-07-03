/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_THREAD_H
#define CANSAT_THREAD_H

#include "RTOS/RTOS.h"

#define INIT_TIME 1
#define MEMORY_SIZE 1024
#define MAX_NORMAL_THREAD 8
#define MAX_TIMING_THREAD 4

typedef volatile void* stack;

class NormalThread;
class TimingThread;

class Thread {
protected:
    typedef struct{
        uint16_t PROGRAM_COUNTER;
        uint8_t STATUS_REG;
        uint8_t REG[32];
    }Context;
    static static volatile uint8_t memory[MEMORY_SIZE];
    static volatile TimingThread*timingThreads[MAX_TIMING_THREAD];
    static volatile NormalThread*normalThreads[MAX_NORMAL_THREAD];
    static uint16_t memoryUsed;
public:
    static stack mainStack;
    Thread() = default;
    Thread(void(*enableFunction)());
    static void changeThread();
};

class NormalThread : Thread {
private:
    static uint8_t counter;
public:
    struct{
        stack stackPointer;
    }information;
    NormalThread() = default;
    NormalThread(uint16_t stackSize, void(*gotoFunction)());
};

class TimingThread : Thread {
private:
    static uint8_t counter;
public:
    struct{
        uint32_t time;
        stack stackPointer;
        uint8_t interval;
    }information;
    TimingThread() = default;
    TimingThread(uint8_t interval, uint16_t stackSize, void(*gotoFunction)());
};







uint32_t getTime();

#endif //CANSAT_THREAD_H
