#include "pbdata.h"

#define GPIOX GPIOB


//This Function will independtly keep the screen running by init GPIO it self
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
			arg_int?GPIO_SetBits(GPIOB, GPIO_Pin_3):GPIO_ResetBits(GPIOB, GPIO_Pin_3);
      break;
    case U8X8_MSG_GPIO_D1:				// D1 or SPI data pin: Output level in arg_int
    //case U8X8_MSG_GPIO_SPI_DATA:
			arg_int?GPIO_SetBits(GPIOB, GPIO_Pin_4):GPIO_ResetBits(GPIOB, GPIO_Pin_4);
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
			arg_int?GPIO_SetBits(GPIOB, GPIO_Pin_6):GPIO_ResetBits(GPIOB, GPIO_Pin_6);
      break;
    case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
			arg_int?GPIO_SetBits(GPIOB, GPIO_Pin_5):GPIO_ResetBits(GPIOB, GPIO_Pin_5);
      break;
    case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
			arg_int?GPIO_SetBits(GPIOB, GPIO_Pin_7):GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			//Set/Reset Bit in OneLine
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