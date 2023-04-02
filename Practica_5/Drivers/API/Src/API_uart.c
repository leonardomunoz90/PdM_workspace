/*
 * API_uart.c
 *
 *  Created on: Apr 1, 2023
 *      Author: leonardo
 */

#include <stdio.h>
#include "API_uart.h"

/* UART handler declaration */
//Se le coloca static para encapsulamiento
static UART_HandleTypeDef UartHandle;


//Configutaciones de UART del ejemplo 2
bool_t uartInit() {
	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART configured as follows:
	 - Word Length = 8 Bits (7 data bit + 1 parity bit) :
	 BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	 - Stop Bit    = One Stop bit
	 - Parity      = ODD parity
	 - BaudRate    = 9600 baud
	 - Hardware flow control disabled (RTS and CTS signals) */
	UartHandle.Instance = USARTx;

	UartHandle.Init.BaudRate = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&UartHandle) != HAL_OK) {
		/* Initialization Error */
		return false;
	}
	printf(
			"\n\r UART configured as follows:"
					"\n\r Word Length = 8 Bits (7 data bit + 1 parity bit) :"
					"BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal"
					"\n\r Stop Bit    = One Stop bit"
					"\n\r Parity      = no parity"
					"\n\r BaudRate    = 9600 baud"
					"\n\r Hardware flow control disabled (RTS and CTS signals)\n\r");
	return true;
}

//Recorre el array y envía el contenido uno a uno hasta encontrar una \0
void uartSendString(uint8_t *pstring) {
	do {
		HAL_UART_Transmit(&UartHandle, pstring, 1, 0xFFFF);
		pstring++;
	} while (*pstring != '\0');
}

void uartSendStringSize(uint8_t *pstring, uint16_t size) {
	HAL_UART_Transmit(&UartHandle, pstring, size, 0xFFFF);
}

void uartReceiveStringSize(uint8_t *pstring, uint16_t size) {
	HAL_UART_Receive(&UartHandle, pstring, size, 0xFFFF);
}

PUTCHAR_PROTOTYPE {
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART3 and Loop until the end of transmission */
	HAL_UART_Transmit(&UartHandle, (uint8_t*) &ch, 1, 0xFFFF);

	return ch;
}
