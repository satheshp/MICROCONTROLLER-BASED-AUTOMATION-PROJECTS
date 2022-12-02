#include <16F877A.h>
#device ADC=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=20MHz)

#define LCD_ENABLE_PIN PIN_D5
#define LCD_RS_PIN PIN_D7
#define LCD_RW_PIN PIN_D6
#define LCD_DATA4 PIN_B4
#define LCD_DATA5 PIN_B5
#define LCD_DATA6 PIN_B6
#define LCD_DATA7 PIN_B7

#include <lcd.c>

void main()                    //LM CHARACTERISTIC 10mv/c
{     long int adcResult =0;
       float voltage = 0;
       float temp =0;
       
      setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0);
   set_adc_channel(0);  
   lcd_init();
   lcd_putc('\f');
   
   while(TRUE)
   {  
       lcd_gotoxy(1,1);
      printf(lcd_putc,"Temp:");
      lcd_gotoxy(10,1);
    // printf(lcd_putc,"temperature");
      adcResult = read_adc();
      //lcd_gotoxy(1,2);
      //printf(lcd_putc,"%ld",adcResult);
      //lcd_gotoxy(10,2);
      voltage = (float)(adcResult * 5)/1023;
      temp = voltage / 0.01;
      printf(lcd_putc,"%f",temp);
      if(temp>30){
      lcd_gotoxy(1,2);
      printf(lcd_putc,"   TEMP  HIGH");
      output_high(PIN_D0);
      delay_ms(500);
      output_low(PIN_D0);
      delay_ms(500);
      }
      else{
      output_low(PIN_D0);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"TEMP NOT HIGH");
      }
      
      
      
      delay_ms(500);
   }

}

