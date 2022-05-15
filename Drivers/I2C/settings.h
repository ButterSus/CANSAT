/**
 * @author ButterSus
 * @date 11.05.2022
 * @name settings for I2C
 */

#ifndef CANSAT_I2C_SETTINGS_H
#define CANSAT_I2C_SETTINGS_H

/*! CONFIG */

#define WRITE_MODE(x) (x &~ 1)
#define READ_MODE(x) (x | 1)

#endif //CANSAT_I2C_SETTINGS_H
