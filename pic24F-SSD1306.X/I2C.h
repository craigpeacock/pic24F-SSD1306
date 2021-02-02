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

#ifndef XC_HEADER_I2C_H
#define	XC_HEADER_I2C_H

int  I2C_Write(unsigned char address, unsigned char * data, unsigned char bytes);
void I2C_Master_Init(void);
int  IdleI2C(void);
int  WaitforI2C(void);

#define I2C_ADDRESS                 0
#define I2C_COMMAND                 1
#define I2C_BYTE1                   2
#define I2C_BYTE2                   3

#define WRITE                       0
#define READ                        1

#define NOT_BUSY                    0
#define BUSY                        1

// Start Sequences
#define I2C_STATE_IDLE              0
#define I2C_STATE_SEND_ADDRESS      1
#define I2C_STATE_SEND_COMMAND      2

// Send Sequences 
#define I2C_STATE_SEND_DATA         3

// Receive Sequences
#define I2C_STATE_REPEATED_START	5
#define I2C_STATE_SEND_ADDRESS_R	6
#define I2C_STATE_RECEIVE_ENABLE1	7
#define I2C_STATE_RECEIVE_BYTE1		8
#define I2C_STATE_RECEIVE_ENABLE2	9
#define I2C_STATE_RECEIVE_BYTE2		10

// Stop Sequences
#define I2C_STATE_STOP				11
#define I2C_STATE_COMPLETE			12
#define I2C_STATE_ERROR				13

#endif	
