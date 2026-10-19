

#include "LCD_2x16_CD4094BE.h"
#include "tim.h"
#include "gpio.h"

unsigned char rs;
  void Serial_LCD_Cmd(unsigned char Command)
{
      rs=0; //because sending command
      WriteNibble(Command>>4);
      WriteNibble(Command & 0x0F);

      if((Command == 0x0C) || (Command == 0x01) || (Command == 0x0E) || (Command == 0x0F) || (Command == 0x10)
                   || (Command == 0x1E) || (Command == 0x18) || (Command == 0x08) || (Command == 0x14)
                   || (Command == 0x02))
      HAL_Delay(50);
}

void Serial_LCD_Chr(unsigned char row, unsigned char col, char LCDChar)
{
        switch(row){

                case 1:
                Serial_LCD_Cmd(0x80 + col-1);
                break;
                case 2:
                Serial_LCD_Cmd(0xC0 + col-1);
                break;
                case 3:
                Serial_LCD_Cmd(0x94 + col-1);
                break;
                case 4:
                Serial_LCD_Cmd(0xD4 + col-1);
                break;
        }

        rs=1;                         //because sending Serial_DATA
        WriteNibble(LCDChar >> 4);
        delay_us(10);
        WriteNibble(LCDChar & 0x0F);

}

void Serial_LCD_Out(char row, char y, char *str){
    switch(row){
    case 1:
      Serial_LCD_Cmd(0x80 + y-1);
      break;
    case 2:
       Serial_LCD_Cmd(0xC0 + y-1);
      break;
    case 3:
       Serial_LCD_Cmd(0x94 + y-1);
      break;
    case 4:
       Serial_LCD_Cmd(0xD4 + y-1);
    break;
  }

  while(*str)              // Write data to LCD up to null
 {
   rs=1;                         //because sending Serial_DATA
   WriteNibble(*str >> 4);
   delay_us(10);
   WriteNibble(*str & 0x0F);
     str++;               // Increment buffer
  }
}

void WriteNibble(unsigned char d)
{
          unsigned char i;
           HAL_GPIO_WritePin(GPIOA, CLK|Serial_DATA, GPIO_PIN_RESET);

          //CLK = 0;
          //Serial_DATA= 0;
          for(i=0;i<8;i++)
                  {
                HAL_GPIO_WritePin(GPIOA, CLK, GPIO_PIN_SET);  // CLK = 1;
                  delay_us(10);
                 HAL_GPIO_WritePin(GPIOA, CLK, GPIO_PIN_RESET);// CLK = 0;
                  delay_us(10);
                  }

          //Serial_DATA = 1;                                        //set Q7= 1 for E
          //CLK =1;
				  HAL_GPIO_WritePin(GPIOA, CLK|Serial_DATA, GPIO_PIN_SET);				
          delay_us(10);
          HAL_GPIO_WritePin(GPIOA, CLK, GPIO_PIN_RESET);//CLK=0;
          delay_us(10);

         // Serial_DATA = rs;  									//set Q6 for RS
				  if(rs==1) HAL_GPIO_WritePin(GPIOA, Serial_DATA, GPIO_PIN_SET);	
					else HAL_GPIO_WritePin(GPIOA, Serial_DATA, GPIO_PIN_RESET);	
									
          HAL_GPIO_WritePin(GPIOA, CLK, GPIO_PIN_SET);  // CLK = 1;
          delay_us(10);
          HAL_GPIO_WritePin(GPIOA, CLK, GPIO_PIN_RESET);// CLK = 0;
          delay_us(10);

                  for ( i=8;i>0;i=i>>1)
                  {
                          if(d & i)
                                  {
                                         HAL_GPIO_WritePin(GPIOA, Serial_DATA, GPIO_PIN_SET);	
                                  }
                                  else
                                  {
                                         HAL_GPIO_WritePin(GPIOA, Serial_DATA, GPIO_PIN_RESET);	
                                  }
                          HAL_GPIO_WritePin(GPIOA, CLK, GPIO_PIN_SET);  // CLK = 1;
                          delay_us(10);
                          HAL_GPIO_WritePin(GPIOA, CLK, GPIO_PIN_RESET);// CLK = 0;
                          delay_us(10);
                  }

          HAL_GPIO_WritePin(GPIOA, Serial_DATA, GPIO_PIN_RESET);	//Serial_DATA=0;
          delay_us(10);                        //shift Q0
          HAL_GPIO_WritePin(GPIOA, CLK, GPIO_PIN_SET); 
          delay_us(10);
          HAL_GPIO_WritePin(GPIOA, CLK, GPIO_PIN_RESET);


          HAL_GPIO_WritePin(GPIOA, Serial_DATA, GPIO_PIN_SET);	
          delay_us(10);                //now send enable
          HAL_GPIO_WritePin(GPIOA, Serial_DATA, GPIO_PIN_RESET);
          delay_us(10);
}

void Serial_LCD_Init(){
          rs=0;
          HAL_Delay(40);
          //WriteNibble(0x03);
          Serial_LCD_Cmd(0x03);
          HAL_Delay(5);
          //WriteNibble(0x03);
          Serial_LCD_Cmd(0x03);
          HAL_Delay(5);
          //WriteNibble(0x03);
          Serial_LCD_Cmd(0x03);
          HAL_Delay(2);
          //WriteNibble(0x02);
          Serial_LCD_Cmd(0x02);

          Serial_LCD_Cmd(0x28);   //set Serial_DATA length 4 bit 2 line
          HAL_Delay(50);
          Serial_LCD_Cmd(0x0C);   // set display on cursor oFF blink off to on the cursor E to and on the blink F
          HAL_Delay(50);
          Serial_LCD_Cmd(0x06);  // cursor shift direction
          HAL_Delay(50);
          Serial_LCD_Cmd(0x0C);
          HAL_Delay(50);
}
