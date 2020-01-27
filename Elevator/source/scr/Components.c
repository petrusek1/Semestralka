/*
 * Components.c
 *
 *  Created on: 25. 1. 2020
 *      Author: Daniel
 */


#include <stdint.h>
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include "include/Timer.h"
#include "include/Protokol.h"
#include "include/Definitions.h"
#include "include/Components.h"

uint8_t events = 0;
uint8_t event_buff_write_pointer = 0;
char event_buff[EVENT_BUFF_SIZE][2];
extern volatile char timer_int;
extern volatile uint8_t rx_buff_write_pointer ;
extern volatile uint8_t rx_buff_read_pointer;

int16_t cabin_position = 0;  //-1

//inicializacia elevatoru ,zistenie statusu, vypnutie vsetkych led
void elevator_init(){
	motor_read_status();

	for(uint8_t i=0; i<5; i++)
		led_set(LED_WALL_P + i, LED_OFF);
	for(uint8_t i=0; i<5; i++)
		led_set(LED_CABIN_P + i, LED_OFF);
}

//kontrola stavu dveri
void status_door_control(uint8_t new_state){
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
char next_floor_dir(uint_fast8_t aktualne_poschodie, uint_fast8_t tlacidla, char smer){
	uint8_t min_smer=255;
	uint8_t min_vzdialenost=255;

	for(uint8_t i=0; i<=4; i++){
		if(tlacidla & (1<<i)){
			uint8_t vzdialenost = abs((aktualne_poschodie - i));
			if((i < aktualne_poschodie) == (smer == UP))
				vzdialenost += 5;
			if(vzdialenost < min_vzdialenost){
				min_vzdialenost = vzdialenost;
				min_smer = i;
			}
		}
	}

	if(min_smer > aktualne_poschodie)
		return UP;
	else
		return DOWN;
}



void delay_ms_timer(const uint_fast16_t time){
	timer_start_ms(time);

	while(!timer_int){
		if(rx_buff_read_pointer != rx_buff_write_pointer)
			analize_incoming_packet();

	}
}

//metoda na parkovanie vytahu _zarovnanie cca na poschodie
void elevator_parking(){
	extern int16_t cabin_position;

	while(cabin_position < 0){
					if(rx_buff_read_pointer != rx_buff_write_pointer)
						analize_incoming_packet();
				}
		//zistenie a zaparkovanie na poschodi start
		uint8_t aktualne_poschodie = (cabin_position - 50) / FLOOR_HEIGHT;
				if(cabin_position < 50)

				aktualne_poschodie = 0;
				if(((cabin_position - 50) % 225) > (FLOOR_HEIGHT/2))
					aktualne_poschodie++;
				lcd(LCD_CLEAR, aktualne_poschodie);

		int16_t pos_vzd; //(vzdialenost poschodia)
		pos_vzd = cabin_position - (50 + (aktualne_poschodie * FLOOR_HEIGHT));


		if(abs(pos_vzd) > 2){
					int8_t spd; //rychlost speed
					status_door_control(DOOR_LOCK);
					delay_ms_timer(1000);

					if(abs(pos_vzd) > 40)
						spd = MOTOR_SPEED_PARK_HI;   //parkovanie vytahu ma poschodi podla rychlosti
					else
						spd = MOTOR_SPEED_PARK_LOW;

					if(pos_vzd > 0)
						spd = -spd;

					motor_move(spd);

					while(1){
								if(rx_buff_read_pointer != rx_buff_write_pointer)
									analize_incoming_packet();

								if( get_events()){
									event_t udalost;
									udalost = event_read();

									if((udalost.device >= LIMIT_SW_MIN) && (udalost.device <= LIMIT_SW_MAX)){
										if(udalost.data == LIMIT_DIST_MED){
											if(spd > 0)
											motor_move(MOTOR_SPEED_PARK_LOW);
											else
												motor_move(-MOTOR_SPEED_PARK_LOW);
										} else if(udalost.data == LIMIT_DIST_CLOSE) {
											motor_stop();
											break;
										}
									}
								}
							}
					delay_ms_timer(1000);
			}

			status_door_control(DOOR_UNLOCK);



}


//logika pre pohyb vytahu pri stlaceni tlacidla
void elevator_moving_buttons(){
		uint8_t tlacidla=0;

		char pohyb = 0;
		char smer = 0;
		uint8_t aktualne_poschodie = (cabin_position - 50) / FLOOR_HEIGHT;
		while(1){



			if( get_events()){
				event_t udalost;
				udalost = event_read();

				if((((udalost.device & 0xF0) == BUTTON_WALL_P) || ((udalost.device & 0xF0) == BUTTON_CABIN_P)) && !(!pohyb && (aktualne_poschodie == (udalost.device & 0x0F)))){
					uint8_t tlacidlo = udalost.device & 0x0F;

										tlacidla |= 1 << tlacidlo;
										if((udalost.device & 0xF0) == BUTTON_WALL_P)
											led_set(LED_WALL_P + tlacidlo, 1);
										else
											led_set(LED_CABIN_P + tlacidlo, 1);
				}

				//osetrene koncove spinace
				else if((udalost.device & 0xF0) == LIMIT_SW_P) {
					char poschodie = udalost.device - LIMIT_SW_P;
										lcd(1+smer, poschodie);

										if((tlacidla & (1<<poschodie)) && udalost.data == LIMIT_DIST_CLOSE) {

											motor_stop();
											pohyb = 0;
											aktualne_poschodie = poschodie;
											led_set(LED_CABIN_P + poschodie, LED_OFF);
											led_set(LED_WALL_P + poschodie, LED_OFF);
											tlacidla &= ~(1<<poschodie);
											lcd(LCD_CLEAR, poschodie);
											delay_ms_timer(1000);
											status_door_control(DOOR_UNLOCK);
											delay_ms_timer(DOOR_OPENING_MS);
											delay_ms_timer(DELAY_FLOOR_MS);
										}

										else if((tlacidla & (1<<poschodie)) && udalost.data == LIMIT_DIST_MED){
											motor_move(smer==UP ? MOTOR_SPEED_LOW : -MOTOR_SPEED_LOW);
										}
				}
						}




			if(rx_buff_read_pointer != rx_buff_write_pointer)
				analize_incoming_packet();

			if(!pohyb && tlacidla){
							smer = next_floor_dir(aktualne_poschodie, tlacidla, smer);

							status_door_control(DOOR_LOCK);
							delay_ms_timer(DOOR_CLOSING_MS);
							lcd(1+smer, aktualne_poschodie);
							motor_move(smer==UP ? MOTOR_SPEED_HI : -MOTOR_SPEED_HI);
							pohyb = 1;
						}


		}

}
