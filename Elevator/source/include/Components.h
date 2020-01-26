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

//inicializacia vytahu
void elevator_init();
//metoda na zistenie statusu dveri
void status_door(uint8_t new_status);
//metoda na nastavenie led on/off
void led_set(uint8_t led, uint8_t on);
//metoda na zstavenie motora
void motor_stop();
//metoda na pohyb vytahu
void motor_move(int8_t speed);
//metoda pre motor
void motor_read_status();
//mastavenie brzdy
void set_brake(uint8_t status);
//metoda pre lcd display
void lcd(uint8_t smer, uint8_t poschodie);
//funckia na cakanie dalsej poziadavky
uint8_t get_events_();
//funkcia na pridanie poziadavky
uint8_t event_add(char zdroj, char data);
//funkcia na citanie poziadavky
event_t event_read();
//funkcia na vypocet dalsieho stavu poschodia
char next_floor_dir(uint_fast8_t aktualny_stav, uint_fast8_t tlacidlo, char stav);

#endif /* INCLUDE_COMPONENTS_H_ */
