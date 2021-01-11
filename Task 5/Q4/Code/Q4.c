

#include <mega16.h>
#include <delay.h>

bit flag=0;
int states[4] = {0b00001001 , 0b000001010 , 0b00000110 , 0b00000101};
int currentPosition=0;
int TimerOverFlowCounter =0;
int n=50 ;
int goingFast=1;
int counter;
int delay;
int max_delay;
int min_delay;
int timerStarted;
int direction;

int currentState;
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{

  TCNT0=0x0C;

    if(timerStarted==1) {

        if(counter>=delay) {
            PORTA = states[currentPosition] ;

            if(currentPosition<3) {
                ++currentPosition;
            } else {
                currentPosition=0;
            }

            if(direction<0) {
                if(delay>min_delay) {
                    delay--;
                } else {
                    direction = 1;
                }
            } else {
                if(delay<max_delay) {
                    delay++;
                } else {
                    direction = -1;
                    timerStarted=0;
                }
            }

            counter = 0;
        }

        counter++;
    }


}

void main(void)
{

DDRA=0xff;
PORTA=0x00;

DDRC=0x00;
PINC=0x00;
   currentState = 0;
    timerStarted = 1;
    direction = -1;
    max_delay = 350;
    min_delay = -350;
    delay = max_delay;
    counter = 0;

TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0 = 255;
OCR0=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);
  #asm("sei")
while (1)
      {
        if(PINC.2==0 &&  timerStarted==0) {
                 delay = max_delay;
                 counter = 0;
                 direction = -1;
                 timerStarted=1;
            }
        }
}
