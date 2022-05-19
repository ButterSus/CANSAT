/*! TODO: MAKE DOCS */

/**
 * @author ButterSus
 * @date May 2022
 * @name 1-WIRE
 */

#ifndef CANSAT_WIRE1_H
#define CANSAT_WIRE1_H

#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include "PORTS.h"

#define WIRE1_SKIPROM 0xCC
#define WIRE1_MATCHROM 0x55

template <volatile uint8_t**port, volatile uint8_t**ddr, volatile uint8_t**pin, uint8_t num>

void WIRE1_reset(){
    **ddr=**ddr|(num);
    **port=**port&~(num);
    _delay_us(480);
    **ddr=**ddr&~(num);
    **port=**port&~(num);
    _delay_us(70);
    _delay_us(410);
}

template <volatile uint8_t**port, volatile uint8_t**ddr, volatile uint8_t**pin, uint8_t num>

bool WIRE1_bitread(){
    **ddr=**ddr|(num);
    **port=**port&~(num);
    _delay_us(6);
    **ddr=**ddr&~(num);
    **port=**port|(num);
    _delay_us(9);
    return (**pin & (num)) != 0;
}

template <volatile uint8_t**port, volatile uint8_t**ddr, volatile uint8_t**pin, uint8_t num>

uint8_t WIRE1_read(){
    volatile uint8_t bit, result=0;
    for(uint8_t i = 0; i < 8; i++)
    {
        result >>= 1;
        **ddr=**ddr|(num);
        **port=**port&~(num);
        _delay_us(6);
        **ddr=**ddr&~(num);
        **port=**port|(num);
        _delay_us(9);
        bit = ((**pin & (num)) != 0) ? false : (1 << 7);
        _delay_us(55);
        result |= bit;
    };
    return result;
}

template <volatile uint8_t**port, volatile uint8_t**ddr, volatile uint8_t**pin, uint8_t num>

void WIRE1_write(uint8_t value){
    for(uint8_t iter = 0; iter < 8; iter++){
        **ddr=**ddr|(num);
        **port=**port&~(num);
        _delay_us(6);
        if(value & (1 << iter))
        {
            **ddr=**ddr&~(num);
            **port=**port|(num);
        }
        else
        {
            **ddr=**ddr|(num);
            **port=**port&~(num);
        };
        _delay_us(64);
        **ddr=**ddr&~(num);
        **port=**port&~(num);
    }
}

#endif //CANSAT_WIRE1_H
