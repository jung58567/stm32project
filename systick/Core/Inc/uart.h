/*
 * uart.h
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include <stdio.h>
#include <string.h>

// 프로토타입 선언
void initUart(UART_HandleTypeDef *inHuart);
char getUart();

#endif /* INC_UART_H_ */
