/*
 * nextion.c
 *
 *  Created on: May 11, 2024
 *      Author: nolls
 */

#include "nextion.h"

static UART_HandleTypeDef* Nextion_UART;
static uint8_t Nextion_Cmd_End[3] = {0xFF, 0xFF, 0xFF};  // commend end sequence


void Nextion_Init(UART_HandleTypeDef *UARTHandle) {
	Nextion_UART = UARTHandle;
}

void NEXTION_SendString(char *ID, char *string) {
	char buf[50];
	int len = sprintf(buf, "%s.txt=\"%s\"", ID, string);
	HAL_UART_Transmit(Nextion_UART, (uint8_t *)buf, len, 1000);
	HAL_UART_Transmit(Nextion_UART, Nextion_Cmd_End, 3, 100);

}

void NEXTION_SendVal(char *ID, uint8_t val) {
	char buf[50];
	int len = sprintf(buf, "%s.val=%d", ID, val);
	HAL_UART_Transmit(Nextion_UART, (uint8_t *)buf, len, 1000);
	HAL_UART_Transmit(Nextion_UART, Nextion_Cmd_End, 3, 100);
}
