#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include <bmp180.h>
#include <i2c.h>
#include "bmp180.c"

void show(int n){
	int i,x;
	 i=1;
	 x=0;
	 
	 if(n%10==0 && i==1)
	 {
		 zero();
		 PORTD= 0b00000100;
		  _delay_ms(5);
		 }
	 else if(n%10==1 && i==1)
	 {
		 one();
		 PORTD= 0b00000100;
		  _delay_ms(5);
		 }
	 else if(n%10==2 && i==1)
	 {
		 two();
		 PORTD= 0b00000100;
		  _delay_ms(5);
	 }

	 else if(n%10==3 && i==1)
	 {
		 three();
		 PORTD= 0b00000100;
		  _delay_ms(5);
	 }
	 else if(n%10==4 && i==1)
	 {
		 four();
		 PORTD= 0b00000100;
		 _delay_ms(5);	 	 
	}
	 else if(n%10==5 && i==1)
	 {
		 five();
		 PORTD= 0b00000100;
		  _delay_ms(5);
	 }
	 else if(n%10==6 && i==1)
	 {
		 six();
		 PORTD= 0b00000100;
		  _delay_ms(5);
	 }
	 else if(n%10==7 && i==1)
	 {
		 seven();
		 PORTD= 0b00000100;
		  _delay_ms(5);
	 }
	 else if(n%10==8 && i==1)
	 {
		 eight();
		 PORTD= 0b00000100;
		  _delay_ms(5);
		 }
	 else if(n%10==9 && i==1)
	 {
		 nine();
		 PORTD= 0b00000100;
		 _delay_ms(5);
	 }
	 
	 i=0;
	 x=1;
	 
	 n /= 10;
	 
	 if(n%10==0 && x==1)
	 {
		 zero();
		 PORTD= 0b00010000;
		 _delay_ms(5);
	 }
	 else if(n%10==1 && x==1)
	 {
		 one();
		 PORTD= 0b00010000;
		 _delay_ms(5);
	 }
	 
	 else if(n%10==2 && x==1)
	 {
		 two();
		 PORTD= 0b00010000;
		 _delay_ms(5);
	 }
	 else if(n%10==3 && x==1)
	 {
		 three();
		 PORTD= 0b00010000;
		 _delay_ms(5);
	 }
	 else if(n%10==4 && x==1)
	 {
		 four();
		 PORTD= 0b00010000;
		 _delay_ms(5);
	 }
	 else if(n%10==5 && x==1)
	 {
		 five();
		 PORTD= 0b00010000;
		 _delay_ms(5);
	 }
	 else if(n%10==6 && x==1)
	 {
		 six();
		 PORTD= 0b00010000;
		 _delay_ms(5);
	 }
	 else if(n%10==7 && x==1)
	 {
		 seven();
		 PORTD= 0b00010000;
		 _delay_ms(5);
	 }
	 else if(n%10==8 && x==1)
	 {
		 eight();
		 PORTD= 0b00010000;
		 _delay_ms(5);
	 }
	 else if(n%10==9 && x==1)
	 {
		 nine();
		 PORTD= 0b00010000;
		 _delay_ms(5);
	 } // end_if

}

void USART_init()
{
	UBRRH = 51>>8;
	UBRRL = 51;
	UCSRB = 0b00011000;
	UCSRC = 0b10000110;     //no parity
}

void USART_transmit(long data)
{
	while( !(UCSRA & (1<<UDRE)) );
	UDR = data;
}

void one()
{
	PORTA=0b10010000;
}
void two()
{
	PORTA=0b01111010;
}
void three()
{
	PORTA=0b11011010;
}
void four()
{
	PORTA=0b10010110;
}
void five()
{
	PORTA=0b11001110;
}
void six()
{
	PORTA=0b11101110;
}

void seven()
{
	PORTA=0b10011000;
}
void eight()
{
	PORTA=0b11111110;
}
void nine()
{
	PORTA=0b11011110;
}
void zero()
{
	PORTA=0b11111100;
}

int main(void)
{
	DDRA = 0xFF;
	DDRD = 0b00010100;
	USART_transmit(22);
	long temp;
	
	init_twi();
	show(11);			// for checking that Initialization started
	init_sensor(1);
	show(00);		// for checking that Initialization is Done !!
	
		USART_init(51);		// setting up the Baud Rate for USART
	
	PORTA = 0xFF;
	_delay_ms(1000);
	PORTA = 0x00;
	_delay_ms(40);
	
		
    while (1) 
    {	
		temp = calculate_temperature();
		
		temp /= 10 ;
		
		 int n = (int) temp;
		 
		//USART_transmit(temp);
		
		show(temp);
		
		_delay_ms(2);
    } // end_while
	
} //end_main

