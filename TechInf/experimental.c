/*
 * Starduino.c
 *
 * Created: 07.05.2018 14:09:30
 *  Author: 81moni1bif
 */ 


#include <avr/io.h>
#define TASTE PINB

volatile int i,active_time,period;

int step_width;


int main(void) {
	step_width = 1; // s ist die Schrittweite fuer die Tastensteuerung
	int max = 10000; // T ist die gesamte Periodendauer
	volatile int frequency = 5; // in hz
	volatile int switch_time = max/frequency;
	volatile int frequency2 = 5;	
	volatile int switch_time2 = max/frequency2;
	
	PORTC = 0b00100010; // ein Anfangsmuster
	DDRC = 0b00111111; // Ausgaenge aktivieren
	
	
	
	while(1){
		//PORTC = 0b00100010;
		
		for(i=0; i<max;i++){
			if(i==switch_time){
				PORTC ^= 0b00000010;
			}
			if(i==switch_time2){
				
				PORTC ^= 0b00100000;
			}
			if(TASTE & 1){ //increase frequency of light 2
				frequency+=step_width;
				switch_time = max/frequency;
			}
			if(TASTE & 4){ //reset lights
				PORTC = 0b00100010;
				switch_time=-1;
				switch_time2=-1;
			}
			if(TASTE & 16){ //increase frequency of light 6
				frequency2+=step_width;
				switch_time2 = max/frequency2;
			}
		}	
		
	}
	
	
	//// Beginn Hauptschleife
	//for (;;) { // Eine Endlosschleife
		//PORTC ^= 0b00111111; // Invertieren der Lampen an Port B
		//
		//for (i=0;i<period;i++) { // eine Periode zaehlen
			//if (i==active_time) PORTC ^= 0b00000001; // beim Vergleichspunkt Lampen umschalten
			//if(i==active_time2) PORTC ^=0b00010100;
		//}
		//if (TASTE & 1) active_time+=step_width;	// Pulsbreite erhoehen
		//if (active_time>=period) active_time=period-1; 
		//if (TASTE & 4) active_time2 += step_width;
		//if(active_time2 >= period)active_time=period-1 //reset when overflow
		//
		//if (TASTE & 16) active_time-=step_width;
		//if (active_time<0) active_time=0; // Pulsbreite erniedrigen
	//}
}
