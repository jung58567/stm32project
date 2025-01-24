/*
 * app.c
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */

#include "app.h"

extern UART_HandleTypeDef huart2;

int cycle300ms;
int cycle380ms;

_Bool curSwitch=1;
// 인터럽트에 의하여 1ms마다 호출됨
void systickCallback(){
	static uint32_t swBuf;
	// 버퍼 왼쪽으로 쉬프트
	swBuf = swBuf<<1;
	// 버퍼 LSB에 현재의 스위치 상태를 저장
	swBuf |=HAL_GPIO_ReadPin(SW_GPIO_Port, SW_Pin);
	//버퍼의 값을 판단
	if(swBuf=0xffffffff) curSwitch = 1;
	if(swBuf==0x00000000) curSwitch = 0;
}

//메인 코드
void app(){
	int count =0;
	_Bool oldSwitch=1;
	//uart 장치 수신 인터럽트 초기화
	initUart(&huart2);
	while(1){
		if(curSwitch!=oldSwitch){
			if(curSwitch==0){
				count++;
				printf("count=%d\n",count);
			}
			oldSwitch = curSwitch;
		}
	}
}
