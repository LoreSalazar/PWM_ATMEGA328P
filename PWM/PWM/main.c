/*
 * PWM.c
 *
 * Created: 10/11/2024 01:49:38 p.m.
 * Author : LSL
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
	int frequency = 100;
	int dutyCicle = 50;
	
    DDRD |= (1<<6); //Se establece como salida el pin 6 del puerto D
	//----------------------------------- FAST PWM -----------------------------------
	//COM0An
	//Compare Output Mode, Fast PWM: Normal port operation, OC0A disconnected
	TCCR0A |= (1<<COM0A1); //Clear OC0A on Compare Match, set OC0A at BOTTOM (non-inverting mode)
	TCCR0A &=~ (1<<COM0A0);  
	
	//Compare Output Mode for channel B: Normal port operation, OC0B disconnected
	TCCR0A |= (1<<COM0B1); // Clear OC0B on Compare Match, set OC0B at BOTTOM, (non-inverting mode)
	TCCR0A &=~ (1<<COM0B0);
	
	//Wareform Generation Mode: Fast PWM
	TCCR0A |= (1<<WGM01);
	TCCR0A |= (1<<WGM00);
	//Wareform Generation Mode: Fast PWM
	TCCR0B &=~ (1<<WGM02);
	
	//Force Output Compare A
	TCCR0B &=~ (1<<FOC0A);
	//Force Output Compare B
	TCCR0B &=~ (1<<FOC0B);
	
	//Clock Select Bit Description
	TCCR0B |= (1<<2); //256 clock
	TCCR0B &=~ (1<<1);
	TCCR0B &=~ (1<<0);
	
	GTCCR &=~ (1<<TSM); //Writing the TSM bit to one activates the Timer/Counter Synchronization mode.
	GTCCR &=~ (1<<PSRASY); // When this bit is one, the Timer/Counter2 prescaler will be reset
	GTCCR &=~ (1<<PSRSYNC); //When this bit is one, Timer/Counter1 and Timer/Counter0 prescaler will be Reset

	TCNT0 = 0x0000; //Counter enable

	//ICR1 = (F_CPU/1024/100) -1; //
	OCR0A = (((F_CPU/256/frequency) -1)*dutyCicle)/100; //
	//OCR0A = 0x00;
	
    while (1) 
    {

    }
}



