/* ////////////////////////////////////////////////////////////////////////////
/ Author :Eslam Aboutaleb
/
/
/////////////////////////////////////////////////////////////////////////// */

#include <string.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "NVIC_interface.h"
#include "Timer_interface.h"
#include "main_SupportFuncs.h"

uint32 MILLIS_PRESCALER=(F_CPU/1000);



void OS_Timer_Init(void)
{
	/*Enable NVIC*/
	NVIC_Init();
	/*Enable Timer 1 interrupt*/
	NVIC_EnableInterrupt(TIM1_UP_TIM10_IRQn);
	/*Set Timer to the lowest priority in NVIC*/
	NVIC_SetPeriority(TIM1_UP_TIM10_IRQn,NVIC_Priority_15);
	/*Struct element to initialize timer*/
	TIM_ConfigType Timer;
	memset(&Timer,0,sizeof(Timer));
	/*Enable Timer*/
	Timer.Counter_State=Enable_CNT;
	/*Initialize period value */
	Timer.PeriodVal=TMR_TICK_MS;
	/*Initialize prescaler*/
	Timer.PrescalerVal=MILLIS_PRESCALER;
	/*Initialize Timer as Down counter*/
	Timer.Direction_State=UpCounter;
	/*Enable Timer interrupt*/
	Timer.UDI_State=Enable_TIM_Update_Interrupts;
	/*Initialize Timer*/
	TIM_Init(TIMER1,&Timer);
}


