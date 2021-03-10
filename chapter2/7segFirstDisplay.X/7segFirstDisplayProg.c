//List any include files you want to use
	#include <conFigInternalOscNoWDTNoLVP.h>
	#include <xc.h>
	#include <PICSetup.h>
	//declare any global variables
	unsigned char n;
	// declare any definitions
	#define zero    0b01000000
	#define one     0b01111001
#define two     0b00100100
#define three   0b00110000
#define four    0b00011001
#define five    0b00010010
#define six     0b00000011
#define seven   0b01111000
#define eight   0b00000000
#define nine    0b00011000
#define startButton PORTAbits.RA0
#define stopButton PORTAbits.RA1
//declare any subroutines
void delay (unsigned char t)
{
for (n = 0; n < t; n++)
{
TMR0 = 0;
while (TMR0 < 255);
}
}
void main ()
{
initialise ();
start: while (! startButton);
while (1)
{ 
if (stopButton) goto start;
PORTB = zero;
delay (61);
PORTB = one;
delay (61);
PORTB = two;
delay (61);
PORTB = three;
delay (61);
PORTB = four;
delay (61);
PORTB = five;
delay (61);
PORTB = six;
delay (61);
PORTB = seven;
delay (61);
PORTB = eight;
delay (61);
PORTB = nine;
}
}

