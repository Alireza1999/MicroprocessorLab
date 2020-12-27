#include <mega16.h>
#include <alcd.h>

void main(void)
{

    DDRA=0b00000000;
    PORTA=0b00000000;

    lcd_init(20);

    while (1)
     	 {

      	   lcd_gotoxy(0,0);
      	   lcd_putsf("Hello Word");

        }
}
