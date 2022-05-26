/**
 * @author ButterSus
 * @date May 2022
 * @name MMC5883
 */

#ifndef CANSAT_MMC5883MA_H
#define CANSAT_MMC5883MA_H

#include "face.h"

void MMC5883_init();
void MMC5883_measure();
face*MMC5883_read();

#endif //CANSAT_MMC5883MA_H
