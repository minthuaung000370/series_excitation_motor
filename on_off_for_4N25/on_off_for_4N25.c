/*
 * on_off_for_4N25.c
 *
 * Created: 4/24/2018 3:51:05 PM
 *  Author: minthuaung
 */ 

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void my_delay_ms(int n);

int main(void)
{
	DDRA = 0;	    //ADC read channel 0
	DDRB = (1<<0); //PORTB.0 output for signal
	DDRD = (0<<2); //PORTD.2 normally low
	PORTD= (0<<2); //PORTD.2 normally low, & waiting for input
	GICR = (1<<INT0); //INT0 externally interrupt
	MCUCR= (1<<ISC01) | (0<<ISC00); // rising edge of INT0	
	ADCSRA = 0x87; //0b10000111,,, ADC enable, prescaler 128
	ADMUX  = 0x40; //REFS0 = 1 & REFS1 = 0 AVCC same as VCC
	
	sei();
	
    while(1)
    {
	}
}

ISR(INT0_vect)
{
	//TODO:: Please write your application code
	int delay_adc;
	ADCSRA |= (1<<ADSC);
	while((ADCSRA & (1<<ADIF)) == 0);
	delay_adc = ADC / 100;
	my_delay_ms(delay_adc);
	PORTB = (1<<0);
	my_delay_ms(10 - delay_adc);
	PORTB = (0<<0);
}

void my_delay_ms(int n)
{
	while(n--)
	{
		_delay_ms(1);
	}
}