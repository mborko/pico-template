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

