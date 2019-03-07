/*--------------------------------------------------------------------------------------------
 *  Контрольная сумма crc32 с использованием аппартного блока STM32F4xx.
 *  Poly  : 0x04c11db7    x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
 *  Init  : 0xffffffff
 *  Revert: true
 *  XorOut: 0xffffffff
 * -------------------------------------------------------------------------------------------------------- */

#include "CRC32.h"

//void sw_CRC32_ON(void) { RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE); }  // включаем тактирование
//void sw_CRC32_OFF(void){ RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, DISABLE);}  // выключаем тактирование
/*
uint32_t sw_calculate_crc(uint32_t *input_data, uint32_t length)
{
    uint32_t* pBuffer        = input_data;		// присваеваем адресс начала данных
    uint32_t index           = 0;
    uint32_t result          = 0;

    sw_CRC32_ON();								// включить тактирование
    CRC->CR = CRC_CR_RESET;						// сброс контрольного регистра

    while(index<length){CRC->DR = pBuffer[index++];}
    result = CRC->DR;							// извлечь просчитаную контрольную сумму

    sw_CRC32_OFF();								// выключить тактирование

    return result;
}
*/


uint32_t sw_calculate_soft_crc(uint32_t *pinput, uint32_t length)
{
	uint32_t initial_crc = 0xFFFFFFFF;                   // начальное значение контрольной суммы
	uint32_t* input_data = pinput;
	uint32_t polynom     = 0x4C11DB7 ;                   // полином
	uint32_t crc         = 0         ;                   // контрольная сумма
	uint32_t index       = 0;
	uint32_t bindex      = 0;

    while( index<length )
    {
    if(index==0){   crc = initial_crc ^ input_data[index];}
    else        {   crc = crc ^ input_data[index];        }

        while(   bindex<(sizeof(input_data[index])*8)   )
        {	// if MSB of CRC = 1
            if((crc>>31)==1){crc=(crc<<1)^polynom;}
            else            {crc=(crc<<1);        }
            bindex++;
        }

    bindex=0;
    index++;
    }

    return crc;
}
