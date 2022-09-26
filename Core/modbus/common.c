#include <stdint.h>
#include "common.h"
#include "stddef.h"

/*
 * bsearch - binary search an array of elements
 * @key: pointer to item being searched for
 * @base: pointer to first element to search
 * @num: number of elements
 * @size: size of each element
 * @cmp: pointer to comparison function
 *
 * This function does a binary search on the given array.  The
 * contents of the array should already be in ascending sorted order
 * under the provided comparison function.
 *
 * Note that the key need not have the same type as the elements in
 * the array, e.g. key could be a string and the comparison function
 * could compare the string with the struct's name field.  However, if
 * the key and elements in the array are of the same type, you can use
 * the same comparison function for both sort() and bsearch().
 */
void *bsearch(const void *key, const void *base, uint32_t num, uint32_t size,
	      int (*cmp)(const void *key, const void *elt))
{
	const char *pivot;
	int result;

	while (num > 0) {
		pivot = (const char *)base + (num >> 1) * size;
		result = cmp(key, pivot);

		if (result == 0)
			return (void *)pivot;

		if (result > 0) {
			base = pivot + size;
			num--;
		}
		num >>= 1;
	}

	return NULL;
}

int compare_modbus_data_addr(const void *key, const void *elt)
{
    uint16_t target_addr = ((const struct modbus_data_operation *)key)->mb_addr;
    uint16_t cur_addr = ((const struct modbus_data_operation *)elt)->mb_addr;
    if (target_addr == cur_addr)
        return 0;
    else if (target_addr > cur_addr)
        return 1;
    else
        return -1;
}

int binary_search(uint16_t search_target, uint32_t *target_index, \
    const struct modbus_data_operation *data_pool, int data_pool_num)
{   
    uint32_t low = 0;
    uint32_t high = data_pool_num - 1;
    while (low <= high) {
        uint32_t mid = (low + high) >> 1;
        uint16_t mid_addr = data_pool[mid].mb_addr;
        if (mid_addr == search_target) {
            *target_index = mid;
            return 0;
        }
        else if (mid_addr > search_target) {
            high = mid - 1;
        }
        else if (mid_addr < search_target) {
            low = mid + 1;
        }
    }
    return -1;
}

uint8_t ascii_to_char_4bit(uint8_t src)
{
    uint8_t ret;
    if ((src >= '0') && (src <= '9')) {
        ret = src - '0';
    }
    else if ((src >= 'A') && (src <= 'F')) {
        ret = src - 'A' + 10;
    }
    else {
        ret = 0xFF;
    }
    return ret;
}


int convert_ascii_to_number(uint8_t *src, uint8_t *dest, int dest_len)
{
    for (int i = 0; i < dest_len; ++i) {
        *dest = ascii_to_char_4bit(*src) << 4;
        src++;
        *dest |= ascii_to_char_4bit(*src);
        src++;
        dest++;
    }
    return 0;
}

void *memory_set_t(void *dest, int value, int size_byte)
{
    uint8_t * dst = (uint8_t *)dest;
    while(size_byte--) {
        *dst++ = value;
    }
    return dest;
}

/**
 * memcpy - Copy one area of memory to another
 * @dest: Where to copy to
 * @src: Where to copy from
 * @count: The byte size of the area.
 *
 * You should not use this function to access IO space, use memcpy_toio()
 * or memcpy_fromio() instead.
 */
void * memcpy_t(void *dest, const void *src, int count)
{
	unsigned long *dl = (unsigned long *)dest, *sl = (unsigned long *)src;
	char *d8, *s8;

	if (src == dest)
		return dest;

	/* while all data is aligned (common case), copy a word at a time */
	if ( (((uint32_t)dest | (uint32_t)src) & (sizeof(*dl) - 1)) == 0) {
		while (count >= sizeof(*dl)) {
			*dl++ = *sl++;
			count -= sizeof(*dl);
		}
	}
	/* copy the reset one byte at a time */
	d8 = (char *)dl;
	s8 = (char *)sl;
	while (count--)
		*d8++ = *s8++;

	return dest;
}


int up_down_lmt_setting(uint16_t *value, uint16_t up_lmt, uint16_t down_lmt)
{
    *value = (*value > up_lmt) ? up_lmt : *value;
    *value = (*value < down_lmt) ? down_lmt : *value;
    return 0;    
}


const char byte_to_ascii[16] = {
    '0','1','2','3','4','5','6','7',
    '8','9','A','B','C','D','E','F',
};
