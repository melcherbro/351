
#include <stdio.h>
#include <sys\alt_stdio.h>
#include <sys\alt_irq.h>
#include <sys\alt_timestamp.h>
#include <sys\alt_alarm.h>
#include <header.h>
int from_handler = 0;
alt_alarm alarm ;
#define DISABLE_INTERRUPTS() { \
asm("wrctl status, zero"); \
}
// enable an interrupt
#define ENABLE_INTERRUPTS() { \
asm("movi et, 1"); \
asm("wrctl status, et"); \
}
alt_u32 my_interrupt_handler(){
	DISABLE_INTERRUPTS();
	printf("handler\n");
	from_handler = 1;
	return 0;
}

void initialize_alarm(){
	if(alt_alarm_start(&alarm, alt_ticks_per_second(), my_interrupt_handler, NULL) != 0){
				printf("ERROR WITH TIMER");
			}
}

void reset_alarm(alt_u32 ticks){
	alt_alarm_stop(&alarm);
	if(alt_alarm_start(&alarm, ticks, my_interrupt_handler, NULL) != 0){
				printf("ERROR WITH TIMER");
			}
}
