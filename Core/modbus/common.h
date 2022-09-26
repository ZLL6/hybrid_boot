#ifndef COMMON_H
#define COMMON_H
#include <stdint.h>


#define MAX_REGS_NUM_ONCE_OPERATION 128
#define __maybe_unused __attribute__ ((unused))	
struct modbus_data_operation
{
    uint8_t properity;   /* define in enum modbus_data_properity */
    uint8_t ratio;
    uint16_t len_2byte;
    uint16_t mb_addr;
    uint16_t memory_event;  /*notify save to eeprom enevt*/
    uint16_t *data_addr; 
    /*bit fields mask, use this need to enable IS_BIT_FIELDS in properity*/
    uint16_t read_mask;
    uint16_t write_mask;
    int (*ops)(uint8_t *addr, uint16_t size_byte);
};

enum modbus_data_properity
{
    RW_DENIED = 0,
    READ_ONLY = 1,
    WRITE_ONLY = 2,
    READ_WRITE = 3,
    IS_OPS = 0x40,
    IS_BIT_FIELDS = 0x80
};

#define TO_UINT16_T(info) *((uint16_t *)(&info))
extern const char byte_to_ascii[16];

void * memcpy_t(void *dest, const void *src, int count);
void *memory_set_t(void *dest, int value, int size_byte);
uint8_t ascii_to_char_4bit(uint8_t src);
int convert_ascii_to_number(uint8_t *src, uint8_t *dest, int dest_len);

int up_down_lmt_setting(uint16_t *value, uint16_t up_lmt, uint16_t down_lmt);
#endif
