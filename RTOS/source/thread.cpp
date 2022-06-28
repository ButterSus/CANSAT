#define _THREAD_

/**
 * @author ButterSus
 * @date June 2022
 */

#include "RTOS/include/thread.h"
#include "RTOS/include/tools.h"

uint8_t taskCounter = 0, taskPoint = 0;
uint8_t memory[MEMORY_SIZE];
uint16_t memoryUsed = 0;

stack stackPointers[8];

Thread::Thread(void (*gotoFunction)(), int stackSize)
{
    memoryUsed += stackSize + sizeof(data);
    stack backPointer = (stack)SP;
    jmpStack(memory + memoryUsed);
    push16(gotoFunction);
    jmpStack(backPointer);
    stackPointers[taskCounter++] = memory + memoryUsed - sizeof(data);
}

ISR(TIMER0_COMP_vect, ISR_NAKED)
{
    push8(SREG);
    pushRegisters;
    jmpStack(stackPointers[(taskPoint++) % taskCounter]);
    popRegisters;
    pop8(SREG);
    reti();
}