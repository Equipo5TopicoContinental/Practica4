/*
 * UartFsm.c
 *
 *  Created on: Apr 28, 2016
 *      Author: agonzalez
 */
#include "UartFsm.h"
#include "stdtypedef.h"
#include "RGB_LEDs.h"

#define CMD 0x26
#define EQU 0x66
#define Album 0x44

#define Play 0x00
#define Pause 0x01
#define Stop 0x02
#define Fw 0x03
#define Bw 0x04
#define Skip 0x05
#define Prev 0x06
#define Reserved 0x07

#define FUNCCMDMASK 0x07

T_UBYTE cmd_type, rub_func,rub_data,rub_checksum;

T_BOOL isValidCMD(T_UBYTE data){
	return (data==CMD || data == EQU || data == Album); 
}

T_BOOL isValidFuncCMD(T_UBYTE data){
	T_UBYTE masked = data&FUNCCMDMASK;
	return (masked == Play || masked == Pause || masked == Stop || masked == Fw
			|| masked == Bw || masked == Skip || masked == Prev);
}
T_UBYTE cmd_type;

void sendCommand(T_UBYTE cmd, T_UBYTE func){
	
}

void uart_fsm(void){
	T_UBYTE lub_state=CmdRqst;
	blue_toggle();
	switch(lub_state){
	case CmdRqst:		
		if(isValidCMD(rub_data)){
			cmd_type = rub_data;
			lub_state = FunctionalityRqst;
			
		}else{
			lub_state = CmdRqst;
		}
		break;
	case FunctionalityRqst:		
		if(cmd_type == CMD && isValidFuncCMD(rub_data)){
			rub_func = rub_data;
			lub_state=ChecksumRqst;
		}else if(cmd_type == EQU){
			rub_func = rub_data;
			lub_state=ChecksumRqst;
		}else if(cmd_type == Album){
			rub_func = rub_data;
			lub_state=ChecksumRqst;
		}else{
			lub_state = CmdRqst;
		}
		break;
	case ChecksumRqst:
		rub_checksum = rub_data;
		if( (cmd_type ^ rub_func)  == rub_checksum ){
			lub_state = Exec;
			uart_fsm();
		}
		break;
	case Exec:
		sendCommand(cmd_type,rub_func);
		lub_state=CmdRqst;
		break;
	default:
		lub_state=CmdRqst;
		break;
	}
	
}

#if UART_MODE == INTERRUPT
void UART0_IRQHandler (void)
{
  char c = 0;
  if (UART0_S1&UART_S1_RDRF_MASK)
  {
    c = UART0_D;
    rub_data = c;
    uart_fsm();
    if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))
    {
    	UART0_D  = c;
    }
  }
}
#endif
