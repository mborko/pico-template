# pico-template
Raspberry Pi RP2040 Template for fast and easy development structure

## Pico SDK

```
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init

## Add pico-sdk Path to your environment
echo export PICO_SDK_PATH=$PWD >> ~/.bashrc
```

## Packages

### Debian based
```
apt update && apt install -y cmake make gcc openssl libssl-dev cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib 
```

### Arch
```
pacman -S arm-none-eabi-gcc arm-none-eabi-binutils arm-none-eabi-newlib cmake autoconf git
yay -S picotool openocd-picoprobe
```

## Programming

1. get SDK
2. cmake example
3. flash it
4. debug it
5. be happy!

## Resources
* https://www.raspberrypi.org/documentation/rp2040/getting-started/
* https://www.raspberrypi.org/documentation/rp2040/getting-started/#board-specifications

### Pico Datasheets
* https://datasheets.raspberrypi.org/
* https://datasheets.raspberrypi.org/pico/raspberry-pi-pico-faq.pdf
* https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf
* https://datasheets.raspberrypi.org/pico/raspberry-pi-pico-c-sdk.pdf

### CMake
* https://cmake.org/cmake/help/latest/guide/tutorial/index.html
* http://derekmolloy.ie/hello-world-introductions-to-cmake/
* https://medium.com/@onur.dundar1/cmake-tutorial-585dd180109b

### FreeRTOS
* "Mastering the FreeRTOS Real Time Kernel - a Hands On Tutorial Guide" [online](https://www.freertos.org/fr-content-src/uploads/2018/07/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf)
* https://www.freertos.org/
* https://github.com/FreeRTOS/FreeRTOS-Kernel
* https://github.com/FreeRTOS/FreeRTOS-SMP-Demos/tree/main/FreeRTOS/Demo/CORTEX_M0%2B_RP2040
* https://lochnerweb.de/freertos-on-raspberry-pi-pico
* https://github.com/PicoCPP/RPI-pico-FreeRTOS
* https://github.com/yunkya2/pico-freertos-sample
* https://github.com/holochn/pi_pico_tasks

