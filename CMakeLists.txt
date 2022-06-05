cmake_minimum_required(VERSION 3.22)
project(CANSAT)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_BUILD_TYPE Debug-AVR)
SET(MCU "atmega128")
SET(F_CPU "8000000")
SET(CMAKE_CXX_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os")
SET(CMAKE_CXX_LINK_FLAGS "-mmcu=${MCU}")
SET(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os")
SET(CMAKE_C_LINK_FLAGS "-mmcu=${MCU}")
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(override CFLAGS = -g -DF_CPU=$(HZ) -Wall -O2 -mmcu=$(MCU_TARGET) $(DEFS))
SET(override LDFLAGS= -Map,$(P).map)
SET(CMAKE_EXE_LINKER_FLAGS -Wl,-u,vfprintf)
SET(OBJCOPY     = avr-objcopy)
SET(OBJDUMP     = avr-objdump)

SET(all: $(P).elf lst text)

SET($(P).elf: $(OBJ))
SET($(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $^)

include_directories(Drivers)
include_directories(Functions)

add_executable(CANSAT main.cpp Drivers/UART.h Drivers/UART/UART.cpp Drivers/UART/UART.h Functions/functions.h Functions/setup.cpp Functions/update.cpp Drivers/SPI.h Drivers/SPI/SPI.h Drivers/ADXL345.h Drivers/ADXL345/settings.h Drivers/ADXL345/ADXL345.cpp Drivers/ADXL345/ADXL345.h Drivers/ADXL345/acceleration.h Drivers/NRF24L01.h Drivers/NRF24L01/settings.h Drivers/NRF24L01/NRF24L01.cpp Drivers/NRF24L01/NRF24L01.h Drivers/BMP280.h Drivers/BMP280/BMP280.cpp Drivers/BMP280/BMP280.h Drivers/BMP280/settings.h Drivers/BMP280/atmosphere.h Drivers/WIRE1.h Drivers/WIRE1/WIRE1.h Drivers/DS18B20/DS18B20.cpp Drivers/DS18B20/DS18B20.h Drivers/DS18B20/settings.h Drivers/PORTS.cpp Drivers/PORTS.h Drivers/DS18B20.h Drivers/I2C/I2C.cpp Drivers/I2C/I2C.h Drivers/I2C/settings.h Drivers/MMC5883MA/MMC5883MA.cpp Drivers/MMC5883MA/MMC5883MA.h Drivers/MMC5883MA/settings.h Drivers/MMC5883MA/face.h Drivers/I2C.h Drivers/MMC5883MA.h Drivers/L3G4200D/L3G4200D.cpp Drivers/L3G4200D/L3G4200D.h Drivers/L3G4200D/settings.h Drivers/L3G4200D/axes.h Drivers/L3G4200D.h RTOS/thread.cpp RTOS/thread.h Drivers/NSystem.cpp Drivers/NSystem.h Drivers/OLD_NRF24L01/NRF24L01.cpp Drivers/OLD_NRF24L01/NRF24L01.h Drivers/OLD_NRF24L01/settings.h)

target_link_libraries(CANSAT -lm -lprintf_flt)