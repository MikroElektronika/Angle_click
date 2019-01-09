![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Angle Click

- **CIC Prefix**  : ANGLE
- **Author**      : MikroE Team

---

### Software Support

We provide a library for the Angle Click on our [LibStock](https://libstock.mikroe.com/projects/view/1667/angle-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

Key functions :

- ``` uint16_t angle_getAngle() ``` - Read Angle
- ``` uint16_t angle_getTemperature() ``` - Read Temperature
- ``` uint16_t angle_getMagnetics() ``` - Read Magnetics 

**Examples Description**

- System Initialization -  Intializes I2C module, and UART for logging
- Application Initialization -   Driver intialization and Angle settings mode
- Application Task - (code snippet) - Reads encoded Angle in degreeses and Magnetic data in gauss.

```.c

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

```

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/1667/angle-click) page.

mikroE Libraries used in the example:

- I2C
- UART
- Conversions

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
