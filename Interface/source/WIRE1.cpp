/**
 * @author ButterSus
 * @date June 2022
 */

#include "WIRE1.h"

WIRE1::WIRE1(volatile uint8_t*port, volatile uint8_t*ddr, volatile uint8_t*pin, uint8_t num)
{
    this->port = port;
    this->ddr = ddr;
    this->pin = pin;
    this->num = num;
}

void WIRE1::reset()
{
    *this->ddr|=this->num;
    *this->port&=~this->num;
    _delay_us(480);
    *this->ddr&=~this->num;
    *this->port&=~this->num;
    _delay_us(70);
    _delay_us(410);
}

bool WIRE1::readBit()
{
    *this->ddr|=(this->num);
    *this->port&=~(this->num);
    _delay_us(6);
    *this->ddr&=~(this->num);
    *this->port|=(this->num);
    _delay_us(9);
    return (*this->pin & (this->num)) != 0;
}

uint8_t WIRE1::read()
{
    uint8_t bit, result = 0;
    for(uint8_t i = 0; i < 8; i++)
    {
        result >>= 1;
        *this->ddr|=this->num;
        *this->port&=~this->num;
        _delay_us(6);
        *this->ddr&=~this->num;
        *this->port|=this->num;
        _delay_us(9);
        bit = ((*this->pin & this->num) != 0) << 7;
        _delay_us(55);
        result |= bit;
    }
    return result;
}

void WIRE1::write(uint8_t data)
{
    for(uint8_t iter = 0; iter < 8; iter++){
        *this->ddr|=num;
        *this->port&=~num;
        _delay_us(6);
        if(data & (1 << iter))
        {
            *this->ddr&=~this->num;
            *this->port|=this->num;
        }
        else
        {
            *this->ddr|=this->num;
            *this->port&=~this->num;
        };
        _delay_us(64);
        *this->ddr&=~this->num;
        *this->port&=~this->num;
    }
}
