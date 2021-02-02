/* 
Copyright (C) 2021 Craig Peacock

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "xc.h"
#include "SSD1306.h"
#include "I2C.h"

void SSD1306_Command(unsigned char byte)
{
    uint8_t payload[2];
    payload[0] = 0x00;
    payload[1] = byte;
    
    I2C_Write(SSD1306_SLAVE_ADDRESS, &payload[0], 2);
    WaitforI2C();
}

void SSD1306_Data(unsigned char byte)
{
    uint8_t payload[2];
    payload[0] = 0x40;
    payload[1] = byte;
  
    I2C_Write(SSD1306_SLAVE_ADDRESS, &payload[0], 2);
    WaitforI2C();
}

void SSD1306_Init(void)
{
    // Turn Display Off.
    SSD1306_Command(SSD1306_DISPLAY_OFF);

    // Set Display Clock Divide Ratio/ Oscillator Frequency.
    SSD1306_Command(SSD1306_SET_DISPLAY_CLOCKDIV);
    SSD1306_Command(0x80);
    
    // Set Multiplex Ratio
    SSD1306_Command(SSD1306_SET_MULTIPLEX);
    SSD1306_Command(0x3F);

    // Set Display Offset     
    SSD1306_Command(SSD1306_SET_DISPLAY_OFFSET);
    SSD1306_Command(0x00);
    
    // Set Charge Pump
    SSD1306_Command(SSD1306_CHARGE_PUMP);
    SSD1306_Command(0x14);

    SSD1306_Command(SSD1306_SETSTARTLINE | 0x00);   

    SSD1306_Command(SSD1306_NORMAL_DISPLAY);
   
    SSD1306_Command(SSD1306_MEMORYMODE);
    SSD1306_Command(0x00); // Horizontal Addressing Mode
   
    SSD1306_Command(SSD1306_SEGREMAP | 0x0);
    
    SSD1306_Command(SSD1306_COMSCANINC);
    
    SSD1306_Command(SSD1306_SET_COM_PINS);
    SSD1306_Command(0x12);
    
    SSD1306_Command(SSD1306_SET_CONTRAST); 
    SSD1306_Command(0xCF);

    SSD1306_Command(SSD1306_SET_PRECHARGE);
    SSD1306_Command(0xF1);
  
    SSD1306_Command(SSD1306_SETVCOMDETECT);
    SSD1306_Command(0x30);
  
    // Turn entire display on regardless of GDDRAM contents
    SSD1306_Command(SSD1306_DISPLAY_ALL_ON); 
    //SSD1306_Command(SSD1306_INVERT_DISPLAY);
    //SSD1306_Command(SSD1306_DEACTIVATE_SCROLL);
    SSD1306_Command(SSD1306_DISPLAY_ON); 
}