#include "pbdata.h"

#define CLR_RS GPIO_ResetBits(GPIOB, GPIO_Pin_13)
#define SET_RS GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define CLR_RW GPIO_ResetBits(GPIOB, GPIO_Pin_14)
#define SET_RW GPIO_SetBits(GPIOB, GPIO_Pin_14)
#define CLR_EN GPIO_ResetBits(GPIOB, GPIO_Pin_15)
#define SET_EN GPIO_SetBits(GPIOB, GPIO_Pin_15)

/****************************************************************
�������ƣ�LCD_PortInit
�������ܣ���ʼ��LCD�˿�
��ڲ�����void
���ڲ�����void
�� ע��

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
�������ƣ�LCD_WriteByte
�������ܣ����з�ʽ��12864д��һ�ֽ�����
��ڲ�����dat  8bit
���ڲ�������
�� ע��
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
�������ƣ�LCD_WriteCom
�������ܣ���12864д������
��ڲ�����com  
���ڲ�������
�� ע��

*****************************************************************/
void LCD_WriteCom(u8 com)
{
	SET_RS;
	LCD_WriteByte(0xf8);
	LCD_WriteByte(com & 0xf0);
	LCD_WriteByte(0xf0 & com << 4); //��ִ��<<
	CLR_RS;
}

/****************************************************************
�������ƣ�LCD_WriteData
�������ܣ���12864д������
��ڲ�����dat
���ڲ�������
�� ע��

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
�������ƣ�Init_LCD
�������ܣ���ʼ��12864Һ��
��ڲ�������
���ڲ�������
�� ע���ϸ������ϸ��ĳ�ʼ�����̱�д

*****************************************************************/
void LCD_Init()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
  delay_us(5000);
  LCD_WriteCom(0x30);   //�����趨ָ���ʾΪ����ָ��
  delay_us(5000);
  LCD_WriteCom(0x02);
  delay_us(5000);
  LCD_WriteCom(0x0c);	//��ʾ״ָ̬���ʾ����ʾ�α�
  delay_us(5000);
  LCD_WriteCom(0x01);  //�����ʾ
  delay_us(5000);
  LCD_WriteCom(0x06);   //������趨������ָ��ò��ֻ��0x06��ʱ�����������ʾ
}

/****************************************************************
�������ƣ�Clear_Screen
�������ܣ������Ļ
��ڲ�������
���ڲ�������
�� ע��

*****************************************************************/
void LCD_ClearScreen()
{
	LCD_WriteCom(0x01);
	delay_us(6000);
}

/****************************************************************
�������ƣ�LCD_Write_String
�������ܣ���12864д���ַ���
��ڲ�����x~(0-7),y~(0-3)---�趨��һ���ַ�������
		*s ----��Ҫ��ʾ���ַ���
���ڲ�������
�� ע��
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
�������ƣ�LCD_WriteImage
�������ܣ���12864д��һ��ͼƬ
��ڲ�����*s ----��Ҫ��ʾ��ͼƬ����
���ڲ�������
�� ע��
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

