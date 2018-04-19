/*
 * Uebung4.c
 *
 * Created: 19.04.2018 14:04:47
 *  Author: 71scfe1bif
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>

void warten(volatile uint32_t anz){
	while(anz!=0){
		anz--;
	}
}

int main(void)
{
	/*
	int lampen[] = {2,8,32};
	int randomInt = 1;
	int buttonPressed= 1;
	uint32_t timer = 300000;
	DDRC = 0x3f;
	PORTC= 0b000000;
	
    while(buttonPressed)
    {
	buttonPressed= 0;
	randomInt = (rand()% 3);
	PORTC= lampen[randomInt];
	warten(timer);
	if(PINB == PORTC)
		buttonPressed = 1;
		
    }
	*/
	uint32_t kurz = 100000;
	uint32_t lang = 300000;
	DDRC = 0x3f;
	PORTC = 0b000000;
	uint8_t signal = 0b111111;
	uint8_t pause = 0b000000;
	
	
	PORTC = signal;
	warten(kurz);	
	PORTC = pause;
	warten(kurz);
	
	PORTC = signal;
	warten(lang);
	PORTC = pause;
	warten(lang);
	
	PORTC = signal;
	warten(lang);
	PORTC = pause;
	warten(kurz);
	
	PORTC = signal;
	warten(lang);
	PORTC = pause;
	warten(lang);
	
		PORTC = signal;
		warten(lang);
		PORTC = pause;
		warten(kurz);
		
				PORTC = signal;
				warten(kurz);
				PORTC = pause;
				warten(kurz);
				
						PORTC = signal;
						warten(lang);
						PORTC = pause;
						warten(kurz);					
						
						
	
}
