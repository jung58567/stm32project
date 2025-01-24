/*
 * app.c
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */

#include "app.h"
#include <stdlib.h>

uint8_t stepTable[] = {0b1010, 0b0110, 0b0101, 0b1001};
// 외부 장치 선언
extern UART_HandleTypeDef huart2;

// [b2] [b1] [a2] [a1]
void runStep(uint8_t inData){
	HAL_GPIO_WritePin(MTA1_GPIO_Port, MTA1_Pin, ((inData >> 0) & 1));
	HAL_GPIO_WritePin(MTA2_GPIO_Port, MTA2_Pin, ((inData >> 1) & 1));
	HAL_GPIO_WritePin(MTB1_GPIO_Port, MTB1_Pin, ((inData >> 2) & 1));
	HAL_GPIO_WritePin(MTB2_GPIO_Port, MTB2_Pin, ((inData >> 3) & 1));
}

void app(){
	// uart 장치 초기화
	initUart(&huart2);
	while(1){
		static uint8_t index = 0;
		static uint8_t direction = 0;
		char ch = getUart();
		if(ch=='f') direction =1;
		if(ch=='r') direction =2;
		if(ch=='s') direction =0;
		// 현재 명령의 진행
		if(direction ==1) {
			index++;
			index%=4;
		}
		else if(direction == 2){
			index--;
			if(index==255) index =3;
		}
		runStep(stepTable[index]);
		HAL_Delay(5);
	}
}
