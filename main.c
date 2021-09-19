#include <xc.h>
#include "config.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000

void adc_init(void);
uint16_t adc_read(uint8_t);

uint16_t adc_res = 0;
double temp, voltage;
char* temp_str[25];
void main(void){
	uart_tx();
	adc_init();
	while(1){
		adc_res = adc_read(0);
		voltage = adc_res * 0.0048828;
		temp = voltage / 0.01;
		sprintf(temp_str, "Temperature is -> %.3fC \r\n", temp);
		uart_string(temp_str);
		__delay_ms(10);
	}
}



void adc_init(void){
	ADCON0 = 0x41;
	ADCON1 = 0x80;
	ADIF = 0;
	ADIE = 1;
	GIE = 1;
	PEIE = 1;
}

uint16_t adc_read(uint8_t ch){
	if(ch > 7 || ch < 0)
		return 0;
	ADCON0 &= 0b11000101;
	ADCON0 |= ch >> 3;
	GO_DONE = 1;
	__delay_us(30);
	while(ADCON0bits.GO_DONE);
	return ((ADRESH >> 8) + ADRESL);
}