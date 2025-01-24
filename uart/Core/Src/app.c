/*
 * app.c
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */


#include "app.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
extern UART_HandleTypeDef huart2;

// interrupt callback for blue switch
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == SW_Pin){
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	}
}
//int _write(int file, char *p, int len){
//	HAL_UART_Transmit(&huart2, (uint8_t *)p, len, 10);
//	return len;
//}
void app(){
	//uart 장치 초기화
	initUart(&huart2);
	int time = HAL_GetTick();
	int time2 = HAL_GetTick();
	while(1){
		if((time + 50) < HAL_GetTick()){//100이 delay time처럼 작용
			time = HAL_GetTick();
			static bool isRun = true;
			static int angle =0;
			if(isRun) angle++;
			angle%=360;
			int sinv = sin(angle*M_PI/180)*100+100;
			int cosv = cos(angle*M_PI/180)*100+100;
			printf("%d,%d\n",sinv,cosv);
			//uart에서 키 입력
			char ch = getUart();
			if(ch!=0){
				if(ch=='g') isRun =true;
				if(ch=='s') isRun =false;
			}
		}
		if((time2 + 365) < HAL_GetTick()){
			time2 = HAL_GetTick();
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		}
	}
}
