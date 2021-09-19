#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000

void uart_tx(void);
void uart_rx(void);
void uart_write(uint8_t);
void uart_string(char*);
//#define TX RC6
//#define RX RC7
#define TX_D TRISC6
#define RX_D TRISC7

void uart_tx(void){
	TX_D = 1;
	RX_D = 1;
	BRGH = 1;
	SYNC = 0;
	SPBRG = 25;
	SPEN = 1;
	TXEN = 1;
}

void uart_rx(void){
	TX_D = 1;
	RX_D = 1;
	BRGH = 1;
	SYNC = 0;
	SPBRG = 25;
	SPEN = 1;
	CREN = 1;
}

void uart_write(uint8_t data){
	while(!TRMT);
	TXREG = data;
}

void uart_string(char* str){
	for(int i=0; str[i] != '\0'; i++)
		uart_write(str[i]);
}