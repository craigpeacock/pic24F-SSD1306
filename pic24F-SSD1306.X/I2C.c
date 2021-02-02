
#include <p24Fxxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpic30.h>
#include "I2C.h"

unsigned char I2C_Flag;
unsigned char I2C_State;
unsigned int  I2C_Result;
unsigned char I2C_Addr;
unsigned char *I2C_Message;
unsigned char I2C_Data_Index;
unsigned char I2C_Message_Length;

void I2C_Master_Init(void)
{
    I2C1CONbits.I2CEN = 0;	// Disable I2C module
    I2C1BRG = 118;          // I2C1BRG = (12MHz/100KHz - 12MHz/10,000,000) - 1;
    I2C1CONbits.SMEN = 1;   // SMBus Input Levels

    IFS1bits.MI2C1IF = 0;   // Clear I2C Interrupt Flag
    IPC4bits.MI2C1IP = 4;	// Medium Priority
    IEC1bits.MI2C1IE = 1;	// Enable Interrupt
    I2C1CONbits.I2CEN = 1;	// Enable I2C
}

int I2C_Write(unsigned char address, unsigned char * data, unsigned char bytes)
{
    //int i;
    //printf("I2CWrite() = {");
    //for (i = 0; i < bytes; i++)
    //    printf("%02X ",data[i]);
    //printf("}\r\n");
   
	if (IdleI2C() == NOT_BUSY) // Bus is in idle state		
	{
        I2C_Flag = WRITE;
        I2C_Addr = address;
        I2C_Message = data;
        I2C_Message_Length = bytes;
        I2C_Data_Index = 0;
        I2C_State = I2C_STATE_SEND_ADDRESS;

		I2C1CONbits.SEN	= 1; 	// Initiate Start condition on SDAx and SCLx pins (hardware clear at end of master Start sequence)
								// MI2C1IF interrupt is generated at completion of the Start condition.
		return NOT_BUSY;
	}
	else return BUSY;
}

int I2C_Read(unsigned char address, unsigned char command)
{
#if 0
    if (IdleI2C() == NOT_BUSY) // Bus in in idle state		
    {
        I2C_Flag = READ;
		I2C_Message[I2C_ADDRESS] 	= address;
		I2C_Message[I2C_COMMAND] 	= command;
		I2C_State = I2C_STATE_SEND_ADDRESS;
		I2C1CONbits.SEN	= 1; 	// Initiate Start condition on SDAx and SCLx pins (hardware clear at end of master Start sequence)
								// MI2C1IF interrupt is generated at completion of the Start condition.
		while (I2C_State != I2C_STATE_IDLE);	// Wait for I2C to complete
		return I2C_Result;
	}
	else return BUSY;
#endif
}

void __attribute__((interrupt, auto_psv)) _MI2C1Interrupt(void)
{
    // The MI2CxIF interrupt is generated on completion of the following master message events:
    //  * Start condition
    //  * Stop condition
    //  * Data transfer byte transmitted or received
    //  * Acknowledge transmit
    //  * Repeated Start
    //  * Detection of a bus collision event.    

    switch (I2C_State)
    {
		case I2C_STATE_IDLE:	
			// No interrupt should be generated in idle mode
			break;

		case I2C_STATE_SEND_ADDRESS: 
            // We have sent start, so now send device address
			I2C1TRN = (I2C_Addr << 1);		// Load address, shifted one as address is 7 bits, LSB = 0 as we are writing
			I2C_State = I2C_STATE_SEND_DATA;			
			break;

		case I2C_STATE_SEND_DATA: 
            // We have sent device address, now send command/data
			if(I2C1STATbits.ACKSTAT==1)         // Ack not received, Retry 
			{ 
				I2C_State = I2C_STATE_ERROR;    // Flag error and exit
			}
			else 
			{
                printf("Byte %d [%02X]\r\n",I2C_Data_Index,I2C_Message[I2C_Data_Index]);
                I2C1TRN = I2C_Message[I2C_Data_Index++];    // Load command byte
                
                if (I2C_Data_Index >= I2C_Message_Length) {
                    // Finished sending command/data. 
                    // If write op, we can stop. If read op, initiate reading
                    if (I2C_Flag == WRITE)	I2C_State = I2C_STATE_STOP;
                    else                    I2C_State = I2C_STATE_REPEATED_START;
                }
			}
			break;

            //
            // Receive Sequences
            //
            
        case I2C_STATE_REPEATED_START:
			// The lower 5 bits of the I2CxCON register must be ‘0’ (master logic inactive) before
			// attempting to set the RSEN bit.
			I2C1CONbits.RSEN = 1;	// initiate repeated start
			I2C_State = I2C_STATE_SEND_ADDRESS_R;
			break;

        case I2C_STATE_SEND_ADDRESS_R:
			I2C1TRN = ((I2C_Message[I2C_ADDRESS]  << 1) | 0b00000001);		// Load address, shifted one as address is 7 bits, LSB = 1 as we are reading
			I2C_State = I2C_STATE_RECEIVE_ENABLE1;
			break;

        case I2C_STATE_RECEIVE_ENABLE1:
			if(I2C1STATbits.ACKSTAT==1) // Ack Not received, Retry 
			{ 
				I2C_State = I2C_STATE_ERROR;	// Flag error and exit
			}
			else
			{
				I2C1CONbits.RCEN	= 1;	// Setting RCEN starts a master reception
				I2C_State = I2C_STATE_RECEIVE_BYTE1;
			}
			break;

		case I2C_STATE_RECEIVE_BYTE1:
			if(I2C1CONbits.RSEN) {
                // We are still starting
            }
			else
			{
				I2C_Result = I2C1RCV << 8;
				I2C1CONbits.ACKDT = 0;	// ACK
				I2C1CONbits.ACKEN = 1;	// Start acknowledge event
				I2C_State = I2C_STATE_RECEIVE_ENABLE2;
			}
			break;

		case I2C_STATE_RECEIVE_ENABLE2:
			I2C1CONbits.RCEN	= 1;	// Setting RCEN starts a master reception
			I2C_State = I2C_STATE_RECEIVE_BYTE2;
			break;

		case I2C_STATE_RECEIVE_BYTE2:
			if(I2C1CONbits.RSEN) {
            
            } 
            else
			{
				I2C_Result += I2C1RCV;
				I2C1CONbits.ACKDT = 1;	// NegACK
				I2C1CONbits.ACKEN = 1;	// Start acknowledge event
				I2C_State = I2C_STATE_STOP;
			}
			break;
            
            //
            // Stop Sequences
            //
            
		case I2C_STATE_STOP: 
            // Send stop
			if(I2C1STATbits.ACKSTAT==1) // Ack Not received, Retry 
			{ 
				I2C_State = I2C_STATE_ERROR;					// Flag error and exit
			}
			else 
			{
      			I2C1CONbits.PEN=1;
				I2C_State = I2C_STATE_COMPLETE;
			}
			break;

		case I2C_STATE_COMPLETE:
			if (IdleI2C() == NOT_BUSY) I2C_State = I2C_STATE_IDLE;
			else I2C_State = I2C_STATE_ERROR;
			break;

		case I2C_STATE_ERROR: 
			I2C_State = 0;
			break;

	}    
    IFS1bits.MI2C1IF = 0; 
}

int IdleI2C(void)
{
    // Check if I2C Bus is Inactive
    if(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT)
	{
		return BUSY;
	}
	else return NOT_BUSY;	
}

int WaitforI2C(void)
{
    while (I2C_State != I2C_STATE_IDLE) {};  
}


