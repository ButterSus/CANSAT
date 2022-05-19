/**
 * @author ButterSus
 * @date May 2022
 * @name atmosphere
 */

#ifndef CANSAT_ATMOSPHERE_H
#define CANSAT_ATMOSPHERE_H

/**
 * @def
 * BMP280 atmosphere struct
 */

typedef struct{
    float TEMP, PRESS;
}atmosphere;

#endif //CANSAT_ATMOSPHERE_H
