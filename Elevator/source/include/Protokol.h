/*
 * Protokol.h
 *
 *  Created on: 25. 1. 2020
 *      Author: Daniel
 */

#ifndef INCLUDE_PROTOKOL_H_
#define INCLUDE_PROTOKOL_H_

//zadefinovanie packetu
#define packet(pckt) rx_buff[(start + pckt) % RX_RINGBUFF_SIZE]
//metoda na poslanie paketu
void protocol_sendMessage(char dest, char *data, size_t data_dlzka);
//metoda na rozparsovanie
void parse();

#endif /* INCLUDE_PROTOKOL_H_ */
