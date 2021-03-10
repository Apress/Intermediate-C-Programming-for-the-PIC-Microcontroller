/* An improved program to display a count
from 0 to 9 on a seven segment display
Written by H. H. Ward Dated 29/10/19
For the PIC18F4525*/
//List any include files you want to use
#include <conFigInternalOscNoWDTNoLVP.h >
#include <xc.h>
#include <PICSetup.h>
//declare any global variables
unsigned char n,m;
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
unsigned char sevenDisplay [10] =
{
zero,
one,
two,
three,
four,
five,
six,
seven,
eight,
nine,
};
unsigned char *displayPointer;
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
displayPointer = sevenDisplay;
for (m = 0; m <10; m ++ )
{
if (stopButton) goto start;
PORTB = *displayPointer;
displayPointer ++;
delay (61); 
}
}
}
