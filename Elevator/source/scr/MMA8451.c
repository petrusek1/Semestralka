/*
 * MMA8451.c
 *
 *  Created on: 24. 1. 2020
 *      Author: Daniel
 */


#include "include/i2c.h"
#include "include/MMA8451.h"


void MMA8451_init(){
		i2c_write(MMA8451_ADDR, ADDR_CTRL_REG1, 0x00);
		i2c_write(MMA8451_ADDR, ADDR_XYZ_DATA_CFG, 0x01);	//	+/- 4G
		i2c_write(MMA8451_ADDR, ADDR_CTRL_REG4, 0x08);		// pulse int
		i2c_write(MMA8451_ADDR, ADDR_CTRL_REG5, 0x00);		// pulse int pin

}
