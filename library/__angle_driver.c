/*
    __angle_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__angle_driver.h"
#include "__angle_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __ANGLE_DRV_I2C__
static uint8_t _slaveAddress;
#endif

/* Error register status */
const uint8_t _ANGLE_ERROR_REG_MASK = 0x34;
const uint8_t _ANGLE_EXTENDED_ERROR_REG_MASK = 0x36;
const uint8_t _ANGLE_EXTENDED_ERROR_REG = 0x26;
const uint8_t _ANGLE_ERROR_REG = 0x24;
const uint8_t _ANGLE_STATUS_REG = 0x22;

const uint8_t _ANGLE_SETTINGS_REG = 0x1E;

/* Change Processor State */
const uint16_t _ANGLE_CDS_NO_CHANGLE = 0x0000 << 13;
const uint16_t _ANGLE_CDS_IDLE_MODE  = 0x0002 << 13;
const uint16_t _ANGLE_CDS_RUN_MODE   = 0x0003 << 13;

/* Hard reset */
const uint16_t _ANGLE_HDR_RESET_0   = 0x0000 << 12;
const uint16_t _ANGLE_HDR_RESET_1   = 0x0001 << 12;

/* Soft Reset */
const uint16_t _ANGLE_SFR_RESET_0   = 0x0000 << 11;
const uint16_t _ANGLE_SFR_RESET_1   = 0x0001 << 11;

/* Clear Status registar */
const uint16_t _ANGLE_CSR_STA_0   = 0x0000 << 9;
const uint16_t _ANGLE_CSR_STA_1   = 0x0001 << 9;

/* Clear Extended Error register*/
const uint16_t _ANGLE_CXE_0 = 0x0000 << 8;
const uint16_t _ANGLE_CXE_1 = 0x0001 << 8;

/* Clear Error register */
const uint16_t _ANGLE_CER_0 = 0x0000 << 7;
const uint16_t _ANGLE_CER_1 = 0x0001 << 7;


/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __ANGLE_DRV_SPI__

void angle_spiDriverInit(T_ANGLE_P gpioObj, T_ANGLE_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __ANGLE_DRV_I2C__

void angle_i2cDriverInit(T_ANGLE_P gpioObj, T_ANGLE_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __ANGLE_DRV_UART__

void angle_uartDriverInit(T_ANGLE_P gpioObj, T_ANGLE_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif

// GPIO Only Drivers - remove in other cases
void angle_gpioDriverInit(T_ANGLE_P gpioObj)
{
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
}

/* ----------------------------------------------------------- IMPLEMENTATION */

uint16_t angle_getAngle()
{
    uint8_t writeReg[1];
    uint8_t readReg[2];
    uint16_t Angle;
    uint16_t AngleVal;
    
    writeReg[0] = 0x20;
    
    hal_i2cStart();
    hal_i2cWrite(_slaveAddress,writeReg,1,END_MODE_RESTART);
    Delay_100ms();
    hal_i2cRead(_slaveAddress,readReg,2,END_MODE_STOP);

    angle = readReg[0];
    angle <<= 8;
    angle |= readReg[1];
    angle &= 0x0FFF;
    AngleVal = (uint16_t)( angle * (360 / 4096.0));
    return AngleVal;
}

uint16_t angle_getTemperature()
{
    uint8_t writeReg[1];
    uint8_t readReg[2];
    uint16_t temp;
    uint16_t TempVal;

    writeReg[0] = 0x28;

    hal_i2cStart();
    hal_i2cWrite(_slaveAddress,writeReg,1,END_MODE_RESTART);
    Delay_100ms();
    hal_i2cRead(_slaveAddress,readReg,2,END_MODE_STOP);

    temp = readReg[0];
    temp <<= 8;
    temp |= readReg[1];
    temp &= 0x0FFF;
    TempVal = (uint16_t)temp / 8 - 273;
    return TempVal;
}

uint16_t angle_getMagnetics()
{
    uint8_t writeReg[1];
    uint8_t readReg[2];
    uint16_t magnet;
    uint16_t magnetVal;

    writeReg[0] = 0x2A;

    hal_i2cStart();
    hal_i2cWrite(_slaveAddress,writeReg,1,END_MODE_RESTART);
    Delay_100ms();
    hal_i2cRead(_slaveAddress,readReg,2,END_MODE_STOP);

    magnet = readReg[0];
    magnet <<= 8;
    magnet |= readReg[1];
    magnet &= 0x0FFF;
    magnetVal = (uint16_t)magnet;
    return magnetVal;
}

uint16_t angle_getStatus( uint8_t reg )
{
    uint8_t writeReg[1];
    uint8_t readReg[2];
    uint16_t status;

    writeReg[0] = reg;

    hal_i2cStart();
    hal_i2cWrite(_slaveAddress,writeReg,1,END_MODE_RESTART);
    Delay_100ms();
    hal_i2cRead(_slaveAddress,readReg,2,END_MODE_STOP);

    status = readReg[0];
    status <<= 8;
    status |= readReg[1];
    status &= 0x0FFF;

    return status;
}

void angle_setConfig(uint16_t setValue)
{
    uint8_t writeReg[3];
    writeReg[0] = 0x1E;
    writeReg[1] = setValue >> 8;
    writeReg[2] = setValue & 0x00FF;
    
    hal_i2cStart();
    hal_i2cWrite(_slaveAddress,writeReg,3,END_MODE_STOP);
    Delay_100ms();
}






/* -------------------------------------------------------------------------- */
/*
  __angle_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */