#include "main.h"

volatile unsigned int sys_tick_counter = 0;

void WatchDog_cfg(void);

int main(void)
{
#if UART_MODE == INTERRUPT	
	int counter = 0;

	put("\r\nHello World! UART Lab using Interrupt mode\r\n");

	EnableInterrupts;
	enable_irq(INT_UART0 -16);
	set_irq_priority((INT_UART0 -16), 2);
/*
	while(TRUE)
	{
		counter++;
		if(counter >= DLY)
		{
			//GREEN_TOGGLE;
			counter = 0;
		}
	}*/
#else
	char ch;

	put("\r\nHello World! UART Lab using Polling mode\r\n");

	while(TRUE)
	{
		ch = in_char();
		out_char(ch);
		BLUE_TOGGLE;
	}
#endif

	/* Disable Watch Dog */
	WatchDog_cfg();
	/* initialize clock system for 48 MHz */
	InitClock(); 
	/* Configure the timer and the interrupt to be used to generate the tick of the scheduler */
	InitSysTick();
	/* Scheduler Initialization and tasks initialization  */
	gsc_sch_core_Init();
	/* Execute Scheduler */
	gsc_sch_core_exec();


	return 0;
}

/*
 * Init watch dog
 */
void WatchDog_cfg(void)
{
	 /* Disable watch dog */
	 SIM_COPC |= SIM_COPC_COPT(0);
}

void SysTick_Handler(void)
{
	sys_tick_counter++;
	gsc_sch_core_tick_isr();
}
