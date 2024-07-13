# Introducing the Green Bean

![image](/images/GreenBean.png)

The Green Bean is a breakout board based on the STM32G473RCT6 microcontroller.  It's designed to be a small, powerful and adaptable platform for STM32-based development.  It comes with everything you need for basic functionality (power inputs, external crystals, USB connector, an LED to blink and even an SWD interface to upload your code) as well as headers exposing all remaining pins to connect to external components.  Want to take it further, just create a basic shield that connects to those pins and the sky is the limit.

## Features
- 25MHz external high speed crystal, supporting speeds up to 170MHz
- 32.768MHz external low speed crystal
- Five Analog-to-Digital converters
- Four Digital-to-Analog converters
- Powered by either a USB-C connecter, a LiPo battery (with reverse polarity protection) or externally via the VIN pin from 6-32v.  
- ESD protection on USB port
- 4-pin I2C header - perfect for a small OLED display
- 8-pin SPI header - perfect for an NRF24L01 module.  This header includes a 10μF decoupling capacitor between power and ground
- Tag-Connect TC2030 Serial Wire Debugger port
- Power Switch
- Green power LED
- Blue user controllable LED
- Boot0 and Reset buttons.  Hold Boot0 and press Reset once to go into Device Firmware Update (DFU) mode and you can upload new firmware via USB without a SWD programmer.
- Exposed 5v and 3.3v pins.  
- All unused pins exposed via standard 2.54mm female headers.  Connect to external components via jumper wires or make a shield 

## Protocol Support
- USB 2.0 full speed
- Universal Synchronous/Asynchronous Receiver/Transmitter (USART)
- Controller Area Network (CAN)
- I2C:    Mirrored on 4-pin header and Qwiic connector
- SPI:    Available on 8-pin header
- Infrared (IR) Out: 
- Serial Wire Debugger (SWD) via pads for a tag-connect TC2030-IDC-NL adapter.  


## Getting Started

The following links provide everything you need to know to get started using your Green Bean, including powering options, initial configuration and your first sketch.

- [Powering your Green Bean](/Powering%20your%20Green%20Bean.md)
- [Initial Configuration](/initial-config.md)
- [Writing your first program - Hello Blinky!](/writing-your-first-program.md)
- [Uploading firmware](/Uploading%20Firmware.md)

## Examples 

Below are a few simple examples, along with code as needed, to help you get started

- [Writing to a Nextion Display](/examples/Nextion/nextion.md)
- [Analog-to-Digital (ADC) Conversion - Reading a Joystick](/examples/ADC/ADC.md)





  


