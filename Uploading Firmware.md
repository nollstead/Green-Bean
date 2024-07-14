# Uploading Firmware

Once you've finished your code it's time to upload it to the green bean.  If you're coming from the Arduino world you probably never thought much about this - you just plug in the USB cable and click upload from the Arduino IDE.  Arduino is a great platform for beginners, however the designers had to make sacrifices in order to make the platform easy to use.  

In the STM32-world those sacrifices do not exist.  While it gives you greater control over the underlying hardware, this comes at the cost of a bit more complexity - including in how to upload firmware.

Fortunately, the Green Bean has two methods to upload firmware, both with their own advantages and disadvantages.  It supports a simple Device Firmware Update mode (DFU) as well as a more advanced Serial Wire Debug (SWD) mode.

## DFU Mode

The simplest, but least powerful, method is to use the built-in Device Firmware Update (DFU) bootloader.  With this method you'll be able to upload compiled code but you won't have debugging capabilities (similar to an Arduino).  

The steps to upload your code using DFU are as follows:

1.  Compile your code in your preferred IDE and obtain a firmware file.  In our examples we'll strictly use the [STM32CubeIDE Integrated Development Environment](https://www.st.com/en/development-tools/stm32cubeide.html), which generates a binary file ending in .elf.  
2.  Place the green bean in DFU mode by holding the Boot0 button then pressing RESET (then release both).  
3.  Identify USB virtual comport in device manager.  
4.  Upload code using the [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) utility.


## Serial Wire Debug (SWD)   

A more powerful, albeit more expensive, method is to upload your code via the IDE using Serial Wire Debug (SWD).  The Green Bean comes configured with a SWD port, allowing an external debugger to be easily attached and detached as needed.  Using SWD has the additional benefit of not only allowing you to upload your code but debug as well - all within the STM32CubeIDE

#### Equipment

In order to use SWD you'll need some gear.  Specifically, a debugger and some cables.  Instead of the standard SWD connection that comes with the ST Debugger, the Green Bean uses a tag-connect cable.  This allows for a very small footprint on the board that doesn't get in the way when not used.  

- [STLink-V3SET Debugger](https://www.digikey.com/en/products/detail/stmicroelectronics/STLINK-V3SET/9636028).  This is the latest version of the debugger from STMicroelectronics.  There are other options out there - including a V2 version from STM - though this is the one I recommend and use in my examples
- [ARM20-CTX 20-Pin to TC2030-IDC Adapter](https://www.tag-connect.com/product/arm20-ctx-20-pin-to-tc2030-idc-adapter-for-cortex).  This adapter connects to the V3SET debugger and allow use of the Tag-Connect cables.
- [Tag-Connect TC2030-IDC-NL](https://www.tag-connect.com/product/tc2030-idc-nl).  This is the "no-leg" version of the cable that connects to the Green Bean.  
- [TC2030 Retainer (3 pack)](https://www.tag-connect.com/product/tc2030-retaining-clip-board-3-pack).  Since the Green Bean uses the "no-leg" version of the Tag-Connect cable to conserve space, this retainer help to keep it in place.


