#include <conFigInternalOscNoWDTNoLVP.h>
#include <xc.h>
//Some definitions
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
#define incButton PORTEbits.RE0
#define decButton PORTEbits.RE1
#define setButton PORTEbits.RE2
//some variables
unsigned char n, m;
unsigned char minUnits = 0, minTens = 0, hourUnits = 0, hourTens = 0;
//some subroutines
void initialise ()
{
PORTA = 0;
PORTB = 0;
PORTC = 0;
PORTD = 0;
PORTE = 0;
TRISA = 0X00;
TRISB = 0x00;
TRISC = 0x00;
TRISD = 0x00;
TRISE = 0x03;
ADCON0 = 0x00;          
ADCON1 = 0x0F;          
OSCTUNE = 0b00000000;   
OSCCON = 0b01110000;    
T0CON = 0b11000111;
}
void debounce ()
{
TMR0 = 0;
while (TMR0 < 101);
}
//some arrays
unsigned char displaynumber [10] =
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
void main ()
{
initialise ();
//set minutes
minunitsset:	
PORTA = displaynumber [minUnits];
if (incButton)debounce ();
if (incButton)
{
minUnits ++;
while (incButton);
PORTA = displaynumber [minUnits];
}
if (decButton )debounce ();
if (decButton)
{
if (minUnits > 0) minUnits --;
else minUnits = 0;
while (decButton);
PORTA = displaynumber [minUnits];
}
if (setButton) debounce ();
if (setButton) goto mintensset;
goto minunitsset;
//**************************************************
mintensset:	while (setButton);
PORTB = displaynumber [minTens];
if (incButton)debounce ();
if (incButton)
{
if (minTens < 6)
minTens ++;
else minTens = 6;
while (incButton);
PORTB = displaynumber [minTens];
}
if (decButton)debounce ();
if (decButton)
{
if (minTens > 0)
minTens --;
else minTens = 0;
while (decButton);
PORTB = displaynumber [minTens];
}
if (setButton) debounce ();
if (setButton) goto hoursunitsset;
goto mintensset;
//sethours
hoursunitsset: while (setButton);
PORTC = displaynumber [hourUnits];	
if (incButton)debounce ();
if (incButton)
{
hourUnits ++;
while (incButton);
PORTC = displaynumber [hourUnits];
}
if (decButton)debounce ();
if (decButton)
{
if (hourUnits > 0)
hourUnits --;
else hourUnits = 0;
while (decButton);
PORTC = displaynumber [hourUnits];
}
if (setButton) debounce ();
if (setButton) goto hourstensset;
goto hoursunitsset;
//**************************************************
hourstensset:	while (setButton);
PORTD = displaynumber [hourTens];
if (incButton)debounce ();
if (incButton)
{
if (hourTens < 2)
hourTens ++;
else hourTens = 2;
while (incButton);
PORTD = displaynumber [hourTens];
}
if (decButton)debounce ();
if (decButton)
{
if (hourTens > 0)
hourTens --;
else hourTens = 0;
while (decButton);
PORTD = displaynumber [hourTens];
}
if (setButton) debounce ();
if (setButton) goto clock;
goto hourstensset;
//*************************************************
clock:		while (1)
{
for (m = 0; m <60; m++)
{
for (n = 0; n <29; n++)
{
TMR0 = 0;
while (TMR0 < 255);
}
}
minUnits ++;
if (minUnits == 10)
{
minUnits = 0;
minTens ++;
if (minTens == 6)
{
minTens = 0;
hourUnits ++;
if (hourTens < 2)
{
if (hourUnits == 10)
{
hourUnits = 0;
hourTens ++;
}
}
else if (hourTens == 2)
{
if (hourUnits == 4)
{
hourUnits = 0;
hourTens =0;
}
}
}
}
PORTA = displaynumber [minUnits];
PORTB = displaynumber [minTens];
PORTC = displaynumber [hourUnits];
PORTD = displaynumber [hourTens];
}
}
