/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <stddef.h>
#include <alt_types.h>
#include <sys\alt_stdio.h>
#include <sys\alt_irq.h>
#include <sys\alt_timestamp.h>
#include <sys\alt_alarm.h>
#define ALARMTICKS(x) ((alt_ticks_per_second()*(x))/10)
#define MAX 2555

// Note that ALARMTICKS(5) = 1 * 5 / 10 or 0.5 seconds
int main()
{
	int i;
	for(i=0;i<5;i++){
		initialize_thread(i, 0);
	}
	for(i=5;i<8;i++){
		initialize_thread(i, 1);
	}
	for(i=8;i<12;i++){
		initialize_thread(i, 2);
	}
	initialize_alarm();
	//alt_printf("This is my prototype OS.\n");

	for(i=0;i<12;i++){
		join_thread(i);
	}
	prototype_os();
	return 0;
}
void prototype_os()
{
	// initialize the timer and its interrupt handler

	while (1)
	{
		printf("This is my prototype OS.\n");
		int j;
	// a delay loop is used below. Try adjust the value of MAX
	for (j = 0; j < 2554; j++){

	}
	}
	return ;
}
