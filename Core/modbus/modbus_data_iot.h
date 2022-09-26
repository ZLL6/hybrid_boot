#ifndef MODBUS_DATA_H
#define MODBUS_DATA_H
#include "modbus_iot.h"
#include "common.h"
extern const struct modbus_data_operation mb_data_pool_iot[];
extern uint8_t machine_serial_number[];
extern const uint32_t MB_DATA_IOT_NUM;
extern uint16_t machine_current_status;
extern uint16_t battery_current;
extern uint16_t mb_machine_fault_code[];
#endif
