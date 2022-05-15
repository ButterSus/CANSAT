/**
 * @author ButterSus
 * @date 06.05.2022
 * @name update
 */

#include <util/delay.h>
#include <stdio.h>
#include "MMC5883MA.h"
#include "I2C.h"

void update(){
    axes*result = MMC5883MA_read();
    printf("%i %i %i\r\n", result->x, result->y, result->z);
    _delay_ms(200);
}
