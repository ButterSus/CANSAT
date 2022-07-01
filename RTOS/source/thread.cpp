#define _THREAD_

/**
 * @author ButterSus
 * @date June 2022
 */

#include "RTOS/include/thread.h"
#include "RTOS/include/tools.h"
#include "TIMER0.h"

volatile uint8_t taskCounter = 0;
volatile int32_t taskPoint = 0;
volatile uint8_t memory[MEMORY_SIZE];
volatile uint16_t memoryUsed = 0;

stack stackPointers[8];

Thread::Thread(void (*gotoFunction)(), int stackSize)
{
    memoryUsed += stackSize + sizeof(data) - 1;
    stack backPointer = (stack)SP;
    jmpStack(memory + memoryUsed);
    push16(gotoFunction);
    jmpStack(backPointer);
    stackPointers[taskCounter++] = memory + memoryUsed - sizeof(data);
}

void Thread::go(TIMER0 interfaceTimer0)
{
    sei();
    interfaceTimer0.enable();
    jmpStack(memory + memoryUsed - sizeof(data));
    popRegisters;
    pop8(SREG);
    ret;
}

ISR(TIMER0_COMP_vect, ISR_NAKED)
{
    {
        TCNT0 = 0;
    }
    push8(SREG);
    pushRegisters;
    stackPointers[(taskPoint - 1) % taskCounter] = (stack)SP;
    jmpStack(stackPointers[(taskPoint++) % taskCounter]);
    popRegisters;
    pop8(SREG);
    reti();
}
