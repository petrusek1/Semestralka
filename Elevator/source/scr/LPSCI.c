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
#include "include/Definitions.h"

#define UART UART0
#define CLKSRC kCLOCK_CoreSysClk
#define CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define IRQn UART0_IRQn
#define IRQHandler UART0_IRQHandler


volatile uint8_t rx_buff_write_pointer = RX_RINGBUFF_SIZE-1;
volatile uint8_t rx_buff_read_pointer = RX_RINGBUFF_SIZE-1;
volatile char rx_buff[RX_RINGBUFF_SIZE];
volatile uint8_t bytes_to_parse = 0;

void IRQHandler(void){

    if ((kLPSCI_RxDataRegFullFlag)&LPSCI_GetStatusFlags(UART)) {
        uint8_t data = LPSCI_ReadByte(UART);

        rx_buff_write_pointer++;
        rx_buff_write_pointer %= RX_RINGBUFF_SIZE;
        rx_buff[rx_buff_write_pointer] = data;
        bytes_to_parse++;
    }
}

//metoda na inicializovanie komunikacneho rozhranie
void lpsci_init(){
	lpsci_config_t config;

    CLOCK_SetLpsci0Clock(0x1U);

    LPSCI_GetDefaultConfig(&config);
    config.baudRate_Bps = BAUDRATE;
    config.enableTx = true;
    config.enableRx = true;

    LPSCI_Init(UART, &config, CLK_FREQ);

    LPSCI_EnableInterrupts(UART, kLPSCI_RxDataRegFullInterruptEnable);

    NVIC_SetPriority(IRQn, 2);
    EnableIRQ(IRQn);
}

void lpsci_sendMessage(char *buff, size_t dlzka){
    LPSCI_WriteBlocking(UART, (uint8_t *) buff, dlzka);
}
