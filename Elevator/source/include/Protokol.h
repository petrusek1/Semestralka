/*
 * Protokol.h
 *
 *  Created on: 25. 1. 2020
 *      Author: Daniel
 */

#ifndef INCLUDE_PROTOKOL_H_
#define INCLUDE_PROTOKOL_H_


#define packet(pos) rx_buff[(start + pos) % RX_RINGBUFF_SIZE]

void send(char dest, char *data, size_t data_len);

void parse();

#endif /* INCLUDE_PROTOKOL_H_ */
