/*
 * nextion.h
 *
 *  Created on: May 11, 2024
 *      Author: nolls
 */

#ifndef INC_NEXTION_H_
#define INC_NEXTION_H_

#include "stm32g4xx_hal.h"
#include "stdio.h"


#ifdef __cplusplus
extern "C" {
#endif


void Nextion_Init(UART_HandleTypeDef *UARTHandle);
void NEXTION_SendString(char *ID, char *string);
void NEXTION_SendVal(char *ID, uint8_t val);




#ifdef __cplusplus
}
#endif


#endif /* INC_NEXTION_H_ */
