/**
 * \file lscpi.h
 *
 * \brief lscpi header file
 */

#ifndef LPSCI_H_
#define LPSCI_H_

#include <stddef.h>

/**
 * \brief initialize lpsci hardware with interrupt based reading
 */
void lpsci_init();

/**
 * \brief send buffer via lpsci
 */
void lpsci_send(char *buff, size_t len);

#endif /* LPSCI_H_ */
