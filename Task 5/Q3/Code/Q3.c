

#include <mega16.h>
#include <delay.h>

bit flag=0;
int states[4] = {0b00001001 , 0b000001010 , 0b00000110 , 0b00000101};
int currentPosition=0;
int TimerOverFlowCounter =0;
 int direction;

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{


          TCNT0=6;

    PORTA = states[currentPosition];

    if(direction>0) {
        if(currentPosition<3) {
            ++currentPosition;
        } else {
            currentPosition=0;
        }
    } else {
        if(currentPosition>0) {
            --currentPosition;
        } else {
            currentPosition=3;
        }
    }


}

void main(void)
{


    currentPosition = 0;
    direction = 1;

DDRA=0xff;
PORTA=0x00;

DDRC=0x00;
PORTC=0x00;


TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (1<<CS01) | (1<<CS00);
TCNT0=0x00;
OCR0=0x00;

TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);


#asm("sei")

while (1)
      {
          if(PINC.2==0) {
            direction =1;

        }else{
            direction =-1;
        }

      }
}
