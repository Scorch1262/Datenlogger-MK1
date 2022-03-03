/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ128GB204
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#define FCY 32000000UL 
#include <assert.h>
#include <stdbool.h>
#include "mcc_generated_files/system.h"
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <xc.h>
#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/fatfs/fatfs.h"
#include "command.h"
#include "mcp3221.h"
#include "mcp79410.h"
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

uint8_t day;                                                    // definiert "day"
uint8_t month;                                                  // definiert "month" 
uint8_t year;                                                   // definiert "year"       
uint8_t hour;                                                   // definiert "hour"
uint8_t min;                                                    // definiert "min"
uint8_t sec;                                                    // definiert "sec"
uint8_t count = 0;                                              // definiert "count" 
float temperatur;                                               // definiert "temperatur"
float luftdruck;                                                // defienert "luftdruck"
float volt_Anz;                                                 // definiert "volt_Anz"

/*
                         Main application
 */
int main(void){                                                 // "main"
    SYSTEM_Initialize();                                        // initialize the device
    __delay_ms(500);
    LPS33HW_Init();                                             // initialize den Sensor (LPS33HW)
    
    day = 0x06;                                                 // schreibt "0x04" in "day"
    month = 0x03;                                               // schreibt "0x03" in "month"
    year = 0x21;                                                // schreibt "0x21" in "year"
    hour = 0x09;                                                // schreibt "0x19" in "hour"
    min = 0x17;                                                 // schreibt "0x10" in "min"    
    //MCP79410_set_date_time(day,month,year,hour,min);          // schreibt "day","month","year","hour","min" an RTC

    while(1){                                                   // Endlosschleife
        MCP79410_get_date(&day,&month,&year);                   // lieﬂt "day","month","year" von RTC aus
        MCP79410_get_time(&hour,&min,&sec);                     // lieﬂt "hour","min","sec" von RTC aus
        volt_Anz = MCP3221_GetValue();                          // schreibt "MCP3221_GetValue" in "volt_Anz" 
        temperatur = LPS33HW_temp_GetValue();                   // schreibt ergebnis von "LPS33HW_temp_GetValue" in "temperatur"
        luftdruck = LPS33HW_press_GetValue();                   // schreibt ergebnis von "LPS33HW_press_GetValue" in "luftdruck"
        FatFs_Tasks();                                          // ruft "FatFs_Tasks" auf
        count = count +1;                                       // "count" + 1
        __delay_ms(1000);                                       // warte 1000ms
    }                                                           // 
    return 1;                                                   // 
}                                                               // 
/**
 End of File
*/

