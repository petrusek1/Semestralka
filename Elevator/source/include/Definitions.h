/*
 * Definitions.h
 *
 *  Created on: 25. 1. 2020
 *      Author: Daniel
 */

#ifndef INCLUDE_DEFINITIONS_H_
#define INCLUDE_DEFINITIONS_H_
#include "stdint.h"

//definicia pre vytah
#define BAUDRATE 230400
#define FLOOR_HEIGHT 225
#define DOOR_OPENING_MS 500
#define DOOR_CLOSING_MS 500
#define DELAY_FLOOR_MS 1000
#define MOTOR_SPEED_HI 100
#define MOTOR_SPEED_LOW 10
#define MOTOR_SPEED_PARK_HI 25
#define MOTOR_SPEED_PARK_LOW 10
#define RX_RINGBUFF_SIZE 32
#define EVENT_BUFF_SIZE 2
#define CONTROLLER_ADDR 0x00
#define RETRY_COUNT 10;
#define DOOR 0xF0
#define MOTOR 0xF1
#define BRAKE 0x0F
#define LCD 0x30

//enum pre led Zapnute/Vypnute
enum {
	LED_OFF,
	LED_ON
};

//enum pre dvere Zamknute/Otvorene
enum {
	DOOR_UNLOCK,
	DOOR_LOCK
};

//Status pre LCD display
enum {
	LCD_CLEAR,
	LCD_UP,
	LCD_DOWN
};

//enum pre poschodia
enum {
	LCD_FLOOR_P,
	LCD_FLOOR_1,
	LCD_FLOOR_2,
	LCD_FLOOR_3,
	LCD_FLOOR_4,
	LCD_FLOOR_NONE = 255
};

//enum pre status motora pohyb/stop/ry&chlost/status
enum {
	MOTOR_STOP = 0x01,
	MOTOR_MOVE,
	MOTOR_GET_STATUS,
	MOTOR_GET_SPEED
};


//enum pre LED na stene pre vytah
enum {
	LED_WALL_P = 0x10,
	LED_WALL_1,
	LED_WALL_2,
	LED_WALL_3,
	LED_WALL_4,

};

//enum pre LED v kabine vytahu
enum {
	LED_CABIN_P = 0x20,
	LED_CABIN_1,
	LED_CABIN_2,
	LED_CABIN_3,
	LED_CABIN_4,
};

//enum pre tlacidla vo vytahu
enum {
	BUTTON_CABIN_P = 0xB0,
	BUTTON_CABIN_1,
	BUTTON_CABIN_2,
	BUTTON_CABIN_3,
	BUTTON_CABIN_4,

};

//enum pre tlacidla na stene pre vytah
enum {
	BUTTON_WALL_P = 0xC0,
	BUTTON_WALL_1,
	BUTTON_WALL_2,
	BUTTON_WALL_3,
	BUTTON_WALL_4,

};


//enum pre spinace
enum {
	LIMIT_SW_MIN = 0xDF,
	LIMIT_SW_P,
	LIMIT_SW_1,
	LIMIT_SW_2,
	LIMIT_SW_3,
	LIMIT_SW_4,
	LIMIT_SW_MAX
};

enum {
	LIMIT_DIST_FAR,
	LIMIT_DIST_MED,
	LIMIT_DIST_CLOSE
};


//enum pre stav pohybu hore/dole
enum {
	UP,
	DOWN
};

typedef struct {
	uint8_t device;
	char data;
} event_t;


#endif /* INCLUDE_DEFINITIONS_H_ */
