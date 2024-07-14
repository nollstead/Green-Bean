# Initial Configuration

In this section we'll cover initial configurations required for setting up a development project using the Green Bean.  This includes setting up the Integrated Development Environment (IDE) as well as the basic initial configurations required to write your first program.  

## Initial Project Creation

While the Green Bean, like all STMicroelectronics-based microcontrollers, can be programmed a number of differnet ways, we'll focus on setting up a project using the STM32CubeIDE IDE.  If you haven't done so already, download and install STM32CubeIDE from STMicroelectronics at https://www.st.com/en/development-tools/stm32cubeide.html.  


Open STM32CubeIDE and select File->New->STM32 Project.  From there, enter stm32g473rct6 in the commercial part number field, select that MCU from the resulting list on the right and click next.  Give your project a name and click finish.

## Pinout Configuration

Open the .ioc file and make sure you're on the Pinout & Configuration Tab.  

### Configure Crystal Pins
The Green Bean includes two external crystals, a 32.768MHz low speed external crystal and a 25MHz high speed external crystal.  Here we'll tell the system that they exist and we'll define their values later.

- Expand System Core then click on RCC
- Set High Speed Clock (HSE) to Crystal\Ceramic Resonator
- Set Low Speed Clock (LSE) to Crystal\Ceramic Resonator

    ![image](/images/RCC.png)


### Configure Debugger Pins
The Green Bean includes a Tag-Connect header for uploading firmware and debugging using a Serial Wire Debugger (SWD).  Here we configure those pins.  

- Expand System Core then click on SYS
- Set Debug to Trace Asynchronous Sw

    ![image](/images/SYS.png)

    Note:  Technically we can get away with setting the Debug option to 'Serial Wire' but 'Trace Asynchronous Sw' also enables the Serial Wire Output (SWO) pin - which can be useful.  Since it's wired on the board we'll go ahead and choose that option.

### Configure Real Time Clock
While we won't likely be using the real-time clock very often, enabling it here allows us to configure the low speed crystal value later.

- Expand Timers then click on RTC
- Check 'Activate Clock Source'

    ![image](/images/RTC.png)

### (Optional) Configure SPI1 Pins

The Green Bean includes an 8-pin SPI header.  The layout is designed for use with an NRF24L01 transceiver though it can be used for any SPI device.  While this only needs to be configured if you plan to use it, it's convenient to reserve those pins so that we don't use them for something else in case we decide to add an NRF24L01 module later - so we'll go ahead and configure it now.

- Expand Connectivity then click on SPI1
- Set Mode to 'Full-Duplex Master'
- Set Data Size to 8-Bits
- Set Prescaler to 32
- Set NSSP Mode to Disabled
- Click on the NVIC Settings tab and enable SPI global interrupt

    ![image](/images/SPI1.png)

### (Optional) Configure USB

While not strictly required, we'll go ahead and enable USB support as a full speed virtual COM port device.

- Expand Connectivity then click on USB
- Check Device (FS)
- Expand 'Middleware and Software Packs' then click on USB_DEVICE
- set Class For FS IP to 'Communication Device Class (Virtual Port Com)'

    ![image](/images/USBVCP.png)

## Pinout

Now that the main basic components have been configured, you'll see those pins selected on the pinout view on the right.  Before we move on to configuring the clock we'll make a few changes

- Click PB10 and set to GPIO_Output
- Right-Click on PB10, select 'Enter User Label' and rename to LED
- Click on PG10 and set to GPIO_Input
- Right-Click on PG10, select 'Enter User Label' and rename to PG10-NRST
- Click on PB8 and set to GPIO_Input
- Right-Click on PB8, select 'Enter User Label' and rename to PB8-BOOT0
- Click on PA1 and set to GPIO_Output
- Right-Click on PA1, select 'Enter User Label' and rename to CE
- Click on PA2 and set to GPIO_Output
- Right-Click on PA2, select 'Enter User Label' and rename to CSN
- Click on PB9 and set to GPIO_EXTI9
- Right-Click on PB9, select 'Enter User Label' and rename to IRQ


    ![image](/images/pinout.png)


## Clock Configuration

Now that our pins pins are configured, our final step is to configure the clocks. While the STM32G473 MCU has both internal high speed and low speed resonators they're not very inaccurate.  So the Green Bean includes external crystals that can be used instead.  Earlier we enabled this functionality but here we'll configure their values.  

As mentioned above, the Green Bean includes two crystals, one for the low speed clock and 

- On the top menu, click on the Clock Configuration tab.  If you get a clock configuration error you can ignore that and close it for now as we'll setup everything manually.
- Set RTC Clock Mux to LSE
- Set HSE input frequency to 25 (MHz)
- Set PLL Source Mux to HSE
- Set System Clock Mux to PLLCLK
- Set CK48 Clock Mux to HSI48
- Set HCLK to 170MHZ

    ![image](/images/Clock.png)

    Note:  You may notice that we're using the internal resonator to drive the USB instead of the PLLQ.  The reason is that we chose the 25MHz high speed crystal value so that we could achieve the highest possible system speed (170MHz), however, USB needs to run at 48MHz and there is no combination that will start at 25MHz and reach 48MHz.  

Click save and the IDE will take the configuration changes you've set and generate the required code for you.  At this point your Green Bean project is setup with the basics needed to start coding

Next:  [Writing your first program - Blinky!](/writing-your-first-program.md)

