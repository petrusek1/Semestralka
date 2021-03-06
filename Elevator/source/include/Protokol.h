/*
 * Protokol.h
 *
 *  Created on: 25. 1. 2020
 *      Author: Daniel
 */

#ifndef INCLUDE_PROTOKOL_H_
#define INCLUDE_PROTOKOL_H_

//bytova poloha s rx buferu vytahu
#define packet(pckt) rx_buff[(start + pckt) % RX_RINGBUFF_SIZE]
//metoda na poslanie spravy vytahu
void protocol_sendMessage(char dest, char *data, size_t data_dlzka);
//metoda na analizovanie spravy s lpsci bufera
void analize_incoming_packet();

#endif /* INCLUDE_PROTOKOL_H_ */
