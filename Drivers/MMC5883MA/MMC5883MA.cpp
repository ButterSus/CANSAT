/**
 * @author ButterSus
 * @date 06.05.2022
 * @name MMC5883MA
 */

#include "settings.h"
#include "axes.h"
#include "I2C.h"

axes MMC5883MA_axes;

void MMC5883MA_init(){
//    I2C_send(REG_MMC5883MA, REG_INTERNAL_CONTROL_0_VALUE, REG_INTERNAL_CONTROL_0);
//    I2C_send(REG_MMC5883MA, REG_INTERNAL_CONTROL_1_VALUE, REG_INTERNAL_CONTROL_1);
//    I2C_send(REG_MMC5883MA, REG_INTERNAL_CONTROL_2_VALUE, REG_INTERNAL_CONTROL_2);
    I2C_start();
    TWDR = REG_MMC5883MA & ~1;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    TWDR = REG_INTERNAL_CONTROL_0;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    TWDR = REG_INTERNAL_CONTROL_0_VALUE;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    I2C_end();
}

axes*MMC5883MA_read(){
    I2C_start();
    TWDR = REG_MMC5883MA & ~1;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    TWDR = REG_INTERNAL_CONTROL_0;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    TWDR = 1;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    I2C_end();


    uint8_t result = 0;

    while((result & 1) == 0){
        I2C_start();

        TWDR = REG_MMC5883MA & ~1;
        TWCR = (1<<TWINT)|(1<<TWEN);
        while (!(TWCR & (1<<TWINT)));

        TWDR = REG_STATUS;
        TWCR = (1<<TWINT)|(1<<TWEN);
        while (!(TWCR & (1<<TWINT)));

        TWDR = REG_MMC5883MA | 1;
        TWCR = (1<<TWINT)|(1<<TWEN);
        while (!(TWCR & (1<<TWINT)));

        TWCR = (1<<TWINT)|(1<<TWEN);
        while(!(TWCR & (1<<TWINT)));
        result = TWDR;

        I2C_end();
    }
    I2C_start();

    TWDR = REG_MMC5883MA & ~1;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    TWDR = REG_X;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    TWDR = REG_MMC5883MA | 1;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!(TWCR & (1<<TWINT)));
    MMC5883MA_axes.x = TWDR;

    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!(TWCR & (1<<TWINT)));
    MMC5883MA_axes.x = (int16_t)TWDR << 8;

    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!(TWCR & (1<<TWINT)));
    MMC5883MA_axes.y = TWDR;

    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!(TWCR & (1<<TWINT)));
    MMC5883MA_axes.y = (int16_t)TWDR << 8;

    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!(TWCR & (1<<TWINT)));
    MMC5883MA_axes.z = TWDR;

    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!(TWCR & (1<<TWINT)));
    MMC5883MA_axes.z = (int16_t)TWDR << 8;

    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    I2C_end();

    return &MMC5883MA_axes;
}


