#include <mega16.h>
#include <alcd.h>
#include <stdio.h>
#include <delay.h>

#define ICR1 256 * ICR1H + ICR1L;

unsigned int start;
unsigned int start2;
unsigned int end;

char frequency[16];

unsigned int period;
long freq;

void main(void)
{
    lcd_init(20);
    DDRA =0xFF;
    PORTA = 0x00;

    while(1)
    {
        TCCR1A = 0;
        TCNT1=0;
        TIFR = (1<<ICF1);

        TCCR1B = 0x41;
        while ((TIFR&(1<<ICF1)) == 0);
        start = ICR1;
        TIFR = (1<<ICF1);

        TCCR1B = 0x01;
        while ((TIFR&(1<<ICF1)) == 0);
        start2 = ICR1;
        TIFR = (1<<ICF1);

        TCCR1B = 0x41;
        while ((TIFR&(1<<ICF1)) == 0);
        end = ICR1;
        TIFR = (1<<ICF1);

        TCCR1B = 0;

		if(start < end)
		{
			period = end - start;

			freq= 8000000UL/period;
            sprintf(frequency,"Freq: %d Hz", (int)freq);

            lcd_clear();
			lcd_puts(frequency);
		}else lcd_puts("Waiting...");

        delay_ms(100);
	}
}
