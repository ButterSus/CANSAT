enable_language(C ASM)

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
SET(OBJCOPY = avr-objcopy)
SET(OBJDUMP = avr-objdump)

SET(all: $(P).elf lst text)

SET($(P).elf: $(OBJ))
SET($(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $^)
SET(CMAKE_ASM_FLAGS "${CFLAGS} -x assembler-with-cpp")

# INCLUDING DIRECTORIES

include_directories(../CANSAT)
include_directories(Drivers/include)
include_directories(Functions/include)
include_directories(Interface/include)

add_executable(CANSAT Program/main.cpp
        Interface/include/UART.h
        Interface/include/SPI.h
        Interface/include/WIRE1.h
        Interface/include/I2C.h
        Interface/tools.h
        Interface/source/UART.cpp
        Interface/source/I2C.cpp
        Interface/source/SPI.cpp
        Interface/source/WIRE1.cpp

        Drivers/include/ADXL345.h
        Drivers/source/ADXL345.cpp
        Drivers/source/BMP280.cpp
        Drivers/include/BMP280.h
        Drivers/source/DS18B20.cpp
        Drivers/include/DS18B20.h
        Drivers/source/HMC5883MA.cpp
        Drivers/include/HMC5883MA.h
        Drivers/source/L3G4200D.cpp
        Drivers/include/L3G4200D.h

        RTOS/include/tools.h
        RTOS/RTOS.h Program/setup.cpp Program/update.cpp RTOS/source/thread.cpp RTOS/include/thread.h RTOS/source/tools.cpp Drivers/include/TIMER0.h Drivers/source/TIMER0.cpp)

target_link_libraries(CANSAT -lm -lprintf_flt)