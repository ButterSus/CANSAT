/**
 * @author ButterSus
 * @date 06.05.2022
 * @name MMC5883MA
 */

#ifndef CANSAT_MMC5883MA_H
#define CANSAT_MMC5883MA_H

#include "axes.h"

void MMC5883MA_init();
axes*MMC5883MA_read();

#endif //CANSAT_MMC5883MA_H
