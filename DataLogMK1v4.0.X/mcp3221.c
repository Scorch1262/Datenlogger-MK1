/*
 * File:   MCP3221.c
 * Author: Torben
 *
 * Created on December 17, 2020, 9:24 AM
 */

// AD-Wandler
#define FCY 32000000UL

#include <xc.h>
#include <assert.h>
#include <stdbool.h>
#include <libpic30.h>
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/i2c1.h"
#include "command.h"
#include "mcp3221.h"

#if defined(__dsPIC33E__)
	#include <p33exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33fxxxx.h>
#elif defined(__dsPIC30F__)
	#include <p30fxxxx.h>
#elif defined(__PIC24E__)
	#include <p24exxxx.h>
#elif defined(__PIC24H__)
	#include <p24hxxxx.h>
#elif defined(__PIC24F__) || defined(__PIC24FK__)
	#include <p24fxxxx.h>
#endif

#define MCP3221_ADDR    0x4D                                            // 

extern I2C1_MESSAGE_STATUS status;                                      // 
extern uint8_t Slave_Address;                                           // definiert "Slave_Address" 
extern uint8_t writeBuffer[3];                                          // definiert "writeBuffer"
extern uint8_t readBuffer[2];                                           // definiert "readBuffer"

float MCP3221_GetValue(void){                                           // "MCP3221_GetValue"
    Slave_Address = MCP3221_ADDR;                                       // schreibt "MCP3221_ADDR" in "Slave_Address"
    float ADCData;                                                      // definiert "ADCData" 
    readBuffer[0] = 0x00;                                               // setzt "readBuffer[0]" auf 0
    readBuffer[1] = 0x00;                                               // setzt "readBuffer[1]" auf 0
  
    I2C1_MasterRead(&readBuffer[0], 2, Slave_Address, &status);         // liest von I2C1 in 2 Byte (readBuffer[0]) 
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf

    ADCData = (readBuffer[0] << 8) + readBuffer[1];                     // 
    ADCData =  ADCData  / 100;                                          // "ADCData" / 100
    
    return ADCData;                                                     // gibt wert von "ADCData" zurück
}                                                                       // 

