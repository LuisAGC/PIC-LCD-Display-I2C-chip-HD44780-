
//************************************************************************************ 
// LCD Display test code for "i2c_Flex_LCD" using Phillips PCF8574T 
// By Hugo Silva - Jun 06Th 2015 
// Based in the 20x4 LCD driver test code (by PCM programmer) with a few changes made
// Modified by Moises Reyes to allow print special characters. 
//
// NOTE: This software show how to implement typical routines on LCD I2C display.
//
// Hardware:
// - PIC16F886.
// - LCD Display 16x2 chip HD44780 or compatible.
// - Adapter, parallel to I2C. Chip PCF8574T or compatible.
//************************************************************************************ 
#include <16F886.h>

#fuses NOWDT,NOPROTECT          // To clarified the meaning of this "Configuration´s BITS"
#fuses NOLVP,INTRC              // go to the datasheet and also on MPLAB following the path
#fuses MCLR,NOBROWNOUT          // MPLAB-> Window-> Pic memory views->
#fuses NOIESO,NOFCMEN,DEBUG     // configuration bits

#use delay(clock=8000000)       // Inform to our compiler the clock frequency to be used  (8Mhz)
#define ocho_MHz 0b01110001     // Define the value of OSCCON register. Setting the internal clock 
                                // as source of system clock, running at 8MHz.
/* Setup I2C */
#use I2C(MASTER, sda=PIN_C4, scl=PIN_C3, FAST=2000000) 
#include <i2c_Flex_LCD_MRP_mod.h> 

// Creation of arrangment to save in the bits, which will represent the special char "°"
// To generate this codes, a free online tool was used, in this case was "Custom Character Generator".
// for HD44780 LCD Modules. https://omerk.github.io/lcdchargen/
char simbolo_gr_celcius[8] = {0b01110,0b10001,0b10001,0b01110,0b00000,0b00000,0b00000,0b00000};


void main() { 
#byte OSCCON = ocho_MHz;   // The register OSCCON take the value previously defined.

int i=0; 
lcd_init();
for(i=0;i<3;i++){
	lcd_backlight_led(ON); //Backligth ON 
	delay_ms(1000);
	lcd_backlight_led(OFF); //Backligth ON
	delay_ms(1000);	
} 
lcd_backlight_led(ON); //Backligth ON 
  
 while (TRUE) { 
   lcd_clear();  //Clear Display 
   // Test the clear screen and newline commands. 
   // Also test that we can write to all 4 lines. 
   printf(lcd_putc, "\fThis is the 1st line"); 
   delay_ms(500); 
   printf(lcd_putc, "\nNext is the 2nd line"); 
   delay_ms(500); 
  
   lcd_clear();  //Clear Display 

   // Clear the LCD. 
   printf(lcd_putc, "\f"); 
   delay_ms(500); 

   // Test that lcd_gotoxy() works.  Go to each of 
   // the four corners and put a number in each one, 
   // in a clockwise direction, starting with the upper 
   // left corner. 
   lcd_gotoxy(5, 1);        
   printf(lcd_putc, "Put a Nr. in");    
   lcd_gotoxy(5, 2);        
   printf(lcd_putc, "each corner"); 
   delay_ms(500); 
   lcd_gotoxy(1, 1);        
   printf(lcd_putc, "1"); 
   delay_ms(500); 
   lcd_gotoxy(20, 1);        
   printf(lcd_putc, "2"); 
   delay_ms(500); 
   lcd_gotoxy(20, 2);        
   printf(lcd_putc, "3"); 
   delay_ms(500); 
   lcd_gotoxy(1, 2);        
   printf(lcd_putc, "4");    
   delay_ms(1000); 

   // Type some characters and backspace over them. 
   printf(lcd_putc, "\f\nType characters and\n"); 
   printf(lcd_putc,   "backspace over them."); 
   delay_ms(500); 

   // Go to end of first line.                
   lcd_gotoxy(20, 2);        

   // Backspace over first line. 
   for(i = 0; i < 20; i++) 
      { 
       printf(lcd_putc," \b\b"); 
       delay_ms(50); 
      }

   lcd_clear();  //Clear Display 

   // Clear the LCD. 
   printf(lcd_putc, "\f"); 
   delay_ms(500); 	  
   
// Print the special character, created by show a grad symbol '°', column 8, ROW 2, char to print located in space address CGRAM 5.   
   imprimir_caracter_especial(8, 2, simbolo_gr_celcius, 5);    

//Backligth OFF 
         lcd_backlight_led(OFF); 
         printf(LCD_PUTC,"\fLCD BackLight\n     OFF      "); 
         delay_ms(1000); 

//Backligth ON 
         lcd_backlight_led(ON); 
         printf(LCD_PUTC,"\fLCD BackLight\n     ON      ");  
         delay_ms(1000); 

   }    
} 