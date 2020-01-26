/*
 * Components.c
 *
 *  Created on: 25. 1. 2020
 *      Author: Daniel
 */


#include <stdint.h>
#include "stdio.h"
#include "string.h"

#include "include/Protokol.h"
#include "include/Definitions.h"
#include "include/Components.h"

uint8_t events = 0;
uint8_t event_buff_write_pointer = 0;
char event_buff[EVENT_BUFF_SIZE][2];
extern volatile uint8_t rx_buff_wptr, rx_buff_rptr;
int16_t cabin_position = -1;

//inicializacia elevatoru ,zistenie statusu, vypnutie vsetkych led
void elevator_init(){
	motor_read_status();

	for(uint8_t i=0; i<5; i++)
		led_set(LED_WALL_P + i, LED_OFF);
	for(uint8_t i=0; i<5; i++)
		led_set(LED_CABIN_P + i, LED_OFF);
}

//kontrola stavu dveri
void door_control(uint8_t new_state){
	protocol_sendMessage(DOOR, (char *) &new_state, 1);
}
//rozsvietenie led
void led_set(uint8_t led, uint8_t power){
	protocol_sendMessage(led, (char *) &power, 1);
}
//stop motor
void motor_stop(){
	char tmp = MOTOR_STOP;
	protocol_sendMessage(MOTOR, &tmp, 1);
}

//pohyb motora
void motor_move(int8_t speed){
	char tmp[5];
	int32_t spd = speed;

	tmp[0] = MOTOR_MOVE;
	memcpy(tmp+1, &spd, 4);
	protocol_sendMessage(MOTOR, tmp,  5);
}
//metoda na zistenie stavu motora
void motor_read_status(){
	char tmp = MOTOR_GET_STATUS;
	protocol_sendMessage(MOTOR, &tmp, 1);
}

//metoda pre LCD display
void lcd(uint8_t dir, uint8_t floor){
	if(floor <5){
		char tmp[2];
		tmp[0] = dir;
		tmp[1] = (floor == 0) ? ('P') : ('0' + floor);

		protocol_sendMessage(LCD, tmp, 2);
	}else{
		char tmp[2];
		tmp[0] = dir;
		tmp[1] = ' ';

		protocol_sendMessage(LCD, tmp, 2);
	}
}
//funckia na poziadavky
uint8_t get_events(){
	return events;
}
//funckia na pridanie dalsej poziadavky
uint8_t event_add(char zdroj, char data){
	if(events < EVENT_BUFF_SIZE){
		event_buff[event_buff_write_pointer][0] = zdroj;
		event_buff[event_buff_write_pointer][1] = data;

		event_buff_write_pointer++;
		event_buff_write_pointer %= EVENT_BUFF_SIZE;

		events++;
		return 1;
	}
	else
		return 0;
}
//funckia na citanie poziadavok(udalosti)
event_t event_read(){
	event_t udalost;

	if(events == 0){
		udalost.device = 0;
		udalost.data = 0;
	}
	else {
		uint8_t tmp = (event_buff_write_pointer + EVENT_BUFF_SIZE - events) % EVENT_BUFF_SIZE;
		events--;

		udalost.data = event_buff[tmp][1];
		udalost.device = event_buff[tmp][0];
	}
	return udalost;
}

//funckia na vypocet dalsieho poschodia
char next_floor_dir(uint_fast8_t aktualny_stav, uint_fast8_t tlacidlo, char stav){
	uint8_t min_stav=255;
	uint8_t min_vzdialenost=255;

	for(uint8_t i=0; i<=4; i++){
		if(tlacidlo & (1<<i)){
			uint8_t vzdialenost = abs((aktualny_stav - i));
			if((i < aktualny_stav) == (stav == UP))
				vzdialenost += 5;
			if(vzdialenost < min_vzdialenost){
				min_vzdialenost = vzdialenost;
				min_stav = i;
			}
		}
	}

	if(min_stav > aktualny_stav)
		return UP;
	else
		return DOWN;
}
