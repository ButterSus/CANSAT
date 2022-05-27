# CANSAT

`February 2022` - `July 2022`

first AVR project. (feat. ThePetrovich & bear1ake)

### Features

- [Project structure](#Project structure)
- [`.cpp` structure](`.cpp` structure)

### Project structure

- `main.c` calls setup then update in loop.
- `RTOS` files for better memory allocation and so more.
  - `multithread` multithread support.
- `Functions` files: setup, update.
  - `functions.h` include setup and update.
  - `setup.cpp` setup.
  - `update.cpp` update.
- `Drivers (sensors)` files for sensors' drivers.
  - `ADXL345` & `ADXL345.h` ADXL345 support.
  - `BMP280` & `BMP280.h` ADXL345 support.
  - `DS18B20` & `DS18B20.h` DS18B20 support.
  - `L3G4200D` & `L3G4200D.h` L3G4200D support.
  - `MMC5883MA` & `MMC5883MA.h` MMC5883MA support.
- `Drivers (protocols)` files for protocols' drivers.
  - `I2C` & `I2C.h` I2C support.
  - `SPI` & `SPI.h` SPI support.
  - `UART` & `UART.h` UART support.
  - `WIRE1` & `WIRE1.h` 1-WIRE support.
- `Drivers (other)` files for another tasks.
  - `PORTS.cpp` & `PORTS.h` library for linking `avr/io.h` ports.

### `.cpp` structure

- commentaries:
  - ```c++
    - author
        "ButterSus"
    - date
        "May 2022"
    - name
        "ADXL345"
    ```

- including libraries:
  - ```c++
    - including standard libraries (in alphabetical order)
        #include <stdio.h>
    - including drivers (in alphabetical order)
        #include "SPI.h"
    - including another files (in alphabetical order)
        #include "settings.h"
    ```

- global variables and constants:
  - ```c++
    jmp_buf MMC5883MA_jmpbuf;
    ```

- defines and macros (in settings.h if count of that more than two):
  - ```c++
    ISR(USART0_RX_vect){
        printf("%c",UDR0);
    }
    ```
- and other things..:
  - ```c++
    int main(){
        setup();
        while(run){
            update();
        }
    }
    ```

[Project structure](#-Project-structure)