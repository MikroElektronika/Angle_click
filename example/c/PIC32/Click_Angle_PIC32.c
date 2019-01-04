/*
Example for Angle Click

    Date          : Dec 2017.
    Author        : MikroE Team

Test configuration PIC32 :
    
    MCU                : P32MX795F512L
    Dev. Board         : EasyPIC Fusion v7
    PIC32 Compiler ver : v4.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization -  Intializes I2C module
- Application Initialization -   Driver intialization and Angle settings mode
- Application Task - (code snippet) - Reads encoded Angle in degreeses and Magnetic data in gauss.

*/

#include "Click_Angle_types.h"
#include "Click_Angle_config.h"

uint16_t Angle;
uint16_t Magnetics;

char txt[50];

void systemInit()
{
     mikrobus_i2cInit( _MIKROBUS1, &_ANGLE_I2C_CFG[0] );
     mikrobus_logInit( _LOG_USBUART_A, 9600 );
     Delay_100ms();
}

void applicationInit()
{
    angle_i2cDriverInit( (T_ANGLE_P)&_MIKROBUS1_GPIO, (T_ANGLE_P)&_MIKROBUS1_I2C, 0x0C );
    angle_setConfig(_ANGLE_CDS_NO_CHANGLE | _ANGLE_HDR_RESET_1 | _ANGLE_SFR_RESET_1 | _ANGLE_CSR_STA_1 | _ANGLE_CXE_1 | _ANGLE_CER_1);
    mikrobus_logWrite("Initialize.....",_LOG_LINE);
}

void applicationTask()
{
    Angle = angle_getAngle();
    IntToStr(Angle,txt);
    mikrobus_logWrite("Angle :",_LOG_TEXT);
    mikrobus_logWrite(txt,_LOG_LINE);

    Magnetics = angle_getMagnetics();
    IntToStr(Magnetics,txt);
    mikrobus_logWrite("Magnetics :",_LOG_TEXT);
    mikrobus_logWrite(txt,_LOG_LINE);
    Delay_1sec();
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}