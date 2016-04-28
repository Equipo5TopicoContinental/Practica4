/*
 * UartFsm.h
 *
 *  Created on: Apr 28, 2016
 *      Author: agonzalez
 */

#ifndef UARTFSM_H_
#define UARTFSM_H_

typedef enum {
	Standby,
	CmdRqst,
	FunctionalityRqst,
	ChecksumRqst,
	Exec
}UART_FSM_STATE;


void uart_fsm(void);	

#endif /* UARTFSM_H_ */
