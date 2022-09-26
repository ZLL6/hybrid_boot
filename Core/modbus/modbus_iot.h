#ifndef MODBUS_IOT_H
#define MODBUS_IOT_H
#include "main.h"
#include "mb.h"

/* ----------------------- Defines ------------------------------------------*/
#define REG_INPUT_START                 ( 1000 )
#define REG_INPUT_NREGS                 ( 64 )

#define REG_HOLDING_START               ( 1 )
#define REG_HOLDING_NREGS               ( 32 )

#define TASK_MODBUS_STACK_SIZE          ( 256 )
#define TASK_MODBUS_PRIORITY            ( tskIDLE_PRIORITY + 1 )

#define TASK_APPL_STACK_SIZE            ( 256 )
#define TASK_APPL_PRIORITY              ( tskIDLE_PRIORITY + 1 )


extern struct modbus_32bitdata_serialization modbus_data_total;
extern struct rtc_time c_time_dec_last;

extern uint16_t arm_software_version;
extern uint16_t c2000_software_version;


/* ----------------------- functions ---------------------------------*/

int time_correction(uint8_t *addr, uint16_t size_byte);
int mb_invoke_flash_upgrade(uint8_t *addr, uint16_t size_byte);

/* ----------------------- Static variables ---------------------------------*/
static USHORT   usRegInputStart = REG_INPUT_START;
static USHORT   usRegInputBuf[REG_INPUT_NREGS];
static USHORT   usRegHoldingStart = REG_HOLDING_START;
static USHORT   usRegHoldingBuf[REG_HOLDING_NREGS];

#endif
