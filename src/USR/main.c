#include "gpio.h"
#include "uart.h"
#include "delay.h"


#include "spi.h"
#include "pit.h"
#include "adc.h"
#include "i2c.h"

#include "stdio.h"
#include "TPM.h"
#include "user.h"
#include "app.h"
#include "counter.h"
#include "include.h"

const uint32_t pwmNumber = 4;
const uint8_t pwmArray[pwmNumber] = {PTA5, PTA12, PTE24, PTE25};
const uint32_t maxPwmDuty = 6000;

static uint32_t time = 400;

static int32_t balance = 0, speed = 0, turn = 0;

int main(void){
  //请认真确定你的外部晶振是否对应，8M请输入参数ClockSource_EX8M，
	//50M请输入参数ClockSource_EX50M。超频频率请使用 go to查看函数定义
  SystemClockSetup(ClockSource_EX50M,CoreClock_120M);
	UART_PortInit(UART0_RX_PD06_TX_PD07,128000);
	UART_PortInit(UART1_RX_PE01_TX_PE00,96000);
  DelayInit();
  DisableInterrupts();
	
	PWM_userInit(pwmArray, pwmNumber, maxPwmDuty);
	ADC_userInit();
	GPIO_userInit();
	PIT_userInit();
	Counter0_Init();
	Counter1_Init();

	while(1){
		if(PIT_GetITStatus(PIT0, PIT_IT_TIF) == SET){
			PIT_ClearITPendingBit(PIT0, PIT_IT_TIF);
			
			if(time>0) { time--; continue; }

			balance = balanceCtrl();
			speed = speedCtrl();
			turn = directionCtrl();
			
			motorControl(balance, speed, turn);
		}
	}
}
