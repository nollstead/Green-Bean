# Introducing the Green Bean

![image](https://github.com/nollstead/Green-Bean/assets/13612518/946539af-7d3a-4dbd-b837-e23c8881a81c)


The Green Bean is a breakout board based on the STM32G473CBT6 microcontroller.  It's designed to be a small, powerful and adaptable platform for STM32-based development.  It comes with everything you need for basic functionality (power inputs, external crystals, USB connector, an LED to blink and even an SWD interface to upload your code) as well as headers exposing all remaining pins to connect to external components.  Want to take it further, just create a basic shield that connects to those pins and the sky is the limit.

## Features
- 16MHz external high speed crystal
- 32.768MHz external low speed crytal
- Powered by either a USB-C connecter or a 1C LiPo battery.  Schottky diodes included to provide reverse voltage protection.
- ESD protection on USB port
- 4-pin I2C header - perfect for a small OLED display
- 8-pin SPI header - perfect for an NRF24L01 module.  This header includes a 4.7μF decoupling capacitor between power and ground
- Tag-Connect NLxxx Serial Wire Debugger connection
- Power Switch
- Green power LED
- Blue user controllable LED
- Boot0 and Reset buttons.  Hold Boot0 and press Reset once to go into Device Firmware Update (DFU) mode and you can upload new firmware via USB without a SWD programmer.
- VIN supports up to 20v
- Exposed 3.3v pins.  Note these are output only (and protected via a Schottky diode)
- All unused pins exposed via standard 2.54mm female headers.  Connect to external components via jumper wires or make a shield 

## Protocol Support
- USB 2.0 full speed
- USART:  Available on pins PA2 (Tx), PA3 (Rx) and Pa4 (Clk)
- I2c:    Available on 4-pin header
- SPI:    Available on 8-pin header
- User LED:  Available on pin PB12
- CAN
- Serial Wire Debugger (SWD) via pads for a tag-connect TC2030-IDC-NL adapter.  



## Getting Started

### Powering the green bean

### Initial Setup (STM32CubeIDE)

### Uploading Code

There are a number of methods to upload code to the green bean.  

- USB DFU Mode:  Details
- Tag-Connect:  Details
- Arduino IDE:  Details



  


