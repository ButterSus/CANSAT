/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_THREAD_H
#define CANSAT_THREAD_H

#include "TIMER0.h"

#ifdef _THREAD_
#define MEMORY_SIZE 2048
#define THREAD_MAX 8
#endif // _THREAD_

typedef volatile void*stack;

class Thread {
private:
    typedef struct {
        uint16_t programCounter;
        uint8_t statusRegister;
        uint8_t registers[32];
    } data;
public:
    Thread(void(*gotoFunction)(), int stackSize, uint8_t times);
    static void go(TIMER0 interfaceTimer0);
};

#endif //CANSAT_THREAD_H
