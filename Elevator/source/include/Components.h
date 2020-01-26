/*
 * Components.h
 *
 *  Created on: 25. 1. 2020
 *      Author: Daniel
 */

#ifndef INCLUDE_COMPONENTS_H_
#define INCLUDE_COMPONENTS_H_
#include "Definitions.h"
#include "stdint.h"


void elevator_init();

void door_control(uint8_t new_state);

void led_set(uint8_t led, uint8_t power);

void motor_stop();

void motor_move(int8_t speed);

void motor_read_enc();

void set_brake(uint8_t state);

void lcd(uint8_t dir, uint8_t floor);

uint8_t get_events_pending();

uint8_t event_add(char source, char data);

event_t event_read();


#endif /* INCLUDE_COMPONENTS_H_ */
