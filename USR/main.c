#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
u8g2_t InitNokia5110(void);


int main(void)
{
	 u8 t = 2;
   RCC_Configuration();	//系统时钟初始化
   GPIO_Configuration();//端口初始化
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
