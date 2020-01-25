/*
 * Timer.c
 *
 *  Created on: 25. 1. 2020
 *      Author: Daniel
 */

#include "fsl_pit.h"
#include "pin_mux.h"
#include "board.h"

#include "include/Timer.h"

char timer_int=0;

void PIT_IRQHandler(){
	if(PIT_GetStatusFlags(PIT, kPIT_Chnl_1) & kPIT_TimerFlag){
		PIT_ClearStatusFlags(PIT, kPIT_Chnl_1, kPIT_TimerFlag);
		timerstop();
		timer_int = 1;
	}
}

void timer_init(const uint16_t t1_period_ms){
    pit_config_t pitconf;
    PIT_GetDefaultConfig(&pitconf);

    PIT_Init(PIT,  &pitconf);
    PIT_SetTimerPeriod(PIT,  kPIT_Chnl_0, USEC_TO_COUNT(t1_period_ms * 1000U, CLOCK_GetBusClkFreq()));
    PIT_SetTimerPeriod(PIT,  kPIT_Chnl_1, USEC_TO_COUNT(100000U, CLOCK_GetBusClkFreq()));
    PIT_EnableInterrupts(PIT,  kPIT_Chnl_0, kPIT_TimerInterruptEnable);
    PIT_EnableInterrupts(PIT,  kPIT_Chnl_1, kPIT_TimerInterruptEnable);

    NVIC_SetPriority(PIT_IRQn, 3);
    EnableIRQ(PIT_IRQn);
}

void timerstart_ms(const uint16_t time){
	timer_int = 0;
	PIT_SetTimerPeriod(PIT,  kPIT_Chnl_1, USEC_TO_COUNT(time * 1000U, CLOCK_GetBusClkFreq()));
	timerstart();
}

void timerstart(){
    PIT_StartTimer(PIT, kPIT_Chnl_1);
}

void timerstop(){
    PIT_StopTimer(PIT, kPIT_Chnl_1);
}
