#include <16F877A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O


#use delay(crystal=4MHz)
#include <lcd.c>


#define LCD_RS_PIN PIN_D7
#define LCD_RW_PIN PIN_D6
#define LCD_ENABLE_PIN PIN_D5
#define LCD_DATA4 PIN_B4
#define LCD_DATA5 PIN_B5
#define LCD_DATA6 PIN_B6
#define LCD_DATA7 PIN_B7

#BIT Data_Pin= 0x08.0
#BIT Data_Pin_Direction = 0x88.0 
            
char message1[] = "Temp = 00.0 C";
char message2[] = "RH   = 00.0 %";
short Time_out;
unsigned int8 T_byte1, T_byte2, RH_byte1, RH_byte2, CheckSum ;


void start_signal(){
  Data_Pin_Direction = 0;              
  Data_Pin = 0;                        
  delay_ms(25);
  Data_Pin = 1;                        
  delay_us(30);
  Data_Pin_Direction = 1;              }

short check_response(){
  delay_us(40);
  if(!Data_Pin){                     
    delay_us(80);
    if(Data_Pin){                    
      delay_us(50);
      return 1;}
 }
}
unsigned int8 Read_Data(){
  unsigned int8 i, k, _data = 0;     
  if(Time_out)
    break;
  for(i = 0; i < 8; i++){
    k = 0;
    while(!Data_Pin){                        
      k++;
      if (k > 100) {Time_out = 1; break;}
      delay_us(1);}
    delay_us(30);
    if(!Data_Pin)
      bit_clear(_data, (7 - i));             
    else{
      bit_set(_data, (7 - i));               
      while(Data_Pin){                       
      k++;
      if (k > 100) {
Time_out = 1; break;
}
      delay_us(1);
} 
}
}
  return _data;
}
void main(){
  lcd_init();                                
  lcd_putc('\f');                            
  while(TRUE){
    delay_ms(1000);
    Time_out = 0;
    Start_signal();
    if(check_response()){                    
      RH_byte1 = Read_Data();                
      RH_byte2 = Read_Data();                 
      T_byte1 = Read_Data();                  
      T_byte2 = Read_Data();                  
      Checksum = Read_Data();                 
      if(Time_out){                           
        lcd_putc('\f');                       
        lcd_gotoxy(5, 1);                     
        lcd_putc("Time out!");  
 }
      else{
       if(CheckSum == ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF)){
        message1[7]  = T_Byte1/10  + 48;
        message1[8]  = T_Byte1%10  + 48;
        message1[10] = T_Byte2/10  + 48;
        message2[7]  = RH_Byte1/10 + 48;
        message2[8]  = RH_Byte1%10 + 48;
        message2[10] = RH_Byte2/10 + 48;
        message1[11] = 223;                   
        lcd_putc('\f');                       
        lcd_gotoxy(1, 1);                     
        printf(lcd_putc, message1);           
        lcd_gotoxy(1, 2);                     
        printf(lcd_putc, message2);      }
        else {
          lcd_putc('\f');                     
          lcd_gotoxy(1, 1);                   
          lcd_putc("Checksum Error!");   } 
 }
 }
    else {
      lcd_putc('\f');             
      lcd_gotoxy(3, 1);           
      lcd_putc("No response");
      lcd_gotoxy(1, 2);           
      lcd_putc("from the sensor");
    }
  }
}
