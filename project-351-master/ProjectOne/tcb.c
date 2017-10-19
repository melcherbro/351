#include <header.h>
#include <stdio.h>
#include <sys\alt_stdio.h>
#include <sys\alt_irq.h>
#include <sys\alt_timestamp.h>
#include <sys\alt_alarm.h>
// disable an interrupt
#define DISABLE_INTERRUPTS() { \
asm("wrctl status, zero"); \
}
// enable an interrupt
#define ENABLE_INTERRUPTS() { \
asm("movi et, 1"); \
asm("wrctl status, et"); \
}
struct thread{
	alt_u32 id;
	alt_u32 *stack_address;
	alt_u32 stack_size;
	alt_u32 *stack_pointer;
	alt_u32 state;
	alt_u32 priority;
	alt_u32 runs;
};
struct thread threads[12];
alt_u32 current_thread = 0;
extern from_handler;
int check_interrupt(){
	if(from_handler == 1){
	//printf("check:%x\n",current_thread );
		}
	return from_handler;
}
void my_thread(alt_u32 thread_id){
	//DISABLE_INTERRUPTS();
	int i = 0;
	for(i=0; i<0xFFFFF; i++){

	}
	alt_printf("This is my thread:%x\n", thread_id);
	//DISABLE_INTERRUPTS();
}
void join_thread(alt_u32 id){
	while(threads[id].state != 2){

	}
}
void destroy_thread(){
	DISABLE_INTERRUPTS();
	//free(threads[current_thread].stack_address);
	threads[current_thread].state = 2;
	ENABLE_INTERRUPTS();
	while(1){
		int i = 0;
		for(i=0; i<2555; i++){

		}
	}
}

void initialize_thread(int num_thread, int priority){

		threads[num_thread].stack_size = 700;
		threads[num_thread].stack_address = malloc(threads[num_thread].stack_size);
		threads[num_thread].stack_pointer = (threads[num_thread].stack_address+threads[num_thread].stack_size-19);
		//threads[num_thread].stack_pointer = (alt_u32 *)(threads[num_thread].stack_address+threads[num_thread].stack_size/2);
		threads[num_thread].state = 0;
		threads[num_thread].priority=priority;

		//initialize stack
		threads[num_thread].stack_pointer[-1] = threads[num_thread].stack_address+threads[num_thread].stack_size;
		threads[num_thread].stack_pointer[0] = &destroy_thread;
		threads[num_thread].stack_pointer[5] = num_thread;
		threads[num_thread].stack_pointer[18] = &my_thread; //72
		threads[num_thread].stack_pointer[17] = 1;
}
int first_run = 1;
alt_u32 *main_context;
alt_u32 my_scheduler(alt_u32 sp){//round robin
	from_handler = 0;
	if(first_run == 1){
		main_context = sp;
		first_run =0;
	}



	/* This section of code is for testing to make sure the threads haven't finished */
	int thread_count = 0;
	if(threads[current_thread].state == 1)						//Check to see if thread is in "Running" state
	{
		alt_printf("This test ran\n");
		threads[current_thread].state = 3;//If so we change the state to paused
		threads[current_thread].stack_pointer = sp;
		alt_printf("stack pointer_after run thread[%x]: %x\n", current_thread, sp);
		current_thread = (current_thread+1)%12;					//and move on to the next thread
	}
	while(threads[current_thread].state == 2 && thread_count < 12)
	{
		alt_printf("thread %x is dead\n", current_thread);
		thread_count++;											//This is used to keep track to see how many times we've run through the code
		current_thread = (current_thread+1)%12;					//Move to the next thread
	}
	if(threads[current_thread].runs == 1){
		//printf("Test:%x", *sp);
	}
if(thread_count == 12){ // all are dead
	//first_run = 1;
	//alt_alarm_stop(&alarm);
	return main_context;
}
	threads[current_thread].state = 1;  // set to running

	/* This is going to be a test to see if memory retention is working */


	//alt_printf("test:%x\n",current_thread );
	//threads[current_thread].stack_pointer[0] =  &destroy_thread;


	/* This is for setting the run quantum time */
	int x = 1;
	if(threads[current_thread].priority == 0)
		x = 2;
	if(threads[current_thread].priority == 1)
		x = 1.5;
	reset_alarm(alt_ticks_per_second()*x);
	threads[current_thread].runs++;
	alt_printf("Stack pointer_prerun thread[%x]: %x\n", current_thread,threads[current_thread].stack_pointer);
	alt_printf("Run count: %x\n",threads[current_thread].runs);

	return threads[current_thread].stack_pointer;

	//return sp;
}

/*
void join_thread(struct thread mythread){
	while(mythread.state = "not dead")
}*/
