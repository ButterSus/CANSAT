/**
 * @author ButterSus
 * @date May 2022
 * @name DS18B20
 */

#include <stdint.h>
#include "WIRE1.h"
#include "settings.h"

void DS18B20_beReadyToFight(uint8_t*id){
    WIRE1_reset<&WIRE1_PORT, &WIRE1_DDR, &WIRE1_PIN, 1<<WIRE1_NUM>();
    if(id == nullptr){
        WIRE1_write<&WIRE1_PORT, &WIRE1_DDR, &WIRE1_PIN, 1<<WIRE1_NUM>(WIRE1_SKIPROM);
    }
    else{
        WIRE1_write<&WIRE1_PORT, &WIRE1_DDR, &WIRE1_PIN, 1<<WIRE1_NUM>(WIRE1_MATCHROM);
        for(uint8_t iter = 0; iter < 8; iter++){
            WIRE1_write<&WIRE1_PORT, &WIRE1_DDR, &WIRE1_PIN, 1<<WIRE1_NUM>(id[iter]);
        }
    }
}

float DS18B20_read(uint8_t*id){
    bool isDone;
    DS18B20_beReadyToFight(id);
    WIRE1_write<&WIRE1_PORT, &WIRE1_DDR, &WIRE1_PIN, 1<<WIRE1_NUM>(CMD_CONVERT_T);
    _delay_ms(800);
    DS18B20_beReadyToFight(id);
    WIRE1_write<&WIRE1_PORT, &WIRE1_DDR, &WIRE1_PIN, 1<<WIRE1_NUM>(CMD_READ_SPD);
    int16_t buffer = WIRE1_read<&WIRE1_PORT, &WIRE1_DDR, &WIRE1_PIN, 1<<WIRE1_NUM>();
    buffer |= (int16_t)WIRE1_read<&WIRE1_PORT, &WIRE1_DDR, &WIRE1_PIN, 1<<WIRE1_NUM>() << 8;
    float result = buffer / 16.0f;
    return result;
}
