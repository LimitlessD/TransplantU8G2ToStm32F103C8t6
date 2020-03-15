#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
u8g2_t InitNokia5110(void);

int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

int main(void)
{
	 u8 t = 2;
   RCC_Configuration();	//ϵͳʱ�ӳ�ʼ��
   GPIO_Configuration();//�˿ڳ�ʼ��
   USART_Configuration();//SerialPort Init
	 u8g2_t NokiaScrn = InitNokia5110(); //Screen Init
	 
   while(TRUE)
   {
       
		 if(++t > 15)t=2;
		 u8g2_DrawCircle(&NokiaScrn,20,24,t,U8G2_DRAW_ALL);
		 u8g2_DrawCircle(&NokiaScrn,20,24,t-1,U8G2_DRAW_ALL);
		 u8g2_DrawCircle(&NokiaScrn,40,24,t,U8G2_DRAW_ALL);
		 u8g2_DrawCircle(&NokiaScrn,40,24,t-1,U8G2_DRAW_ALL);
		 u8g2_DrawCircle(&NokiaScrn,60,24,t,U8G2_DRAW_ALL);
		 u8g2_DrawCircle(&NokiaScrn,60,24,t-1,U8G2_DRAW_ALL);
     u8g2_SendBuffer(&NokiaScrn);  
		 delay_ms(50);
   }	
}

void RCC_Configuration(void)
{
    SystemInit();//72m
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//Ҫ�ȿ�ʱ�ӣ�����ӳ�䣻����ʾ�ر�jtag��ʹ��swd��  
}

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	//LED
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}


void USART_Configuration(void)
{
  USART_InitTypeDef  USART_InitStructure;

	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;

	USART_Init(USART1,&USART_InitStructure);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_TC);
}




