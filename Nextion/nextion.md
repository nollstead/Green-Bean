# Nextion


The following instructions are for using the custom nextion libraries to communicate with a Nextion display.  This assumes that you have a Nextion that is configurated with code up and running and connected to USART 

## Enable USART

The nextion display communicates via a serial connection, so the first step is to enable the USART on your Green Bean.  In this example we'll use USART1 since it's available, however, the Nextion display runs at 5v - so we'll need to make sure USART1 is connected to pins that are 5v tolerant.

- Open your .ioc file, navigate to Connectivity->USART1 and change Mode to 'Asynchronous'
- In the pinout view, click on PA9 and select USART1_TX then click on PA10 and select USART1_RX
- Save and close the .ioc file and allow it to generate the required code.

## Importing the nextion libraries

To easily communicate with the Nextion we're included a simple library.  Here we'll import that library into your main code.

- Download the nextion.c and nextion.h files to your computer.  
- Open nextion.c in a text editor and copy the contents to the clipboard
- In your STM32CubeIDE project, navigate to Core\Src in the Project Explorer
- Right-Click and select New->Src
- Name the file nextion.c and replace the contents with the code in your clipboard and save
- Navigate to Core\Inc, Right-Click and select New->Header File
- Name the file nextion.h and replace the contents with the nextion.h code you downloaded.

## Initializing the library

Before writing to the nextion display you'll first need to include the nextion header file and initialize the library

- In the USER CODE BEGIN Includes section of main.c add the following code

```c
/* USER CODE BEGIN Includes */
#include "nextion.h"
```

- In the USER CODE BEGIN 2 section of main.c, call Nextion_Init.  This just tells the library which USART to use.  Since we configured USART1 above we'll use that

```c
  /* USER CODE BEGIN 2 */
  Nextion_Init(&huart1);
```

## Connect Your Nextion Display

Note that since the Nextion communicates via a serial protocol, the instructions below include swapping TX and RX (e.g. Nextion TX connects to Green Bean RX and Nextion RX connects to Green Bean Tx). 

- Connect the 5v pin on your Nextion to the 5v pin on Green Bean
- Connect the GND pin on your Nextion to any GND pin on the Green Bean
- Connect the TX pin on your Nextion to the PA10 pin on the Green Bean
- Connect the RX pin on your Nextion to the PA9 pin on the Green Bean

## Write to the Nextion Display

Now we're setup to write to the Nextion display.  Currently the library consists of two functions, NEXTION_SendString and NEXTION_SendVal to send strings and numbers, respectively.

For example, assuming your Nextion has a text field called Message that you want to write a string to you'd use the following code:

```c
  NEXTION_SendString("Message", "Hellow World!");
```

Likewise, assuming your nextion has a number field called Num you'd use the following code:

```c
    NEXTION_SendVal("Num", 123);
```

