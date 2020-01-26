/*
 * MMA8451.h
 *
 *  Created on: 24. 1. 2020
 *      Author: Daniel
 */

#ifndef INCLUDE_MMA8451_H_
#define INCLUDE_MMA8451_H_



#include <stdint.h>


#define MMA8451_ADDR 0x1D

#define ADDR_XYZ_DATA_CFG 0x0E
#define ADDR_CTRL_REG1 0x2A
#define ADDR_CTRL_REG4 0x2D
#define ADDR_CTRL_REG5 0x2E
#define ADDR_PULSE_CFG 0x21
#define ADDR_PULSE_THSX 0x23
#define ADDR_PULSE_THSY 0x24
#define ADDR_PULSE_THSZ 0x25
#define ADDR_PULSE_TMLT 0x26
#define ADDR_PULSE_LTCY 0x27

void mma8451_init();

#endif /* MMA8451_H_ */
