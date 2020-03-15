#ifndef __STM32F10X_LCDDISPLAY_H__
#define __STM32F10X_LCDDISPLAY_H__

void LCD_PortInit(void);
void LCD_WriteByte(unsigned char dat);
void LCD_WriteCom(unsigned char com);
void LCD_WriteData(unsigned char dat);
void LCD_Init(void);
void LCD_ClearScreen(void);
void LCD_WriteString(unsigned char y,unsigned char x,char *s);
void LCD_WriteImage(unsigned char *p);

#endif
