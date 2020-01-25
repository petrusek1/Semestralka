/*
 * Definitions.h
 *
 *  Created on: 25. 1. 2020
 *      Author: Daniel
 */

#ifndef INCLUDE_DEFINITIONS_H_
#define INCLUDE_DEFINITIONS_H_


#define SERIAL_SPEED 230400
#define FLOOR_HEIGHT 225
#define DOOR_OPENING_MS 1000
#define DOOR_CLOSING_MS 1000
#define DELAY_FLOOR_MS 1000
#define MOTOR_SPEED_HI 70
#define MOTOR_SPEED_LOW 10
#define MOTOR_SPEED_PARK_HI 25
#define MOTOR_SPEED_PARK_LOW 10
#define RX_RINGBUFF_SIZE 32
#define EVENT_BUFF_SIZE 8
#define CONTROLLER_ADDR 0x00
#define SERIAL_RETRY_COUNT 10;
#define ELEVATOR_DOOR 0xF0
#define ELEVATOR_MOTOR 0xF1
#define ELEVATOR_BRAKE 0x0F
#define ELEVATOR_LCD 0x30

enum {
	LED_OFF,
	LED_ON
};


enum {
	DOOR_UNLOCK,
	DOOR_LOCK
};


enum {
	BRAKE_OFF,
	BRAKE_ON
};

enum {
	WDT_CLR,
	WDT_RESET
};


enum {
	LCD_CLEAR,
	LCD_UP,
	LCD_DOWN
};


enum {
	LCD_FLOOR_P,
	LCD_FLOOR_1,
	LCD_FLOOR_2,
	LCD_FLOOR_3,
	LCD_FLOOR_4,
	LCD_FLOOR_NONE = 255
};


enum {
	MOTOR_STOP = 0x01,
	MOTOR_MOVE,
	MOTOR_GET_ENCODER,
	MOTOR_GET_SPEED
};


enum {
	LED_WALL_P = 0x10,
	LED_WALL_1,
	LED_WALL_2,
	LED_WALL_3,
	LED_WALL_4,
	LED_CABIN_P = 0x20,
	LED_CABIN_1,
	LED_CABIN_2,
	LED_CABIN_3,
	LED_CABIN_4,};

enum {
	BUTTON_CABIN_P = 0xB0,
	BUTTON_CABIN_1,
	BUTTON_CABIN_2,
	BUTTON_CABIN_3,
	BUTTON_CABIN_4,
	BUTTON_WALL_P = 0xC0,
	BUTTON_WALL_1,
	BUTTON_WALL_2,
	BUTTON_WALL_3,
	BUTTON_WALL_4,};


enum {
	LIMIT_SW_MIN = 0xDF,
	LIMIT_SW_P,
	LIMIT_SW_1,
	LIMIT_SW_2,
	LIMIT_SW_3,
	LIMIT_SW_4,
	LIMIT_SW_MAX};

enum {
	LIMIT_DIST_FAR,
	LIMIT_DIST_MED,
	LIMIT_DIST_CLOSE};


enum {
	DIR_UP,
	DIR_DOWN};


typedef struct {
	uint8_t device;
	char data;} event_t;

#endif /* INCLUDE_DEFINITIONS_H_ */
