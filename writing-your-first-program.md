# Writing your First Program - "Hello Blinky"

Now that your Green Bean is configured it's time to write your first program.  We'll write a simple "Hello Blinky" that flashes the LED and writes "Hello World" to the USB.

## Add includes to reference required libraries

Add the standard IO and USB CDC IF header references to the **USER CODE BEGIN Includes** section at the top of main.c.  Your code should look like this:

```c
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "usbd_cdc_if.h"

/* USER CODE END Includes */
```

## Declare private variables to hold data to be transmitted and length of the string

Add the following code to the **USER CODE BEGIN PV** section

```c
/* USER CODE BEGIN PV */
char txBuf[128];
uint8_t bufLen;

/* USER CODE END PV */
```

## Add main logic code to flash the LED and write to the USB port every 500ms (1/2 second).

Add the following code to the **USER CODE BEGIN 3** section
```c
  /* USER CODE BEGIN 3 */
  bufLen = snprintf(txBuf, 128,"Hello World\r\n");
  CDC_Transmit_FS((uint8_t *) txBuf, bufLen);
  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  HAL_Delay(500);
```

Now compile and upload your code.  You should see the blue LED flashing every second.  If you connect to the serial port with a terminal emulator (such as Putty) you should see "Hello World" printed every 1/2 second.

Next:  [Uploading Firmware](/Uploading%20Firmware.md)






