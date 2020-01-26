/**
 * \file lscpi.h
 *
 * \brief lscpi header file
 */

#ifndef LPSCI_H_
#define LPSCI_H_

#include <stddef.h>

//inicializacia rozhrania na komunikaciu
void lpsci_init();

//metoda na posielanie sprav
void lpsci_sendMessage(char *buff, size_t dlzka);

#endif /* LPSCI_H_ */
