/*
 * LPSCI.c
 *
 *  Created on: 24. 1. 2020
 *      Author: Daniel
 */


#include <stdint.h>

#include "board.h"
#include "fsl_lpsci.h"
#include "clock_config.h"
#include "pin_mux.h"

//#include "lift_defs.h"

#define LPSCI_UART UART0
#define LPSCI_CLKSRC kCLOCK_CoreSysClk
#define LPSCI_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define LPSCI_IRQn UART0_IRQn
#define LPSCI_IRQHandler UART0_IRQHandler
#define RX_RINGBUFF_SIZE 32
#define SERIAL_SPEED 230400

uint8_t rx_buff_wptr = RX_RINGBUFF_SIZE-1, rx_buff_rptr = RX_RINGBUFF_SIZE-1;
char rx_buff[RX_RINGBUFF_SIZE];
uint8_t bytes_to_parse = 0;

void LPSCI_IRQHandler(void){

    if ((kLPSCI_RxDataRegFullFlag)&LPSCI_GetStatusFlags(LPSCI_UART)) {
        uint8_t data = LPSCI_ReadByte(LPSCI_UART);

        rx_buff_wptr++;
        rx_buff_wptr %= RX_RINGBUFF_SIZE;
        rx_buff[rx_buff_wptr] = data;
        bytes_to_parse++;
    }
}

void lpsci_init(){
	lpsci_config_t config;

    CLOCK_SetLpsci0Clock(0x1U);

    LPSCI_GetDefaultConfig(&config);
    config.baudRate_Bps = SERIAL_SPEED;
    config.enableTx = true;
    config.enableRx = true;

    LPSCI_Init(LPSCI_UART, &config, LPSCI_CLK_FREQ);

    LPSCI_EnableInterrupts(LPSCI_UART, kLPSCI_RxDataRegFullInterruptEnable);

    NVIC_SetPriority(LPSCI_IRQn, 2);
    EnableIRQ(LPSCI_IRQn);
}

void lpsci_send(char *buff, size_t dlzka){
    LPSCI_WriteBlocking(LPSCI_UART, (uint8_t *) buff, dlzka);
}
