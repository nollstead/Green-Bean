# Analog-to-Digital (ADC) Conversion

In this example, we'll learn how to configure your green bean to convert an analog input to a digital value.  For the analog source we'll use a small joystick which has two analog outputs (X and Y positions) as well as a digital output representing a button press.  Examples of inexpensive joysticks can be found here and here.

## Configure a timer

Rather than manually performing a single ADC conversion, we'll want our program to do this automatically at a defined interval - so we'll configure a timer that fires an event every 200 milliseconds.

When we setup the green bean we set the main system clock to the maximum 170MHz, which is way too fast for our ADC conversions.  So we'll need to slow the timer clock back by configuring a combination of a clock prescaler and counter period (autoreload register).  The clock rate ($T_{out}$) can be calculated for a given autoreload register (ARR), clock prescaler (PSC) and clock frequency ($F_{clk}$) as follows:

 $T_{out}={(ARR+1)(PSC+1) \over F_{clk}}$

 Since Timer2 has a 32-bit autoreload register it can hold a big value, we'll use that and make our calculation a bit easier and set the prescaler to 0.  Substituting 0.2 seconds for $T_{out}, 0 for PSC and 170MHz for $F_{clk}$ we can rearrange the equation and solve for ARR to get 42,500,000

- In STM32CubeIDE open your .ioc file, go to the Timers section and select TIM2
- In the Mode section
  - Set Clock Source to Internal Clock
- In the Configuration section
  - Set Prescaler to 0
  - Set Counter Period (Auto Reload Register) to 42500000-1 (note we subtract 1 since the counter starts at 0)
  - Set Trigger Event Selection TRGO to Update Event
  - Click on NVIC Settings and check TIM2 global interrupt.

## Configure ADC


## Connect Joystick

## Write values

