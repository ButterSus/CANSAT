/**
 * @author ButterSus
 * @date June 2022
 */

#ifndef CANSAT_TOOLS_H
#define CANSAT_TOOLS_H

#include <avr/io.h>

/*! signed two bytes into one short in Little Endian */
#define sb2l(b, a) int16_t(((uint16_t)(b) << 8) | (uint16_t)(a))
/*! signed two bytes into one short in Big Endian */
#define sb2b(a, b) int16_t(((uint16_t)(b) << 8) | (uint16_t)(a))
/*! unsigned two bytes into one short in Little Endian */
#define ub2l(b, a) uint16_t(((uint16_t)(b) << 8) | (uint16_t)(a))
/*! unsigned two bytes into one short in Big Endian */
#define ub2b(a, b) uint16_t(((uint16_t)(b) << 8) | (uint16_t)(a))
/*! signed four bytes into one long in Little Endian */
#define sb4l(b, a) int32_t(((uint32_t)(b) << 16) | (uint32_t)(a))
/*! signed four bytes into one long in Big Endian */
#define sb4b(a, b) int32_t(((uint32_t)(b) << 16) | (uint32_t)(a))
/*! unsigned four bytes into one long in Little Endian */
#define ub4l(b, a) uint32_t(((uint32_t)(b) << 16) | (uint32_t)(a))
/*! unsigned four bytes into one long in Big Endian */
#define ub4b(a, b) uint32_t(((uint32_t)(b) << 16) | (uint32_t)(a))

#define jmpStack(x) asm volatile("out %[_SPL], %A[_MEM]\r\nout %[_SPH], %B[_MEM]\r\n"::[_SPL]"i"(_SFR_IO_ADDR(SPL)),\
[_SPH]"i"(_SFR_IO_ADDR(SPH)),[_MEM]"r"(x + sizeof(x)))
#define low(x) (x & 0xFF)
#define high(x) ((x >> 8) & 0xFF)
#define pass asm volatile("nop")
#define swap(x) asm volatile("swap %[a]" : [a]"=&r"(x) : "[a]"(x))
#define call asm volatile("call _next_%=\r\n_next_%=:")
#define ret asm volatile("ret")
#define pushRegisters asm volatile("push r31\n\tpush r30\n\tpush r29\n\tpush r28\n\tpush r27\n\tpush r25\n\tpush r24\n\t"\
"push r23\n\tpush r22\n\tpush r21\n\tpush r20\n\tpush r19\n\tpush r18\n\tpush r17\n\tpush r16\n\tpush r15\n\t"\
"push r14\n\tpush r13\n\tpush r12\n\tpush r11\n\tpush r10\n\tpush r9\n\tpush r8\n\tpush r7\n\tpush r6\n\tpush r5\n\t"\
"push r4\n\tpush r3\n\tpush r2\n\tpush r1\n\tpush r0")
#define popRegisters asm volatile("pop r0\n\tpop r1\n\tpop r2\n\tpop r3\n\tpop r4\n\tpop r5\n\tpop r6\n\tpop r7\n\t" \
"pop r8\n\tpop r9\n\tpop r10\n\tpop r11\n\tpop r12\n\tpop r13\n\tpop r14\n\tpop r15\n\tpop r16\n\tpop r17\n\tpop r18\n\t" \
"pop r19\n\tpop r20\n\tpop r21\n\tpop r22\n\tpop r23\n\tpop r24\n\tpop r25\n\tpop r26\n\tpop r27\n\tpop r28\n\tpop r29\n\t" \
"pop r30\n\tpop r31")

#endif //CANSAT_TOOLS_H
