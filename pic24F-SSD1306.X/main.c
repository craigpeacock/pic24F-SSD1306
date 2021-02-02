/* 
Example code for SSD1306 Based OLED LCD
Connect SDA to RD9, SCL to RD10
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

#include <p24Fxxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpic30.h>

#include "board.h"
#include "I2C.h"
#include "SSD1306.h"

int main(void){

    //*************************************
    // Unlock Registers
    //*************************************
    asm volatile (  "MOV #OSCCON, w1 \n"
                    "MOV #0x46, w2 \n"
                    "MOV #0x57, w3 \n"
                    "MOV.b w2, [w1] \n"
                    "MOV.b w3, [w1] \n"
                    "BCLR OSCCON,#6");
    //***************************
    // Configure Input Functions
    // (See Table 10-2)
    //***************************
    RPINR18bits.U1RXR = 23;   // U1 RX In = RP23
    //***************************
    // Configure Output Functions
    // (See Table 10-3)
    //***************************
    RPOR11bits.RP22R = 3;    // U1 TX Out = RP22
    //*************************************
    // Lock Registers
    //*************************************
    asm volatile (  "MOV #OSCCON, w1 \n"
                    "MOV #0x46, w2 \n"
                    "MOV #0x57, w3 \n"
                    "MOV.b w2, [w1] \n"
                    "MOV.b w3, [w1] \n"
                    "BSET OSCCON, #6" );

    TRISEbits.TRISE0 = 0; 	// Make LED 1 an output
    TRISEbits.TRISE1 = 0;	// Make LED 2 an output
    TRISEbits.TRISE2 = 0;	// Make LED 3 an output
    TRISEbits.TRISE3 = 0;	// Make LED 4 an output
   
    UART_Init();
    printf("\r\nPIC24F SSD1306 Example\r\n");
        
    I2C_Master_Init();
    printf("I2C Initialised\r\n");
 
    SSD1306_Init(); 
    printf("SSD1306 Initialised\r\n");
    
    while(1) {

    }
}




