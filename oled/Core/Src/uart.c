/*
 * uart.c
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */

#include "uart.h"

UART_HandleTypeDef *myHuart;

#define rxBufferMax 100
uint8_t rxCharacter;
uint8_t rxBuffer[rxBufferMax];  //circle buffer = ring buffer
int rxBufferReadIndex; //읽기 위치
int rxBufferWriteIndex;


int _write(int file, char *p, int len){
	HAL_UART_Transmit(myHuart, (uint8_t *)p, len, 10);
	return len;
}

// 수신 인터럽트(interrupt = event) 콜백(listner, isr)
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	//수신된 문자 저장
	rxBuffer[rxBufferWriteIndex++] = rxCharacter;
	//최대값 도달시 처음으로
	rxBufferWriteIndex %=rxBufferMax;
	//인터럽트 재 장전
	HAL_UART_Receive_IT(myHuart, &rxCharacter, 1);
}

//uart 장치 초기화
void initUart(UART_HandleTypeDef *inHuart){
	//uart 장치 주소 백업
	myHuart = inHuart;
	//인터럽트 장전
	HAL_UART_Receive_IT(myHuart, &rxCharacter, 1);
}

char getUart(){
	char result;
	if(rxBufferReadIndex == rxBufferWriteIndex) return 0;
	result = rxBuffer[rxBufferReadIndex++];
	rxBufferReadIndex %= rxBufferMax;
	return result;
}

char*getMessage(){
	static char message[50];
	static uint8_t messageCount = 0;
	char ch=getUart();
	if(ch!=0){
		if(ch=='\n'||ch=='\r'){
			messageCount=0;
			memset(message,0,50);
		}
		else if(ch>=0x20){
			message[messageCount++] = ch;
		}
	}
	return message;
}
