/**
 * @author ButterSus
 * @date June 2022
 */

#include "RTOS/include/thread.h"
#include "RTOS/include/tools.h"

Thread::Thread(void(*enableFunction)())
{
    sei();
    enableFunction();
    mainStack = (stack)SP;
    jmpStack(&memory[memoryUsed] - sizeof(Context));
    popRegisters;
    pop8(SREG);
    ret;
}

NormalThread::NormalThread(uint16_t stackSize, void (*gotoFunction)())
{
    memoryUsed += stackSize + sizeof(Context);
    stack backPointer = (stack)SP;
    jmpStack(&memory[memoryUsed]);
    push16(gotoFunction);
    jmpStack(backPointer);
    this->information.stackPointer = &memory[memoryUsed] - sizeof(Context);
    normalThreads[NormalThread::counter++] = this;
}

TimingThread::TimingThread(uint8_t interval, uint16_t stackSize, void(*gotoFunction)())
{
    this->information.interval = interval;
    this->information.time = interval + getTime() + INIT_TIME;
    memoryUsed += stackSize + sizeof(Context);
    stack backPointer = (stack)SP;
    jmpStack(&memory[memoryUsed]);
    push16(gotoFunction);
    jmpStack(backPointer);
    this->information.stackPointer = &memory[memoryUsed] - sizeof(Context);
    timingThreads[TimingThread::counter++] = this;
}

void Thread::changeThread()
{
    while(timingThreads[0]->information.time < getTime()){
    }
}

ISR(TIMER0_COMP_vect, ISR_NAKED){
    push8(SREG);
    pushRegisters;
    jmpStack(Thread::mainStack);
    Thread::changeThread();
    popRegisters;
    pop8(SREG);
    reti();
}

//volatile uint8_t taskCounter = 0;
//volatile int32_t taskPoint = 0;
//volatile uint8_t memory[MEMORY_SIZE];
//volatile uint16_t memoryUsed = 0;
//
//stack mainStack;
//NormalThread normalThreads[MAX_NORMAL_THREAD];
//
//Thread::Thread(void (*gotoFunction)(), int stackSize)
//{
//    memoryUsed += stackSize + sizeof(data) - 1;
//    stack backPointer = (stack)SP;
//    jmpStack(memory + memoryUsed);
//    push16(gotoFunction);
//    jmpStack(backPointer);
//    stackPointers[taskCounter++] = memory + memoryUsed - sizeof(data);
//}
//
//void Thread::go(TIMER0 interfaceTimer0)
//{
//    sei();
//    interfaceTimer0.enable();
//    mainStack = (stack)SP;
//    jmpStack(memory + memoryUsed - sizeof(data));
//    popRegisters;
//    pop8(SREG);
//    ret;
//}
//
//void Thread::next()
//{
//
//}
//
//ISR(TIMER0_COMP_vect, ISR_NAKED)
//{
//    TCNT0 = 0;
//    push8(SREG);
//    pushRegisters;
//    {
//        jmpStack(mainStack);
//        Thread::next();
//    }
//
////    stackPointers[(taskPoint - 1) % taskCounter] = (stack)SP;
////    jmpStack(stackPointers[(taskPoint++) % taskCounter]);
//    popRegisters;
//    pop8(SREG);
//    reti();
//}
