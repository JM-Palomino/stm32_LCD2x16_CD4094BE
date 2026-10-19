#ifndef __LCD_2x16_CD4094BE_lcd_H
#define __LCD_2x16_CD4094BE_lcd_H

#define CLK     GPIO_PIN_5
#define Serial_DATA  GPIO_PIN_4


#define _LCD_FIRST_ROW          0x80         //Move cursor to the 1st row
#define _LCD_SECOND_ROW         0xC0         //Move cursor to the 2nd row
#define _LCD_THIRD_ROW          0x94         //Move cursor to the 3rd row
#define _LCD_FOURTH_ROW         0xD4         //Move cursor to the 4th row
#define _LCD_CLEAR              0x01         //Clear display
#define _LCD_RETURN_HOME        0x02         //Return cursor to home position, returns a shifted display to
                                                 //its original position. Display data RAM is unaffected.
#define _LCD_CURSOR_OFF         0x0C         //Turn off cursor
#define _LCD_UNDERLINE_ON       0x0E         //Underline cursor on
#define _LCD_BLINK_CURSOR_ON    0x0F          //Blink cursor on
#define _LCD_MOVE_CURSOR_LEFT   0x10          //Move cursor left without changing display data RAM
#define _LCD_MOVE_CURSOR_RIGHT  0x14           //Move cursor right without changing display data RAM
#define _LCD_TURN_ON            0x0C         //Turn Lcd display on
#define _LCD_TURN_OFF           0x08         //Turn Lcd display off
#define _LCD_SHIFT_LEFT         0x18         //Shift display left without changing display data RAM
#define _LCD_SHIFT_RIGHT        0x1E         //Shift display right without changing display data RAM

  //Function Prototypes
void Serial_LCD_Init(void);
void Serial_LCD_Cmd(unsigned char Command);
void Serial_LCD_Chr(unsigned char row, unsigned char col, char LCDChar);
void Serial_LCD_Out(char row, char y, char *str);
void WriteNibble(unsigned char);
#endif
