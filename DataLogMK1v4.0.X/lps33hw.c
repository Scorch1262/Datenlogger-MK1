#define FCY 32000000UL

#include "xc.h"
#include <assert.h>
#include <stdbool.h>
#include <libpic30.h>
#include <stdint.h>
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/i2c1.h"
#include "command.h"
#include "lps33hw.h"

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

#define LPS33HW_ADDR    0x5C // oder 0xB8, 0xBB, 0xBA, 0xB9    0x5C 0x5D

#define INTERRUPT_CFG   0x0b
#define THS_P_L         0x0C
#define THS_P_H         0x0d
#define WHO_AM_I        0x0f
#define CTRL_REG1       0x10
#define CTRL_REG2       0x11
#define CTRL_REG3       0x12
#define FIFO_CTRL       0x14
#define REF_P_XL        0x15
#define REF_P_L         0x16
#define REF_P_H         0x17
#define RPDS_L          0x18
#define RPDS_H          0x19
#define RES_CONF        0x1A
#define INT_SOURCE      0x25
#define FIFO_STATUS     0x26
#define STATUS          0x27
#define PRESS_OUT_XL    0x28
#define PRESS_OUT_L     0x29
#define PRESS_OUT_H     0x2A
#define TEMP_OUT_L      0x2B
#define TEMP_OUT_H      0x2C
#define LPFP_RES        0x33

extern I2C1_MESSAGE_STATUS status;                                      // 
extern uint8_t Slave_Address;                                           // definiert "Slave_Address" 
extern uint8_t writeBuffer[3];                                          // definiert "writeBuffer"
extern uint8_t readBuffer[2];                                           // definiert "readBuffer"


void LPS33HW_Init(void){                                                // "LPS33HW_Init"
    Slave_Address = LPS33HW_ADDR;                                       // schreibt "LPS33HW_ADDR" in "Slave_Address"    
  
    writeBuffer[0] = CTRL_REG2;                                         // schreibt "CTRL_REG2" in "writeBuffer[0]"
    writeBuffer[1] = 0b00000001;                                        // schreibt "0b00000001" in "writeBuffer[1]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
    __delay_ms(500);                                                    // warte 500ms
}                                                                       // 

float LPS33HW_temp_GetValue(void){                                      // "LPS33HW_temp_GetValue"  
    Slave_Address = LPS33HW_ADDR;                                       // schreibt "LPS33HW_ADDR" in "Slave_Address"

    uint16_t tempData;                                                  // definiert "tempData"
    float    tempDataAnz;                                               // definiert "tempDataAnz"
    
    writeBuffer[0] = CTRL_REG2;                                         // schreibt "CTRL_REG2" in "writeBuffer[0]"
    writeBuffer[1] = 0b00000001;                                        // schreibt "0b00000001" in "writeBuffer[1]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 

    writeBuffer[0] = TEMP_OUT_H;                                        // schreibt "TEMP_OUT_H" in "writeBuffer[0]"
    I2C1_MasterWrite(&writeBuffer[0], 1, Slave_Address, &status);       // schreibt 1 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
    I2C1_MasterRead(&readBuffer[1], 1, Slave_Address, &status);         // liest von I2C1 in 1 Byte (readBuffer[1]) 
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf
    writeBuffer[0] = TEMP_OUT_L;                                        // schreibt "TEMP_OUT_L" in "writeBuffer[0]"
    I2C1_MasterWrite(&writeBuffer[0], 1, Slave_Address, &status);       // schreibt 1 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
    I2C1_MasterRead(&readBuffer[0], 1, Slave_Address, &status);         // liest von I2C1 in 1 Byte (readBuffer[0]) 
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf
    
    tempData = (readBuffer[1] << 8) + readBuffer[0];                    //       
    tempDataAnz = tempData;                                             // "tempDataAnz" gleich "tempData" 
    tempDataAnz = tempDataAnz / 100;                                    // "tempDataAnz" / 100

    return tempDataAnz;                                                 // gibt "tempDataAnz" zur?ck     
}                                                                       // 

float LPS33HW_press_GetValue(void){                                     // "LPS33HW_press_GetValue" 
    Slave_Address = LPS33HW_ADDR;                                       // schreibt "LPS33HW_ADDR" in "Slave_Address"
    
    float    pressDataAnz;                                              // definiert "pressDataAnz"
    uint32_t pressLSBw;                                                 // definiert "pressLSBw"
    
    writeBuffer[0] = CTRL_REG2;                                         // schreibt "CTRL_REG2" in "writeBuffer[0]"
    writeBuffer[1] = 0b00000001;                                        // schreibt "0b00000001" in "writeBuffer[1]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 

    writeBuffer[0] = PRESS_OUT_XL;                                      // schreibt "PRESS_OUT_XL" in "writeBuffer[0]"
    I2C1_MasterWrite(&writeBuffer[0], 1, Slave_Address, &status);       // schreibt 1 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
    I2C1_MasterRead(&readBuffer[0], 1, Slave_Address, &status);         // liest von I2C1 in 1 Byte (readBuffer[0]) 
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf
    writeBuffer[0] = PRESS_OUT_L;                                       // schreibt "PRESS_OUT_L" in "writeBuffer[0]"
    I2C1_MasterWrite(&writeBuffer[0], 1, Slave_Address, &status);       // schreibt 1 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
    I2C1_MasterRead(&readBuffer[1], 1, Slave_Address, &status);         // liest von I2C1 in 1 Byte (readBuffer[1]) 
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf
    writeBuffer[0] = PRESS_OUT_H;                                       // schreibt "PRESS_OUT_H" in "writeBuffer[0]"
    I2C1_MasterWrite(&writeBuffer[0], 1, Slave_Address, &status);       // schreibt 1 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
    I2C1_MasterRead(&readBuffer[2], 1, Slave_Address, &status);         // liest von I2C1 in 1 Byte (readBuffer[2]) 
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf
    
    pressLSBw = (((uint32_t)readBuffer[2] << 16) | ((uint32_t)readBuffer[1] << 8) | ((uint32_t)readBuffer[0]));
    pressDataAnz = pressLSBw / 4096.0f;                                 // "pressDataAnz" gleich "pressLSBw" / 4096
    
    return pressDataAnz;                                                // gibt "pressDataAnz" zur?ck     
}                                                                       // 