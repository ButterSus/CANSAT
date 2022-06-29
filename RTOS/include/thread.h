/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_THREAD_H
#define CANSAT_THREAD_H

#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef _THREAD_
#define MEMORY_SIZE 1024
#endif // _THREAD_

typedef volatile void* stack;

class Thread {
private:
    typedef struct {
        uint16_t programCounter;
        uint8_t statusRegister;
        uint8_t registers[32];
    } data;
public:
    Thread(void(*gotoFunction)(), int stackSize);
};

#endif //CANSAT_THREAD_H
