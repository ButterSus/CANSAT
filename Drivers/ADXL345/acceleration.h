/**
 * @author ButterSus
 * @date 06.05.2022
 * @name acceleration
 */

#ifndef CANSAT_ACCELERATION_H
#define CANSAT_ACCELERATION_H

/**
 * @def
 * ADXL345 acceleration struct
 */

typedef struct{
    unsigned int X,Y,Z;
}acceleration;

#endif //CANSAT_ACCELERATION_H
