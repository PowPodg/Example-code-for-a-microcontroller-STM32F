#include "usart.h"
//-------------------------------------------------------------------------
void USART_SetGain_Init(void) {
USART_ClockInitTypeDef USART_ClockInitStruct;
/* USART configuration -------------------------------------------------------*/
USART_ClockInitStruct.USART_CPHA=USART_CPHA_1Edge;
USART_ClockInitStruct.USART_CPOL=USART_CPOL_Low;
USART_ClockInitStruct.USART_LastBit=USART_LastBit_Disable;
/* The synchronous mode is selected by writing the CLKEN bit in the USART_CR2 register to 1*/
USART_ClockInitStruct.USART_Clock=USART_Clock_Enable;
/*In synchronous mode, the following bits must be kept cleared:*/
// cleared LINEN bit in the USART_CR2 register
USART_LINCmd(USART3,DISABLE);
//cleared SCEN,
USART_SmartCardCmd(USART3,DISABLE);
//cleared HDSEL
USART_HalfDuplexCmd(USART3,DISABLE);
//cleared IREN bits in the USART_CR3 register.
USART_IrDACmd(USART3,DISABLE);
USART_ClockInit(USART3,&USART_ClockInitStruct);

USART_InitTypeDef USART_InitStruct;
USART_StructInit(&USART_InitStruct);
USART_InitStruct.USART_BaudRate=4500000;//4.5 MHz (for AD5160 Fclk max=25 MHz)
USART_InitStruct.USART_Mode = USART_Mode_Tx;
/*
SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
//SPI_SSOutputCmd(SPI1,DISABLE);
SPI_InitStructure.SPI_NSS = SPI_NSS_Hard
SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2
SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//The CRC polynomial (0007h) is the reset value of this register.
SPI_InitStructure.SPI_CRCPolynomial = 0x07;
*/
USART_Init(USART3, &USART_InitStruct);

/* Enable SPI */
USART_Cmd(USART3, ENABLE);
}
//-----------------------------------------------------------------------------------------------------
void USART_SetGain_SendData(uint16_t Data)
{
	GPIO_WriteBit(GPIOD,GPIO_Pin_2,Bit_RESET); //SC to "0" for U1 Digital Potentiometer AD5160
	USART_SendData(USART3, Data);
	  /* Loop until the end of transmission */
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	GPIO_WriteBit(GPIOD,GPIO_Pin_2,Bit_SET); //PD2 - SC to "1" for  transfer to the internal RDAC register (U1 Digital Potentiometer AD5160)
}

