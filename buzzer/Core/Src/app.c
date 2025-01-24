/*
 * app.c
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */

#include "app.h"

//c d e f g a b C
uint16_t soundLUT[] = {261,293,329,349,392,440,493,523};
//장치 선언
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart2;

void setSound(uint16_t frequency){
	htim1.Instance->ARR = 1000000/frequency-1;
	htim1.Instance->CCR1 = htim1.Instance->ARR /2;
	htim1.Instance->CNT = 0;//CNT 초기화
}

void stopSound(){
	htim1.Instance->CCR1 = 0;
}
void app(){
	// uart 수신 인터럽트 시작
	initUart(&huart2);
	// 타이머 시작
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	while(1){
		char ch = getUart();
		switch(ch){
			case 'c': setSound(soundLUT[0]); break;
			case 'd': setSound(soundLUT[1]); break;
			case 'e': setSound(soundLUT[2]); break;
			case 'f': setSound(soundLUT[3]); break;
			case 'g': setSound(soundLUT[4]); break;
			case 'a': setSound(soundLUT[5]); break;
			case 'b': setSound(soundLUT[6]); break;
			case 'C': setSound(soundLUT[7]); break;
			case ' ': stopSound(); break;
			default: break;
		}
		HAL_Delay(300);
	}
}
