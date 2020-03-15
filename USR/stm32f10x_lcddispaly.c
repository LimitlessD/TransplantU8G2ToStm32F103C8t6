#include "pbdata.h"

#define CLR_RS GPIO_ResetBits(GPIOB, GPIO_Pin_13)
#define SET_RS GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define CLR_RW GPIO_ResetBits(GPIOB, GPIO_Pin_14)
#define SET_RW GPIO_SetBits(GPIOB, GPIO_Pin_14)
#define CLR_EN GPIO_ResetBits(GPIOB, GPIO_Pin_15)
#define SET_EN GPIO_SetBits(GPIOB, GPIO_Pin_15)

/****************************************************************
函数名称：LCD_PortInit
函数功能：初始化LCD端口
入口参数：void
出口参数：void
备 注：

*****************************************************************/
void LCD_PortInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
/****************************************************************
函数名称：LCD_WriteByte
函数功能：串行方式向12864写入一字节数据
入口参数：dat  8bit
出口参数：无
备 注：
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
*****************************************************************/
void LCD_WriteByte(u8 dat)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		CLR_EN;		   
		delay_us(30);
		if(dat & 0x0080)
		  SET_RW;
		else
			CLR_RW;
		SET_EN;
		delay_us(30);
		CLR_EN;
		delay_us(30);
		dat = dat << 1;
	}
}

/****************************************************************
函数名称：LCD_WriteCom
函数功能：向12864写入命令
入口参数：com  
出口参数：无
备 注：

*****************************************************************/
void LCD_WriteCom(u8 com)
{
	SET_RS;
	LCD_WriteByte(0xf8);
	LCD_WriteByte(com & 0xf0);
	LCD_WriteByte(0xf0 & com << 4); //先执行<<
	CLR_RS;
}

/****************************************************************
函数名称：LCD_WriteData
函数功能：向12864写入数据
入口参数：dat
出口参数：无
备 注：

*****************************************************************/
void LCD_WriteData(u8 dat)
{
	SET_RS;
	LCD_WriteByte(0xfa);
	LCD_WriteByte(dat&0xf0);
	LCD_WriteByte(0xf0&dat<<4);
	CLR_RS;
}


/****************************************************************
函数名称：Init_LCD
函数功能：初始化12864液晶
入口参数：无
出口参数：无
备 注：严格按照资料给的初始化流程编写

*****************************************************************/
void LCD_Init()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
  delay_us(5000);
  LCD_WriteCom(0x30);   //功能设定指令，表示为基本指令
  delay_us(5000);
  LCD_WriteCom(0x02);
  delay_us(5000);
  LCD_WriteCom(0x0c);	//显示状态指令，表示不显示游标
  delay_us(5000);
  LCD_WriteCom(0x01);  //清楚显示
  delay_us(5000);
  LCD_WriteCom(0x06);   //进入点设定，这条指令貌似只有0x06的时候才能正常显示
}

/****************************************************************
函数名称：Clear_Screen
函数功能：清楚屏幕
入口参数：无
出口参数：无
备 注：

*****************************************************************/
void LCD_ClearScreen()
{
	LCD_WriteCom(0x01);
	delay_us(6000);
}

/****************************************************************
函数名称：LCD_Write_String
函数功能：向12864写入字符串
入口参数：x~(0-7),y~(0-3)---设定第一个字符的坐标
		*s ----需要显示的字符串
出口参数：无
备 注：
*****************************************************************/
void LCD_WriteString(u8 y,u8 x,char *s)
{
	switch(y)
	{
		case 0:LCD_WriteCom(0x80 + x);break;
		case 1:LCD_WriteCom(0x90 + x);break;
		case 2:LCD_WriteCom(0x88 + x);break;
		case 3:LCD_WriteCom(0x98 + x);break;
		default:break;
	}
	while(*s)
	{
		LCD_WriteData(*s);
		s++;
	}
}
/****************************************************************
函数名称：LCD_WriteImage
函数功能：向12864写纫一副图片
入口参数：*s ----需要显示的图片数据
出口参数：无
备 注：
*****************************************************************/
void LCD_WriteImage(u8 *p)
{
	u8 i, j, k;
	u8 x, y ;
	x = 0x80;
	y = 0x80;
	LCD_WriteCom(0x34);
	for(i = 0; i < 2; i ++)
	{
		for(j = 0; j < 32; j ++)
		{
			LCD_WriteCom(y + j);
			LCD_WriteCom(x);
			for(k = 0; k<16; k ++)
			{
				LCD_WriteData(*p ++);
			}
		}
		x = 0x88;
	}
	LCD_WriteCom(0x36);
	LCD_WriteCom(0x30);
}

