# Analog-to-Digital (ADC) Conversion

In this example, we'll learn how to configure your green bean to convert an analog input to a digital value.  For the analog source we'll use a small [Dual-Axis XY Joystick with Push Button](https://www.addicore.com/products/dual-axis-xy-joystick-with-push-button?variant=45731914842429), which has two analog outputs (X and Y positions) as well as a digital output representing a button press.

## Configure a timer

Rather than manually performing a single ADC conversion, we'll want our program to do this automatically at a defined interval - so we'll configure a timer that fires an event every 200 milliseconds.

When we [setup the green bean](/initial-config.md) we set the main system clock to the maximum 170MHz, which is way too fast for our ADC conversions.  So, we'll need to slow the timer clock back by configuring a combination of a clock prescaler and counter period (autoreload register).  The clock rate ($T_{out}$) can be calculated for a given autoreload register (ARR), clock prescaler (PSC) and clock frequency ($F_{clk}$) as follows:

<p align="center">$T_{out}={(ARR+1)(PSC+1) \over F_{clk}}$</p>

 Since Timer2 has a 32-bit autoreload register it can hold a big value, we'll use that and make our calculation a bit easier and set the prescaler to 0.  Substituting 0.2 seconds for $T_{out}, 0 for PSC and 170MHz for $F_{clk}$ we can rearrange the equation and solve for ARR to get 42,500,000

- In STM32CubeIDE open your .ioc file, go to the Timers category and select TIM2
- In the Mode section set Clock Source to Internal Clock

    ![image](/examples/ADC/images/TIM2ClockSource.png)

- In the Configuration section on the Parameter Settings tab
  - Set Prescaler to 0
  - Set Counter Period (AutoReload Register) to 42500000-1 (note we subtract 1 since the counter starts at 0)
  - Set Trigger Event Selection TRGO to Update Event

    ![image](/examples/ADC/images/TIM2ParameterSettings.png)

  - Click on the NVIC Settings tab and check TIM2 global interrupt.

    ![image](/examples/ADC/images/TIM2NVIC.png)

## Configure ADC

Now that we've configured the timer we need to configure the ADC controller. We'll start by deciding which pins we want to use.  The Green Bean has five ADC's, each of which is divided into a number of channels.  Each pin has different options as to which ADC and channel it can work on.  For convenience, we'll pick two pins on the same analog controller.

#### 1. Enable pins

- In the right Pinout view pane
  - Click on PC0, select ADC1_IN6 and right-click then rename to JOYX
  - Click on PC1, select ADC1_IN7 and right-click then rename to JOYY
  - Click on PC2, select GPIO_Input and right-click then rename to JOYButton

   Note that these are case sensitive, be sure to use the same capitalization as above to match the code sections below.

    ![image](/examples/ADC/images/ADCPins.png)

Since the joystick we're using connects the button to GND when pressed, which is typical of most, we'll need to enable an internal pull-up resistor on the PC2 pin.  If you coming from an Arduino background this is similar to calling something like **pinMode(JOYButton, INPUT_PULLUP)**.  We could code this manually in main.c but since we're here anyway we'll let the code generator do it for us.

- Expand the System Core category and click on GPIO
- Click on PC2 and set set GPIO Pull-up/Pull-down to Pull-up

    ![image](/examples/ADC/images/pullup.png)

Each channel can be configured as either Single-Ended (where each conversion is done individually) or Differential (used to compare two different pins).  Since we are interested in obtaining individual values for the X and Y joystick, rather than compare those two values to each other, we'll set each channel to Single-Ended.

- Under the Analog category click on ADC1
- In the Mode section change change IN6 and IN7 to Single-ended

    ![image](/examples/ADC/images/ADCMode.png)

#### 2. Configure DMA

There are several options for performing ADC conversions.  In our example, we'll configure it to automatically convert the results and store in a variable using Direct Memory Access (DMA).  DMA is a function of the microcontroller that works in the background to transfer data between a peripheral device (like our joystick) to a memory buffer.  


  - In the Configuration section click on the DMA Settings tab
  - Click Add
  - Set DMA Request to ADC1
  - Set Mode to Circular
  - Set Memory to Byte

    ![image](/examples/ADC/images/DMA.png)

#### 3. Configure ADC Parameters

Now we'll tell the ADC where to obtain the analog data, in which order we want to sample (rank), how to convert it and how often we want to sample the data.  Since we're reading joystick values, which inherently range from 0 to 255, we'll tell it to do an 8-bit conversion.  This saves us from having to map the results into that range via code (as is typically done with an Arduino using the map() function).  We'll also tell it to let us know, by firing an event (we'll see that later), when both conversions are complete.  We also set the sampling time arbitrarily to something in the middle of the range:  Lower values are quicker but less accurate, higher values take more time - although in this case the sampling time doesn't make much difference.

Note the order that these settings are made is important - as some options are not available until others are set

  - click on the parameter settings tab
  - Set resolution to ADC 8-bit resolution
  - Set Number of Conversion to 2
  - Set End of Conversion Selection to End of sequence of conversion
  - Set DMA Continuous Requests to Enabled
  - Set External Trigger Conversion Source to Timer 2 Trigger Out Event
  - Expand Rank 1, set channel to Channel 6 and Sampling Time to 247.5 Cycles
  - Expand Rank 2, set channel to Channel 7 and Sampling Time to 247.5 Cycles

    ![image](/examples/ADC/images/ParameterSettings.png)

Finally we'll wire up the shared ADC1/ADC2 global interrupt

 - Click on the NVIC settings tab and enable ADC1 and ADC2 global interrupt

    ![image](/examples/ADC/images/interrupt.png)

## Code

Now that the timer and ADC are configured, close the .ioc file and let it auto-generate that code.  If you were to run this code now it wouldn't do much, as all we've done is setup some initial parameters and variables and had that code auto-generated.  Now we need to add some code to use these. 

We'll create a buffer of size 2 (for x and y) to store the data (that's the DMA function at work) as well as additional variables to hold the individual values.  

- Open your main.c file.  If you have any code from a previous example that flashes the LED either remove or comment that out as we'll be using the LED in this example for another purpose.

- In the **USER CODE BEGIN PD** section declare a constant.  This will be used in a few places to define how many ADC conversions we want to do and set the size for a buffer to hold that data - so it's handy to declare it in one place in case you want to change it later.

```c
/* USER CODE BEGIN PD */
#define ADC_BUF_SIZE 2
```

- In the **USER CODE BEGIN PV** section declare four private variables.  One is the buffer that the DMA will use to transfer converted analog values and the other three will be where we store those variables for later use. 

```c
/* USER CODE BEGIN PV */
uint8_t JoyX, JoyY, JoyButton;
uint8_t AD_RES_BUFFER[ADC_BUF_SIZE];
```

- In the **USER CODE BEGIN 2** section we need to add some code to initialize the ADC and start the timer and DMA process.  We'll also set the LED to ON - this is optional but gives us a visual indication that this part of the code ran (and if it's not blinking later we know the ADC isn't working correctly).  We'll also insert a small 100ms delay after calibrating the ADC just to give it time to complete the calibration.  
```c
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);  			// Initialize to on
  HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);				// Initial ADC Calibration
  HAL_Delay(100);														// Delay a bit to be sure it finishes
  HAL_TIM_Base_Start(&htim2);											// Start timer
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *) AD_RES_BUFFER, ADC_BUF_SIZE);  // Enable DMA to memory buffer
```

- Now we'll write a callback function for the ADC and place it in the **USER CODE BEGIN 0** section.  This function will be called automatically when the ADC completes it's work.  Remember that above we set the end of conversion selection to end of sequence of conversion.  That means that once both ADC conversions are complete it'll call this function, rather than after each conversion.  Here we're just toggling the LED pin - just to give us a visual indication that it's working - and pull the variables from the buffer to individual variables to be used later.

```c
/* USER CODE BEGIN 0 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	JoyX = AD_RES_BUFFER[0];
	JoyY = AD_RES_BUFFER[1];
	JoyButton = !HAL_GPIO_ReadPin(JOYButton_GPIO_Port, JOYButton_Pin);  // Invert pin on read due to pull-up
}
```

Note:  You'll notice that in the ConvCpltCallback function we're just storing values from the AD_RES_BUFFER into separate variables but not doing anything with them.  This is typical as you want the ADC conversion to run quickly (and repeatedly) - so don't include any logic in this function.  Its only purpose is to store the data in variables, so that we can use them later, and move on.  It does this every 200ms (per the timer we configured) so we don't want anything that takes a long time to run.  Also note that we're reading the JoyButton value here as well.  While that's not an analog conversion this seems like a reasonable place to update that variable so that we know that everything was read at the same time and we don't need to configure a separate timer to read that value.

Finally we'll add some code to the main while loop to write the values to the USB.  If you already have code from a previous example that writes to the USB either delete or comment that out first, then add the following code to the **USER CODE BEGIN 3** section

```c
    /* USER CODE BEGIN 3 */
	  bufLen = snprintf(txBuf, 128, "JoyX:  %d\tJoyY: %d\tJoyButton: %d\r\n", JoyX, JoyY, JoyButton);
	  CDC_Transmit_FS((uint8_t *) txBuf, bufLen);
	  HAL_Delay(500);
```

## Connect joystick

Now we can connect our joystick according to the pins we configured above.  Wire in the joystick as follows (note that while the joystick we're using lists the power pin as +5V, our green bean natively runs at 3.3v - so we'll use that)

| Joystick pin | Green Bean header pin |
| :---: | :---:|
| SW           | PC2                   |
| VRX          | PC0                   |
| VRY          | PC1                   |
| +5V          | 3V3                   |
| GND          | GND                   |

## Test

If you upload and run your code now you should see the blue light flashing about every 2.5 times a second.  If the blue light is on then you likely have a configuration issue with the ADC, so review the steps above to be sure you haven't missed anything in that section.

Now it's time to check the conversion and read the values.  We'll do this two ways: via the USB and 

#### Via USB

As before, once your code is uploaded and running you can connect to the Green Bean using a terminal emulator such as PuTTY.  You should see the joystick values printed every 1/2 second. 

    ![image](/examples/ADC/images/USBOutput.png)

#### Via the debugger

While inspecting variables via the USB is fine, and likely very familiar to anyone coming from an Aruidno background using Serial.println, we're in the STM32 world now and there are better ways.  Let's see how we can inspect variables using the debugger

- Upload and run your code using Run->Debug (instead of Run->Run)
- When the debugger stops on the first line (typically HAL_Init()) press F8 to allow it to resume.  You should see the blue light flashing, indicating that the code is running and the ADC is working.
- In the debug window look for a tab called Live Expressions.  Note that you may need to enable this in the IDE options if it's not there
- Click on Add new expression and add in the JoyX, JoyY and JoyButton variables
- As you move the joystick and press the button you should see the values change in that window

    ![image](/examples/ADC/images/liveexpressions.png)
