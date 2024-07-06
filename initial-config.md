In this section we'll cover initial configurations required for setting up a development project using the Green Bean.  This includes setting up the Integrated Development Environment (IDE) as well as the basic initial configurations required to write your first program.  

## Initial Project Creation

While the Green Bean, like all STMicroelectronics-based microcontrollers, can be programmed a number of differnet ways, we'll focus on setting up a project using the STM32CubeIDE IDE.  If you haven't done so already, download and install STM32CubeIDE from STMicroelectronics at https://www.st.com/en/development-tools/stm32cubeide.html.  


Open STM32CubeIDE and select File->New->STM32 Project.  From there, enter stm32g473rct6 in the commercial part number field, select that MCU from the resulting list on the right and click next.  Give your project a name and click finish.

## Pinout Configuration

Open the .ioc file and make sure you're on the Pinout & Configuration Tab.  

### Expand System Core then click on RCC
The Green Bean includes two external crystals, a 32.768MHz low speed external crystal and a 25MHz high speed external crystal.  Here we'll tell the system that they exist and we'll define their values later.

- Set High Speed Clock (HSE) to Crystal\Ceramic Resonator
- Set Low Speed Clock (LSE) to Crystal\Ceramic Resonator

![image](/images/RCC.png)


### Expand System Core then click on SYS
The Green Bean includes a Tag-Connect header for uploading firmware and debugging using a Serial Wire Debugger (SWD).  Here we configure those pins.  
- Set Debug to Trace Asynchronous Sw

![image](/images/SYS.png)

Note:  Technically we can get away with setting the Debug to 'Serial Wire' but 'Trace Asynchronous Sw' also enables the Serial Wire Output (SWO) pin - which can be useful.

### Expand Timers then click on RTC
While we won't necessarily be using the real-time clock very often, enabling it here allows us to configure the low speed crystal value later.
- Check 'Activate Clock Source'

![image](/images/RTC.png)

### (Optional) Expand Connectivity then click on SPI1

The Green Bean includes an 8-pin SPI header.  The layout is designed for use with an NRF24L01 transceiver though it can be used for any SPI device.  While this only needs to be configured if you plan to use it, it's convenient to reserve those pins so we have options later - so we'll go ahead and configure it now.

- Set Mode to 'Full-Duplex Master'
- Set Data Size to 8-Bits
- Set Prescaler to 32
- Set NSSP Mode to Disabled
- Click on the NVIC Settings tab and enable SPI global interrupt

![image](/images/SPI1.png)



## Clock Configuration

![image](/images/Clock.png)

## Pinout

![image](/images/pinout.png)

