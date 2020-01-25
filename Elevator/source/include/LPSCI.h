/*
 * LPSCI.h
 *
 *  Created on: 24. 1. 2020
 *      Author: Daniel
 */

#ifndef INCLUDE_LPSCI_H_
#define INCLUDE_LPSCI_H_

#include <stddef.h>


void lpsci_init();
void lpsci_send(char *buff, size_t dlzka);

#endif /* INCLUDE_LPSCI_H_ */
