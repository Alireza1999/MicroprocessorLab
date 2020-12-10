/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Q2
Version :
Date    : 2020-12-10
Author  : Alireza Soleymani
Company :
Comments:


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>

// Declare your global variables here
       int TimerOverflowCounter=0 ;
       int  n =0;
       int  NUMBER  =0b00000001;
       int state=0;


// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{

    TCNT0=0x6;
    ++TimerOverflowCounter;

    if(TimerOverflowCounter ==250){
     TimerOverflowCounter =0;
        if(n==1){

          if(state ==1){

             NUMBER = NUMBER >>1;
             PORTB = PORTB & NUMBER;
             PORTB = PORTB | NUMBER ;

          }else{

             if(NUMBER == 128){
                PORTB = PORTB & NUMBER;
                PORTB = PORTB | NUMBER;
                state =1;

             }else{

             PORTB = PORTB & NUMBER;
             PORTB = PORTB | NUMBER;
             NUMBER = NUMBER <<1;

             }



          }
     }
    }



}

void main(void)
{

DDRA=0b00000000;
PORTA=0b00000000;


DDRB=0b11111111;
PORTB=0b00000000;


TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (1<<CS01) | (1<<CS00);
TCNT0=6;
OCR0=0x00;



// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);


#asm("sei")

while (1)
      {


          if(state ==1 && PORTB==0){
           PORTB = 0x00;
           n=0;
           state=0;
           NUMBER =0b00000001;
          }

           if(PINA.0 == 1){

            n=1;
          }
      }
}
