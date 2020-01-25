/*
 * MMA8451.c
 *
 *  Created on: 24. 1. 2020
 *      Author: Daniel
 */


#include "include/i2c.h"
#include "include/MMA8451.h"


void mma8451_init(){
	iic_write(MMA8451_ADDR, ADDR_CTRL_REG1, 0x00);
	iic_write(MMA8451_ADDR, ADDR_XYZ_DATA_CFG, 0x01);	//	+/- 4G
	iic_write(MMA8451_ADDR, ADDR_CTRL_REG4, 0x08);		// pulse int
	iic_write(MMA8451_ADDR, ADDR_CTRL_REG5, 0x00);		// pulse int pin

	iic_write(MMA8451_ADDR, ADDR_PULSE_THSY, 15);		//pulse Y treshold
	iic_write(MMA8451_ADDR, ADDR_PULSE_TMLT, 5);		//tap pulse time limit
	iic_write(MMA8451_ADDR, ADDR_PULSE_CFG, 0x04);
	iic_write(MMA8451_ADDR, ADDR_PULSE_LTCY, 20);		//tap detect latency

	iic_write(MMA8451_ADDR, ADDR_CTRL_REG1, 0x1D);		// 100 Hz
}
