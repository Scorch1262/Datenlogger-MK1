/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
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


#include "ff.h"
#include "../mcc.h"
#include "../../mcc_generated_files/sd_spi/sd_spi.h"
#include "../../mcp79410.h"

static FATFS drive;
static FIL file;

extern uint8_t day;                                                             // definiert "day"
extern uint8_t month;                                                           // definiert "month" 
extern uint8_t year;                                                            // definiert "year"       
extern uint8_t hour;                                                            // definiert "hour"
extern uint8_t min;                                                             // definiert "min"
extern uint8_t sec;                                                             // definiert "sec"
extern uint8_t count;                                                           // definiert "count"
extern float temperatur;                                                        // definiert "temperatur"
extern float luftdruck;                                                         // defienert "luftdruck"
extern float volt_Anz;                                                          // definiert "volt_Anz"

void FatFs_Tasks(void){                                                         // "FatFs_Tasks"
    UINT actualLength;                                                          // definiert "actualLength"
    char data[70] = {0};                                                        // definiert "data"
    char datafilename[50] = {0};                                                // definiert "filename"
    char enter[2] = "\r\n";                                                     // definiert "enter" und schreibt "\r\n" hinein
    
    sprintf(datafilename, "20%02x-%02x-%02xLogdatei.TXT" ,                      // schreibt "Logdatei20%02x-%02x-%02x.TXT"
            year,                                                               // 
            month,                                                              // 
            day);                                                               // 
    sprintf(data, "Werte %.2fC  %.2fhPa  %.2fV  %02x:%02x:%02x  %d" ,           // schreibt "Werte %.2fC  %.2fhPa  %.2fV  %02x:%02x:%02x  %d"
            temperatur,                                                         // 
            luftdruck,                                                          // 
            volt_Anz,                                                           // 
            hour,                                                               // 
            min,                                                                // 
            sec,                                                                // 
            count);                                                             // 

    if(SD_SPI_IsMediaPresent() == false){                                       // wenn "SD_SPI_IsMediaPresent" gleich "false"
        LED1_Toggle();                                                          // Blinkt mit LED1
        return;                                                                 // Zurück
    }                                                                           // 
    
    if(f_mount(&drive,"0:",1) == FR_OK){                                        // Wenn Mount von SD-Karte ist gleich "FR_OK"
        if(f_open(&file, datafilename, FA_OPEN_APPEND | FA_READ | FA_WRITE) == FR_OK){ // erzeugt/öffnet "filename"
            f_write(&file, data, sizeof(data)-1, &actualLength);                // schreibt "data" in "file"
            f_write(&file, enter, sizeof(enter)-1, &actualLength);              // schreibt "enter" in "file"
            f_close(&file);                                                     // schließt Datei "file"
        }                                                                       // 
        f_mount(0,"0:",0);                                                      // Dismount SD-Karte 
    }                                                                           // 
}                                                                               // 