# Raspberry Pi RP2040 Template
Raspberry Pi RP2040 Template for fast and easy development structure

## Pico SDK

```bash
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init

## Add pico-sdk Path to your environment
echo export PICO_SDK_PATH=$PWD >> ~/.bashrc
```

## Packages

### Debian based
```bash
apt update && apt install -y cmake make gcc g++ openssl libssl-dev cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib 
```

### Arch
```bash
pacman -S arm-none-eabi-gcc arm-none-eabi-binutils arm-none-eabi-newlib cmake autoconf git
yay -S picotool openocd-picoprobe
```

## Programming

        1. get SDK
        2. cmake example
        3. flash it
        4. debug it
        5. be happy!

### Programming examples on your Pico
First of all check the `CMakeLists.txt` File, if the desired subdirectories are included (e.g. `add_subdirectory(blink)`) and execute the following commands in this repository:
```bash
rm build -rf
mkdir build && cd build
cmake ..
make
```

Afterwards you can mount your Pico as described in Chapter 3.2.2 of "Getting Started with Raspberry Pi Pico" [1]. _"Removing power from the board does not remove the code. When the board is reattached to power, the code you have just loaded will begin running again. If you want to upload new code to the board (and overwrite whatever was already on there), press and hold the BOOTSEL button when applying power to put the board into Mass Storage mode."_

```bash
$ sudo dmesg | tail
[ 371.973555] sd 0:0:0:0: [sda] Attached SCSI removable disk
$ sudo mkdir -p /mnt/pico
$ sudo mount /dev/sda1 /mnt/pico
$ ls /mnt/pico/
INDEX.HTM INFO_UF2.TXT
$ sudo cp blink/blink.uf2 /mnt/pico
$ sudo sync
```

### FreeRTOS Examples
The FreeRTOS Examples need the Kernel Sources, so don't forget to load the submodule with `git submodule update --init` in this repository. This will load the Kernel into `freertos/FreeRTOS/FreeRTOS-Kernel`.

## Resources
* "The official documentation for Raspberry Pi computers and microcontrollers" [raspberrypi.com](https://www.raspberrypi.com/documentation/microcontrollers/)

### Pico Datasheets
* [1] "Getting Started with Raspberry Pi Pico" [raspberrypi.com](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)
* [2] "Raspberry Pi Datasheets" [raspberrypi.com](https://datasheets.raspberrypi.com/)
* https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf

### CMake
* https://cmake.org/cmake/help/latest/guide/tutorial/index.html
* http://derekmolloy.ie/hello-world-introductions-to-cmake/
* https://medium.com/@onur.dundar1/cmake-tutorial-585dd180109b

### FreeRTOS
* [3] "Mastering the FreeRTOS Real Time Kernel - a Hands On Tutorial Guide" [freertos.org](https://www.freertos.org/fr-content-src/uploads/2018/07/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf)
* https://www.freertos.org/
* https://github.com/FreeRTOS/FreeRTOS-Kernel
* https://github.com/FreeRTOS/FreeRTOS-SMP-Demos/tree/main/FreeRTOS/Demo/CORTEX_M0%2B_RP2040
* https://lochnerweb.de/freertos-on-raspberry-pi-pico
* https://github.com/PicoCPP/RPI-pico-FreeRTOS
* https://github.com/yunkya2/pico-freertos-sample
* https://github.com/holochn/pi_pico_tasks

### CAN
* https://github.com/adamczykpiotr/pico-mcp2515
* https://github.com/a-kipp/RP2040-CAN-Driver

### MQTT with Pico W
* [4] "Connecting to the Internet with Raspberry Pi Pico W" [raspberrypi.com](https://datasheets.raspberrypi.com/picow/connecting-to-the-internet-with-pico-w.pdf)
* https://github.com/cniles/picow-iot
* https://www.nongnu.org/lwip/2_1_x/group__mqtt.html
* https://www.elektronik-kompendium.de/sites/raspberry-pi/2709071.htm

