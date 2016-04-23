#include <timer.h>
#include <types.h>
#include <vm.h>

/* memory mapping for timer */
#define TIMER MMIO_P2V(0x101e3000)

#define TIMER_LOAD    0x00
#define TIMER_VALUE   0x01
#define TIMER_CONTROL 0x02
#define TIMER_INTCTL  0x03
#define TIMER_BGLOAD  0x06

void timer_set_interval(uint32_t interval_microsecond)
{
	TIMER[TIMER_CONTROL] = 0;
	TIMER[TIMER_BGLOAD] = 0;
	TIMER[TIMER_LOAD] = interval_microsecond;
	TIMER[TIMER_CONTROL] = 0xe2;	
}

void timer_clear_interrupt(void)
{
	TIMER[TIMER_INTCTL] = 0;
}
