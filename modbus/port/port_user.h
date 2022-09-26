#ifndef PORT_USER_H
#define PORT_USER_H
#include "main.h"
#include "mb_common.h"


struct mb_timer 
{
    uint16_t timer_enable;
    uint16_t expired_offset;
    uint32_t timer_expired_value;
};

void    vMBPortSetWithinException( BOOL bInException );
BOOL    bMBPortIsWithinException( void );
void    TCX_IRQHANDLER( void );
void    prvvMasterTIMERExpiredISR(void);

#endif
