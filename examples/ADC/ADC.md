# Analog-to-Digital (ADC) Conversion

In this example, we'll learn how to configure your green bean to convert an analog input to a digital value.  For the analog source we'll use a small [Dual-Axis XY Joystick with Push Button](https://www.addicore.com/products/dual-axis-xy-joystick-with-push-button?variant=45731914842429), which has two analog outputs (X and Y positions) as well as a digital output representing a button press.

## Configure a timer

Rather than manually performing a single ADC conversion, we'll want our program to do this automatically at a defined interval - so we'll configure a timer that fires an event every 200 milliseconds.

When we setup the green bean we set the main system clock to the maximum 170MHz, which is way too fast for our ADC conversions.  So we'll need to slow the timer clock back by configuring a combination of a clock prescaler and counter period (autoreload register).  The clock rate ($T_{out}$) can be calculated for a given autoreload register (ARR), clock prescaler (PSC) and clock frequency ($F_{clk}$) as follows:

<p align="center">$T_{out}={(ARR+1)(PSC+1) \over F_{clk}}$</p>

 Since Timer2 has a 32-bit autoreload register it can hold a big value, we'll use that and make our calculation a bit easier and set the prescaler to 0.  Substituting 0.2 seconds for $T_{out}, 0 for PSC and 170MHz for $F_{clk}$ we can rearrange the equation and solve for ARR to get 42,500,000

- In STM32CubeIDE open your .ioc file, go to the Timers section and select TIM2
- In the Mode section
  - Set Clock Source to Internal Clock

<p align="center"><img src="/examples/ADC/images/TIM2ClockSource.png"</p>

- In the Configuration section on the Parameter Settings tab
  - Set Prescaler to 0
  - Set Counter Period (AutoReload Register) to 42500000-1 (note we subtract 1 since the counter starts at 0)
  - Set Trigger Event Selection TRGO to Update Event

<p align="center"><img src="/examples/ADC/images/TIM2ParameterSettings.png"</p>


  - Click on the NVIC Settings tab and check TIM2 global interrupt.

<p align="center"><img src="/examples/ADC/images/TIM2NVIC.png"</p>

## Configure ADC

Now that we've configured the timer we'll decide which ports we want to configure for the joystick.  We'll pick two pins on the same analog controller and one digital pin.

- In the right Pinout view pane
  - Click on PC0, select ADC1_IN6 and right-click then rename to JOYX
  - Click on PC1, select ADC1_IN7 and right-click then rename to JOYY
  - Click on PC2, select GPIO_Output and right-click then rename to JOYButton

<p align="center"><img src="/examples/ADC/images/ADCPins.png"</p>

- Under the Analog section click on ADC1
  - In the Mode section change change IN6 and IN7 to Single-ended

<p align="center"><img src="/examples/ADC/images/ADCMode.png"</p>

  - In Configuration/DMA Settings
    - Click Add
    - Set DMA Request to ADC1
    - Set Mode to Circular
    - Set Memory to Byte

  - In Configuration/Parameter Settings
    - Set resolution to ADC 8-bit resolution
    - Set Number of Conversion to 2
    - Set End of Conversion Selection to End of sequence of conversion
    - Set DMA Continuous Requests to Enabled
    - Set External Trigger Conversion Source to Timer 2 Trigger Out Event
    - Expand Rank 1, set channel to Channel 6 and Sampling Time to 247.5 Cycles
    - Expand Rank 2, set channel to Channel 7 and Sampling Time to 247.5 Cycles

 - On the NVIC Settings tab 
   - Enable ADC1 and ADC2 global interrupt


## Code

Now that the timer and ADC are configured, close the .ioc file and let it auto-generate that code.  If you were to run this code it wouldn't do much, as all we've done is setup some initial parameters and variables (that code was auto-generated).  Now we need to add some code 

- Open your main.c file.  If you have any code from a previous example that flashes the LED either remove or comment that out as we'll be using the LED in this example for another purpose.

- In the USER CODE BEGIN PD section declare a constant.  This will be used in a few places to define how many ADC conversions we want to do and set the size for a buffer to hold that data.

```c
/* USER CODE BEGIN PD */
#define ADC_BUF_SIZE 2
```

- In the USER CODE BEGIN PV section declare four private variables.  One is the buffer that the DMA will use to transfer converted analog values and the other three will be where we store those variables for later use.

```c
/* USER CODE BEGIN PV */
uint8_t JoyX, JoyY, JoyButton;
uint8_t AD_RES_BUFFER[ADC_BUF_SIZE];
```

- In the USER CODE BEGIN 2 section we need to add some code to initialize the ADC and start the timer and DMA process.  We'll also set the LED to ON - this is optional but gives us a visual indication that this part of the code ran (and if it's not blinking later we know the ADC isn't working correctly).  We'll also insert a small 100ms delay after calibrating the ADC just to give it time to complete the calibration.  
```c
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);  			// Initialize to on
  HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);				// Initial ADC Calibration
  HAL_Delay(100);														// Delay a bit to be sure it finishes
  HAL_TIM_Base_Start(&htim2);											// Start timer
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *) AD_RES_BUFFER, ADC_BUF_SIZE);  // Enable DMA to memory buffer
```

- Now we'll write a callback function for the ADC and place it in the USER CODE BEGIN 0 section.  This function will be called automatically when the ADC completes it's work.  Remember that above we set the end of conversion selection to end of sequence of conversion.  That means that once both ADC conversions are complete it'll call this function, rather than after each conversion.  Here we're just toggling the LED pin - just to give us a visual indication that it's working - and pull the variables from the buffer to individual variables to be used later.

```c
/* USER CODE BEGIN 0 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	JoyX = AD_RES_BUFFER[0];
	JoyY = AD_RES_BUFFER[1];
	JoyButton = HAL_GPIO_ReadPin(JOYButton_GPIO_Port, JOYButton_Pin);	
}
```

## Connect joystick and Test

Now we're ready to test.  Wire in the joystick as follows (note that while the joystick we're using lists the power pin as +5V, our green bean natively runs at 3.3v - so we'll use that)

| Joystick pin | Green Bean header pin |
| :---: | ----------------------|
| SW           | PC2                   |
| VRX          | PC0                   |
| VRY          | PC1                   |
| +5V          | 3V3                   |
| GND          | GND                   |

## Write values

