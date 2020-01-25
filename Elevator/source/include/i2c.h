/*
 * i2c.h
 *
 *  Created on: 24. 1. 2020
 *      Author: Daniel
 */

#ifndef INCLUDE_I2C_H_
#define INCLUDE_I2C_H_

#include "fsl_i2c.h"

/**
 * \brief i2c initialization
 */
void i2c_init();

/**
 * \brief write one byte to i2c device
 */
bool i2c_write(uint8_t device, uint8_t addr, uint8_t data);

/**
 * \brief read one byte from i2c device
 */
bool i2c_read(uint8_t device, uint8_t rd_addr, uint8_t *rd_data, size_t dlzka);

#endif /* INCLUDE_I2C_H_ */
