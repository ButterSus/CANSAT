#define _DS18B20_

/**
 * @author ButterSus
 * @date June 2022
 */

#include "DS18B20.h"

DS18B20::DS18B20(uint8_t*ID)
{
    this->ID = ID;
    this->interfaceWIRE1 = WIRE1(&WIRE1_PORT, &WIRE1_DDR, &WIRE1_PIN, 1 << WIRE1_NUM);
}

void DS18B20::sendID()
{
    this->interfaceWIRE1.reset();
    if(this->ID == nullptr){
        this->interfaceWIRE1.write(WIRE1_SKIPROM);
    }
    else{
        this->interfaceWIRE1.write(WIRE1_MATCHROM);
        for(uint8_t iter = 0; iter < 8; iter++){
            this->interfaceWIRE1.write(ID[iter]);
        }
    }
}

void DS18B20::measure()
{
    sendID();
    this->interfaceWIRE1.write(CMD_CONVERT_T);
}

float DS18B20::read()
{
    sendID();
    this->interfaceWIRE1.write(CMD_READ_SCRATCHPAD);
    int16_t buffer = this->interfaceWIRE1.read();
    buffer |= (int16_t)this->interfaceWIRE1.read() << 8;
    float result = buffer / 16.0f;
    return result;
}


