#include "Click_Angle_types.h"

const uint32_t _ANGLE_I2C_CFG[ 1 ] = 
{ 
	_I2C_100KHZ 
};

const uint32_t _ANGLE_UART_CFG[ 4 ] = 
{
	9600, 
	_UART_8_BIT_DATA, 
    _UART_NOPARITY, 
    _UART_ONE_STOPBIT
};

