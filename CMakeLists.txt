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
SET(override LDFLAGS= -Wl,-u,vfprintf,-Map,$(P).map)
SET(OBJCOPY     = avr-objcopy)
SET(OBJDUMP     = avr-objdump)

SET(all: $(P).elf lst text)

SET($(P).elf: $(OBJ))
SET($(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $^)

include_directories(Drivers)
include_directories(Functions)

add_executable(CANSAT main.cpp Drivers/UART.h Drivers/UART/UART.cpp Drivers/UART/UART.h Functions/functions.h Functions/setup.cpp Functions/update.cpp Drivers/SPI.h Drivers/SPI/send.h Drivers/ADXL345.h Drivers/ADXL345/settings.h Drivers/ADXL345/ADXL345.cpp Drivers/ADXL345/ADXL345.h Drivers/ADXL345/acceleration.h Drivers/NRF24L01.h Drivers/NRF24L01/settings.h Drivers/NRF24L01/NRF24L01.cpp Drivers/NRF24L01/NRF24L01.h Drivers/BMP280.h Drivers/BMP280/BMP280.cpp Drivers/BMP280/BMP280.h Drivers/BMP280/settings.h Drivers/BMP280/atmosphere.h)

target_link_libraries(CANSAT -lm -lprintf_flt)