/**
 * @author ButterSus
 * @date 06.05.2022
 * @name ADXL345
 */

#ifndef CANSAT_ADXL345_H
#define CANSAT_ADXL345_H

#include "acceleration.h"

/**
 * @def
 * init ADXL345
 */

void ADXL345_init();

/**
 * @def
 * ADXL345 data read function
 * @return
 * ADXL345 acceleration result
 */

acceleration*ADXL345_read();

#endif //CANSAT_ADXL345_H
