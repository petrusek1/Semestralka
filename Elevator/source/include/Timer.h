/*
 * Timer.h
 *
 *  Created on: 25. 1. 2020
 *      Author: Daniel
 */

#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

//inicializacia timeru
void timer_init(const uint16_t t1_period_ms);
//metoda na start timeru v ms
void timerstart_ms(const uint16_t time);
//start
void timerstart();
//stop
void timerstop();
#endif /* INCLUDE_TIMER_H_ */
