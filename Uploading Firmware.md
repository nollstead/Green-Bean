There are a number of methods to upload code to the green bean.  
- USB DFU Mode:  The simplest, but least powerful, method is to use the built-in Device Firmware Update (DFU) bootloader.  With this method you'll be able to upload compiled code but you won't have debugging capabilities (similar to an Arduino).  1.  Compile your code in your preferred IDE and obtain a firmware file.  2.  Place the green bean in DFU mode by holding the Boot0 button then pressing RESET (then release both).  3.  Identify USB virtual comport in device manager.  4.  Upload code using STM32CubeProgrammer Utility.
   

- Tag-Connect:  Details

