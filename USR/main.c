#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);

uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr);

int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

int main(void)
{
	 u8 t = 2;
   RCC_Configuration();	//系统时钟初始化
   GPIO_Configuration();//端口初始化
   USART_Configuration();
	 u8g2_t u8g2; // a structure which will contain all the data for one display
   u8g2_Setup_pcd8544_84x48_f(&u8g2, U8G2_R0, u8x8_byte_4wire_sw_spi, u8x8_stm32_gpio_and_delay);  // init u8g2 structure
   u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,
   u8g2_SetPowerSave(&u8g2, 0); // wake up display
	 
   while(1)
   {
     u8g2_ClearBuffer(&u8g2);  
		 if(++t > 15)t=2;
		 u8g2_DrawCircle(&u8g2,20,24,t,U8G2_DRAW_ALL);
		 u8g2_DrawCircle(&u8g2,20,24,t-1,U8G2_DRAW_ALL);
		 u8g2_DrawCircle(&u8g2,40,24,t,U8G2_DRAW_ALL);
		 u8g2_DrawCircle(&u8g2,40,24,t-1,U8G2_DRAW_ALL);
		 u8g2_DrawCircle(&u8g2,60,24,t,U8G2_DRAW_ALL);
		 u8g2_DrawCircle(&u8g2,60,24,t-1,U8G2_DRAW_ALL);
     u8g2_SendBuffer(&u8g2);  
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
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//要先开时钟，再重映射；这句表示关闭jtag，使能swd。  
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

uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  switch(msg)
  {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:	// called once during init phase of u8g2/u8x8
      break;							// can be used to setup pins
    case U8X8_MSG_DELAY_NANO:			// delay arg_int * 1 nano second
			delay_us(1);
      break;    
    case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
			delay_us(100);
      break;
    case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
			delay_ms(10);
      break;
    case U8X8_MSG_DELAY_MILLI:			// delay arg_int * 1 milli second
			__NOP();
      break;
    case U8X8_MSG_DELAY_I2C:				// arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
      break;							// arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
    case U8X8_MSG_GPIO_D0:				// D0 or SPI clock pin: Output level in arg_int
    //case U8X8_MSG_GPIO_SPI_CLOCK:
		if(arg_int){
				GPIO_SetBits(GPIOB, GPIO_Pin_3);
			}else{
				GPIO_ResetBits(GPIOB, GPIO_Pin_3);
			}
      break;
    case U8X8_MSG_GPIO_D1:				// D1 or SPI data pin: Output level in arg_int
    //case U8X8_MSG_GPIO_SPI_DATA:
		if(arg_int){
				GPIO_SetBits(GPIOB, GPIO_Pin_4);
			}else{
				GPIO_ResetBits(GPIOB, GPIO_Pin_4);
			}
      break;
    case U8X8_MSG_GPIO_D2:				// D2 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D3:				// D3 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D4:				// D4 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D5:				// D5 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D6:				// D6 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D7:				// D7 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_E:				// E/WR pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
			if(arg_int){
				GPIO_SetBits(GPIOB, GPIO_Pin_6);
			}else{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			}
      break;
    case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
			if(arg_int){
				GPIO_SetBits(GPIOB, GPIO_Pin_5);
			}else{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);
			}
      break;
    case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
			if(arg_int){
				GPIO_SetBits(GPIOB, GPIO_Pin_7);
			}else{
				GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			}
      break;
    case U8X8_MSG_GPIO_CS1:				// CS1 (chip select) pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_CS2:				// CS2 (chip select) pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_I2C_CLOCK:		// arg_int=0: Output low at I2C clock pin
      break;							// arg_int=1: Input dir with pullup high for I2C clock pin
    case U8X8_MSG_GPIO_I2C_DATA:			// arg_int=0: Output low at I2C data pin
      break;							// arg_int=1: Input dir with pullup high for I2C data pin
    case U8X8_MSG_GPIO_MENU_SELECT:
      u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
      break;
    case U8X8_MSG_GPIO_MENU_NEXT:
      u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
      break;
    case U8X8_MSG_GPIO_MENU_PREV:
      u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
      break;
    case U8X8_MSG_GPIO_MENU_HOME:
      u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
      break;
    default:
      u8x8_SetGPIOResult(u8x8, 1);			// default return value
      break;
  }
  return 1;
}


