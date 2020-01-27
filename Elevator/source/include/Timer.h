/*
 * Timer.h
 *
 *  Created on: 27. 1. 2020
 *      Author: Daniel
 */

#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_


//inicializacia timeru
void timer_init(const uint16_t t1_period_ms);
//start timeru v ms
void timer_start_ms(const uint_fast16_t time);

#endif /* INCLUDE_TIMER_H_ */
