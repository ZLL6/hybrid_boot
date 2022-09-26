#include "mbport.h"
#include "port_user.h"


struct mb_timer mb_timer_d = {
    .timer_enable = 0,
    .expired_offset = 4,    // 5ms
};
BOOL xMBPortTimersInit( USHORT usTimeOut50us )
{
    return TRUE;
}

void 
vMBPortTimerClose( void )
{

}

void
vMBPortTimersEnable( void )
{
    mb_timer_d.timer_enable = 1;
    mb_timer_d.timer_expired_value = HAL_GetTick() + mb_timer_d.expired_offset; 
}

void
vMBPortTimersDisable(  )
{
    mb_timer_d.timer_enable = 0;
    mb_timer_d.timer_expired_value = 0;
}

void
vMBPortTimersDelay( USHORT usTimeOutMS )
{
    uint32_t timer_start = HAL_GetTick(); 
    while(1)
    {
        if ((HAL_GetTick() - timer_start) > usTimeOutMS) {
            break;
        }
    }
}

void TCX_IRQHANDLER( void )
{
    if (mb_timer_d.timer_enable) {
        if (HAL_GetTick() > mb_timer_d.timer_expired_value) {
            pxMBPortCBTimerExpired();
        }
    }
}
