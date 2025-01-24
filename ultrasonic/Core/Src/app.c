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
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim11;
extern UART_HandleTypeDef huart2;

void delay_us(uint16_t t){
	htim11.Instance->CNT= 0;
	while(htim11.Instance->CNT<t);
}

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
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//pwm
	HAL_TIM_Base_Start(&htim11);//서로 다른 종류의 스타트 카운팅만 되는 스타트
	initUltrasonic(&htim3);
	while(1){
		uint8_t distance = getDistance();
		printf("distance = %d\n", distance);
		HAL_Delay(50);
		/*if(distance>50){
			stopSound();
		}
		else if(distance>20){
			setSound(500);
			HAL_Delay(500);
			stopSound();
			HAL_Delay(500);
		}
		else if(distance>15){
			setSound(500);
			HAL_Delay(400);
			stopSound();
			HAL_Delay(400);
		}
		else if(distance>10){
					setSound(500);
					HAL_Delay(300);
					stopSound();
					HAL_Delay(300);
				}
		else if(distance>5){
					setSound(500);
					HAL_Delay(200);
					stopSound();
					HAL_Delay(200);
				}
		else{
			htim1.Instance->CCR1 = htim1.Instance->ARR/2;
		}*/
		htim1.Instance->CCR1 = htim1.Instance->ARR/2;
	}
}
