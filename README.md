# Introducing the Green Bean

![image](https://github.com/nollstead/Green-Bean/assets/13612518/946539af-7d3a-4dbd-b837-e23c8881a81c)

The Green Bean is a breakout board based on the STM32G473CBT6 microcontroller.  It's designed to be a small, powerful and adaptable platform for STM32-based development.  It comes with everything you need for basic functionality (power inputs, external crystals, USB connector, an LED to blink and even an SWD interface to upload your code) as well as headers exposing all remaining pins to connect to external components.  Want to take it further, just create a basic shield that connects to those pins and the sky is the limit.

## Features
- 25MHz external high speed crystal
- 32.768MHz external low speed crystal
- Powered by either a USB-C connecter, a 1C LiPo battery (with reverse polarity protection) or externally via the VIN pin from 6-32v.  
- ESD protection on USB port
- 4-pin I2C header - perfect for a small OLED display
- 8-pin SPI header - perfect for an NRF24L01 module.  This header includes a 10μF decoupling capacitor between power and ground
- Tag-Connect TC2030 Serial Wire Debugger port
- Power Switch
- Green power LED
- Blue user controllable LED
- Boot0 and Reset buttons.  Hold Boot0 and press Reset once to go into Device Firmware Update (DFU) mode and you can upload new firmware via USB without a SWD programmer.
- VIN supports up to 32v
- Exposed 5v and 3.3v pins.  
- All unused pins exposed via standard 2.54mm female headers.  Connect to external components via jumper wires or make a shield 

## Protocol Support
- USB 2.0 full speed
- USART
- I2C:    Mirrored on 4-pin header and Qwiic connector
- SPI:    Available on 8-pin header
- User LED:  Available on pin PB12
- CAN
- Infrared (IR) Out: 
- Serial Wire Debugger (SWD) via pads for a tag-connect TC2030-IDC-NL adapter.  


## Getting Started

The following links provide everything you need to know to get started using your Green Bean, including powering options, initial configuration and your first sketch.

- Powering your Gr33n Bean
- Software and Basic Configuration
- Writing your first program - Blinky!
- Uploading firmware

### Powering the green bean

### Initial Setup (STM32CubeIDE)

### Uploading Code

There are a number of methods to upload code to the green bean.  
- USB DFU Mode:  The simplest, but least powerful, method is to use the built-in Device Firmware Update (DFU) bootloader.  With this method you'll be able to upload compiled code but you won't have debugging capabilities (similar to an Arduino).  1.  Compile your code in your preferred IDE and obtain a firmware file.  2.  Place the green bean in DFU mode by holding the Boot0 button then pressing RESET (then release both).  3.  Identify USB virtual comport in device manager.  4.  Upload code using STM32CubeProgrammer Utility.
   

- Tag-Connect:  Details




  


