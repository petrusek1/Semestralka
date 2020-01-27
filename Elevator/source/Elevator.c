/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    Elevator.c
 * @brief   Application entry point.
 */
/**
 * \file vytah.c
 *
 * \brief program entry point and main elevator logic
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <stdint.h>
#include <stdlib.h>

#include "include/LPSCI.h"
#include "include/Components.h"
#include "include/Definitions.h"
#include "include/Protokol.h"
#include "include/Timer.h"
#include "include/i2c.h"
#include "include/MMA8451.h"

extern volatile uint8_t rx_buff_write_pointer ;
extern volatile uint8_t rx_buff_read_pointer;
uint8_t buttons=0;
extern int16_t cabin_position;
volatile char acc_int = 0;
//extern volatile char timer_int;
/**
 * \brief main program function
 */

/*void delay_ms_timer(const uint_fast16_t time){
	timerstart_ms(time);

	while(!timer_int){
		if(rx_buff_read_pointer != rx_buff_write_pointer)
			analize_incoming_packet();
		}
}
*/

int main(void) {

	BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();

    //inicializacia rozhrania ktore je potrebne
	i2c_init();
	MMA8451_init();
	EnableIRQ(PORTA_IRQn);
	lpsci_init();
	elevator_init();



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

		}

		status_door_control(DOOR_UNLOCK);






	  /* Force the counter to be placed into memory. */
	    volatile static int i = 0 ;
	    /* Enter an infinite loop, just incrementing a counter. */
	    while(1) {
	        i++ ;
	        /* 'Dummy' NOP to allow source level single stepping of
	            tight while() loop */
	        __asm volatile ("nop");
	    }
	    return 0 ;
}
