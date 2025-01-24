/*
 * app.c
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */

#include "app.h"
#include <stdlib.h>
// 외부 장치 선언
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;

// 0~100
void setSpeed(uint8_t speed){
	htim1.Instance->CCR1 = (speed*10)-1;
}

void runMotor(uint8_t direction){
	if(direction){
		HAL_GPIO_WritePin(Motor1_GPIO_Port, Motor1_Pin, 1);
		HAL_GPIO_WritePin(Motor2_GPIO_Port, Motor2_Pin, 0);
	}
	else{
		HAL_GPIO_WritePin(Motor1_GPIO_Port, Motor1_Pin, 0);
		HAL_GPIO_WritePin(Motor2_GPIO_Port, Motor2_Pin, 1);

	}
}

void stopMotor(){
	HAL_GPIO_WritePin(Motor1_GPIO_Port, Motor1_Pin, 0);
	HAL_GPIO_WritePin(Motor2_GPIO_Port, Motor2_Pin, 0);
}

void app(){
	// uart 초기화
	initUart(&huart2);
	// tim1 초기화
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	while(1){
		// f100\n, r080\n, stop\n
		char *msg = getMessage();
		if(strlen(msg)>3){
			if(msg[0]=='f'){
				runMotor(1);
				int speed = atoi(&msg[1]);
				setSpeed(speed);
			}
			else if(msg[0]=='r'){
				runMotor(0);
				int speed = atoi(&msg[1]);
				setSpeed(speed);
			}
			else if(strncmp(msg,"stop",4)==0) {
				stopMotor();
			}
		}
	}
}
