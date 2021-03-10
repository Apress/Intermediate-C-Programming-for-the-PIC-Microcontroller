/*This is a basic program to control the LCD using the PIC 18F4525
Written by H H Ward dated 31/01/15
Extended 03/01/19 to include the day of the week display*/
#include <xc.h>
#include <conFigInternalOscNoWDTNoLVP.h>
#include <PICSetUp.h>
//some definitions
#define firstbyte     0b00110011
#define secondbyte    0b00110011
#define fourBitOp    	0b00110010  
#define twoLines      0b00101100  
#define incPosition   0b00000110  
#define cursorNoBlink  0b00001100   
#define clearScreen     0b00000001 
#define returnHome      0b00000010  
#define lineTwo         0b11000000  
#define doBlink         0b00001111  
#define shiftLeft       0b00010000  
#define shiftRight      0b00010100  
#define shdisright      0b00011100  
#define lcdPort         PORTB       
#define eBit            PORTBbits.RB5 
#define incbutton       PORTAbits.RA0
#define decbutton       PORTAbits.RA1
#define setbutton       PORTAbits.RA2
#define Mon             lcdData = 0x4D; lcdOut (); 	lcdData = 0x6F; lcdOut (); lcdData = 0x6E; lcdOut 	();
#define Tue             lcdData = 0x54; lcdOut (); 	lcdData = 0x75; lcdOut (); lcdData = 0x65; lcdOut 	();
#define Wed             lcdData = 0x57; lcdOut (); 	lcdData = 0x65; lcdOut (); lcdData = 0x64; lcdOut 	();
#define Thur            lcdData = 0x54; lcdOut (); lcdData = 0x68; lcdOut (); lcdData = 0x72; lcdOut ();
#define Fri             lcdData = 0x46; lcdOut (); 	lcdData = 0x72; lcdOut (); lcdData = 0x69; lcdOut 	();
#define Sat             lcdData = 0x53; lcdOut (); 	lcdData = 0x61; lcdOut (); lcdData = 0x74; lcdOut 	();
#define Sun             lcdData = 0x53; lcdOut (); 	lcdData = 0x75; lcdOut (); lcdData = 0x6E; lcdOut 	();
//some variables
unsigned char n, lcdData, lcdTempData, rsLine, 	daynumber = 1, setbutcounts = 0;
char str[80];
char lcdInitialise [8] =
{
firstbyte,
secondbyte,
fourBitOp,
twoLines,
incPosition,
cursorNoBlink,
clearScreen,
returnHome,
};
//the subroutines
void sendData ()
{
lcdTempData = (lcdTempData << 4 | lcdTempData >>4); 
lcdData = lcdTempData & 0x0F;   
lcdData = lcdData | rsLine;      
lcdPort = lcdData;              
eBit = 1;
eBit = 0;
TMR0 = 0; while (TMR0 < 20);    
}
void lcdOut ()
{
lcdTempData = lcdData;       
sendData ();                       
sendData ();                       
}
void setUpTheLCD ()
{
TMR0 = 0; while (TMR0 <255); 
n = 0;
rsLine = 0X00;                  
while (n < 8)
{
lcdData = lcdInitialise [n];
lcdOut ();
n ++;
}
rsLine = 0x10;              
}
void line2 ()
{
rsLine = 0X00;    
lcdData = lineTwo;
lcdOut ();
rsLine = 0x10;              
}
void clearTheScreen ()
{
rsLine = 0X00;                 
lcdData = clearScreen;
lcdOut ();
//lcdData = returnHome;
//lcdOut ();
rsLine = 0x10;              
}
void sendcursorhome ()
{
rsLine = 0X00;                  
//lcdData = clearScreen;
//lcdOut ();
lcdData = returnHome;
lcdOut ();
rsLine = 0x10;              
}
void shiftcurleft (unsigned char l)
{
for (n = 0; n < l; n ++)
{
rsLine = 0X00;
lcdData = shiftLeft;
lcdOut ();
rsLine = 0x10; 
}             
}
void shiftcurright (unsigned char r)
{
for (n = 0; n < r; n ++)
{
rsLine = 0X00;
lcdData = shdisright;
lcdOut ();
rsLine = 0x10;
}              
}
unsigned char n, secunits = 0X30, sectens = 0X30, minunits = 0X30, mintens = 0X30, hourunits = 0X30, hourtens = 0X30;
void writeString (const char *words)
{
while (*words)              
{
lcdData = *words;       
lcdOut ();              
*words ++;              
}
}
void debounce ()
{
TMR0 = 0;
while (TMR0 < 101);
}
//The main program
void main ()
{
initialise ();
setUpTheLCD ();
clearTheScreen ();
while (1)
{
writeString ("Set The Day");
line2 (); 
while (!setbutton)
{
if (incbutton) debounce ();
if (incbutton) daynumber ++;
while (incbutton);
if (decbutton) debounce ();
if (decbutton) daynumber --;
while (decbutton);
if (daynumber == 1)
{
Mon;
line2 ();
}
if (daynumber == 2)
{
Tue;
line2 ();
}
if (daynumber == 3)
{
Wed;
line2 ();
}
if (daynumber == 4)
{
Thur;
line2 ();
}
if (daynumber == 5)
{
Fri;
line2 ();
}
if (daynumber == 6)
{
Sat;
line2 ();
}
if (daynumber == 7)
{
Sun;
line2 ();
}
if (daynumber == 8) daynumber = 1;
if (daynumber == 0) daynumber = 1;
}
debounce ();
while (setbutton);
clearTheScreen ();
writeString ("Set The Clock");
while (!setbutton)
{
line2 ();
writeString ("Hours"); 
lcdData = 0x3A;
lcdOut ();
lcdData = hourtens;
lcdOut (); 
lcdData = hourunits;
lcdOut (); 
shiftcurleft (1); 
if (incbutton) debounce ();
if (incbutton) hourunits ++;
while (incbutton);
if(hourunits == 0X3A)
{
hourunits = 0X30;
hourtens ++;
}
if (hourtens == 0X32 & hourunits == 0X34 )
{
hourtens = 0x30;
hourunits = 0x30;
}
if (decbutton) debounce ();
if (decbutton)
{
if (hourunits == 0x30)
{
hourunits = 0x39;
hourtens --;               
}
else hourunits --;    
}
while (decbutton);
if (setbutton) debounce ();
if (setbutton) goto minset;
}
minset:   line2 ();       
writeString ("Minutes");
lcdData = 0x3A;
lcdOut ();
for (n = 0; n < 15; n ++)
{
TMR0 = 0;
while (TMR0 < 255);
}            
setmins:  lcdData = mintens;
lcdOut ();
lcdData = minunits;
lcdOut ();
shiftcurleft (2);
if (incbutton) debounce ();
if (incbutton) minunits ++;
while (incbutton)
;
if(minunits == 0X3A)
{
minunits = 0X30;
mintens ++;
} 
if (decbutton) debounce ();
if (decbutton)  
{
if (minunits == 0x30)
{
minunits = 0x39;
mintens --;                
}
else minunits --;
}
while (decbutton);
if (!setbutton) goto setmins;       
clearTheScreen ();
writeString ("The Time/Day is");
lcdData = 0xA0;
lcdOut ();    
while (1) 
{ 
if (daynumber == 1)
{
Mon;
line2 ();
}
if (daynumber == 2) 
{
Tue;
line2 ();
}
if (daynumber == 3)
{
Wed;
line2 ();
}
if (daynumber == 4)
{
Thur;
line2 ();
}
if (daynumber == 5)
{
Fri;
line2 ();
}
if (daynumber == 6)
{
Sat;
line2 ();
}
if (daynumber == 7)
{
Sun;
line2 ();
}
for (n = 0; n < 29; n ++)
{
TMR0 = 0;
while (TMR0 < 255);
}
secunits ++;
if (secunits == 0X3A)
{
secunits = 0X30;
sectens ++;
if ( sectens == 0X36)
{
sectens = 0X30;
minunits ++;
if (minunits == 0X3A)
{
minunits = 0X30;
mintens ++;
if (mintens == 0X36)
{
mintens = 0X30;
hourunits ++;
if(hourunits == 0X3A)
{
hourunits = 0X30;
hourtens ++;
}
}
}
}
if (hourtens == 0X32 & hourunits == 0X34 )
{
hourtens = 0x30;
hourunits= 0x30;
daynumber ++;
if (daynumber == 8) daynumber = 1;
}
}
line2 ();
lcdData = hourtens;
lcdOut ();
lcdData = hourunits;
lcdOut ();
lcdData = 0x3A;
lcdOut ();
lcdData = mintens;
lcdOut ();
lcdData = minunits;
lcdOut ();
lcdData = 0x3A;
lcdOut ();    
lcdData = sectens;
lcdOut ();
lcdData = secunits;
lcdOut ();
lcdData = 0xA0;
lcdOut (); 
}
}
}