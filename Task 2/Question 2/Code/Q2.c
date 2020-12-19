
#include <mega16.h>
#include <delay.h>

int temp;
int SevenSegNumber[10] = {0b00111111 , 0b00000110 , 0b01011011 , 0b01001111 , 0b01100110 , 0b01101101 , 0b01111101 , 0b00000111 ,0b01111111 ,0b01101111};

int Timer0OverFlowCounter =0;
int Timer1OverFlowCounter =0;
int SevenSegCounter[4] = {0,0,0,0};
int i =3;
int lastSevenSeg=3;

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{


   ++Timer0OverFlowCounter;
    if(Timer0OverFlowCounter ==2){
           temp = PORTC ^ 0b11111111;
           PORTC= temp ^ 0b11111111;
           PORTD = SevenSegNumber[SevenSegCounter[lastSevenSeg]];
           temp = temp >>1;
           if(temp ==0){
           temp = 8;
           }
           temp = temp ^ 0b11111111;
           PORTC = temp;
           temp = temp ^ 0b11111111;

              Timer0OverFlowCounter=0;
             lastSevenSeg--;
             if(lastSevenSeg == -1 ){
             lastSevenSeg = 3;
             }
    }


       TCNT0=0x00;

}

// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{

    ++Timer1OverFlowCounter;
    if(Timer1OverFlowCounter ==500){

         SevenSegCounter[3]++;

         while (i>=0){

            if( SevenSegCounter[i] ==10){

            SevenSegCounter[i-1]++;
            SevenSegCounter[i]=0;

            }
             i--;
         }


                   i=3;
             Timer1OverFlowCounter=0;

    }


        TCNT1H=0xFF;
        TCNT1L=0xF0;

}



void main(void)
{



DDRD=0b11111111;
PORTD=0b00000000;
DDRC=0b11111111;
PORTC=0b11101111;
 // 0b00001000 = 8 decimal





// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);


// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 8000.000 kHz
// Mode: Normal top=0xFF
// OC0 output: Disconnected
// Timer Period: 0.032 ms
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0x00;
OCR0=0x00;



// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 8000.000 kHz
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 8.192 ms
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H=0xFF;
TCNT1L=0xF0;



// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);

#asm("sei")
while (1)
      {




      }
}
