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

#ifndef XC_HEADER_SSD1306_H
#define	XC_HEADER_SSD1306_H

#define SSD1306_SLAVE_ADDRESS           0x3C

void SSD1306_Init();
void SSD1306_Command(unsigned char byte);
void SSD1306_Data(unsigned char byte);

#define SSD1306_SET_CONTRAST                0x81
#define SSD1306_DISPLAY_ALL_ON_RESUME       0xA4
#define SSD1306_DISPLAY_ALL_ON              0xA5
#define SSD1306_NORMAL_DISPLAY              0xA6
#define SSD1306_INVERT_DISPLAY              0xA7
#define SSD1306_DISPLAY_OFF                 0xAE
#define SSD1306_DISPLAY_ON                  0xAF
#define SSD1306_SET_DISPLAY_OFFSET          0xD3
#define SSD1306_SET_COM_PINS                0xDA
#define SSD1306_SETVCOMDETECT               0xDB
#define SSD1306_SET_DISPLAY_CLOCKDIV        0xD5
#define SSD1306_SET_PRECHARGE               0xD9
#define SSD1306_SET_MULTIPLEX               0xA8
#define SSD1306_SETLOWCOLUMN                0x00
#define SSD1306_SETHIGHCOLUMN               0x10
#define SSD1306_SETSTARTLINE                0x40
#define SSD1306_MEMORYMODE                  0x20
#define SSD1306_COLUMNADDR                  0x21
#define SSD1306_PAGEADDR                    0x22
#define SSD1306_COMSCANINC                  0xC0
#define SSD1306_COMSCANDEC                  0xC8
#define SSD1306_SEGREMAP                    0xA0
#define SSD1306_CHARGE_PUMP                 0x8D

#define SSD1306_NOP                         0x3E

//  Scroll (Graphic Acceleration Command) 
#define SSD1306_DEACTIVATE_SCROLL           0x2E    
#define SSD1306_ACTIVATE_SCROLL             0x2F
#define SSD1306_SET_VERTICAL_SCROLL_AREA    0xA3
#define SSD1306_HORIZONTAL_SCROLL_SETUP     0x26

#endif