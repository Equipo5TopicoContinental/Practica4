/*
 * Buttons.c
 *
 *  Created on: Apr 19, 2016
 *      Author: Adrian
 */

#include "derivative.h"
#include "Buttons.h"
#include "Player_Fsm.h"

#define ticks_per_call 5
#define debounce_ticks 15

#define longpush_ticks 600



#define GPIO_PIN_MASK            0x1Fu
#define GPIO_PIN(x)              (((1)<<(x & GPIO_PIN_MASK)))


/*IRQ_NONE	
0x0. no documentation

IRQ_DMA_RISING	
0x1. no documentation

IRQ_DMA_FALLING	
0x2. no documentation

IRQ_DMA_EITHER	
0x3. no documentation

IRQ_ZERO	
0x8. no documentation

IRQ_RISING	
0x9. no documentation

IRQ_FALLING	
0xa. no documentation

IRQ_EITHER	
0xb. no documentation

IRQ_ONE	
0xc. no documentation

 * 
 * 
 * 
 * */
void InitButtons(void){
	/* Configure pin as input */
	/* GPIOB_PDDR: PDD&=~0x0100 */ //Port 8
	/* GPIOB_PDDR: PDD&=~0x0200 */ //Port 9
	GPIOB_PDDR &= (uint32_t)~(uint32_t)(GPIO_PDDR_PDD(
			GPIO_PIN(9)| 
			GPIO_PIN(8)| 
			GPIO_PIN(10) | 
			GPIO_PIN(11)));

	/* Initialization of Port Control register */
	/* PORTB_PCR8: ISF=0,MUX=1 */
	PORTB_PCR8 = (uint32_t)((PORTB_PCR8 & (uint32_t)~(uint32_t)(
			PORT_PCR_ISF_MASK |
			PORT_PCR_MUX(0x06)
	)) | (uint32_t)(
			PORT_PCR_MUX(0x01)
	));
	PORTB_PCR9 = (uint32_t)((PORTB_PCR9 & (uint32_t)~(uint32_t)(
			PORT_PCR_ISF_MASK |
			PORT_PCR_MUX(0x06)
	)) | (uint32_t)(
			PORT_PCR_MUX(0x01)
	));
	PORTB_PCR10 = (uint32_t)((PORTB_PCR10 & (uint32_t)~(uint32_t)(
			PORT_PCR_ISF_MASK |
			PORT_PCR_MUX(0x06)
	)) | (uint32_t)(
			PORT_PCR_MUX(0x01)
	));
	PORTB_PCR11 = (uint32_t)((PORTB_PCR11 & (uint32_t)~(uint32_t)(
			PORT_PCR_ISF_MASK |
			PORT_PCR_MUX(0x06)
	)) | (uint32_t)(
			PORT_PCR_MUX(0x01)
	)) | PORT_PCR_IRQC(0xA);
}
/*
 * Play Button: PORT B PIN 8
 * */
T_BOOL PlayButtonState(void){
	return (T_BOOL)((GPIOB_PDIR & GPIO_PDIR_PDI(GPIO_PIN(8)))==0);
}

/*
 * Play Button: PORT B PIN 9
 * */
T_BOOL StopButtonState(void){
	return (T_BOOL)((GPIOB_PDIR & GPIO_PDIR_PDI(GPIO_PIN(9)))==0);
}

/*
 * Play Button: PORT B PIN 10
 * */
T_BOOL VolUpButtonState(void){
	return (T_BOOL)((GPIOB_PDIR & GPIO_PDIR_PDI(GPIO_PIN(10)))==0);
}

/*
 * Play Button: PORT B PIN 11
 * */
T_BOOL VolDownButtonState(void){
	return (T_BOOL)((GPIOB_PDIR & GPIO_PDIR_PDI(GPIO_PIN(11)))==0);
}



void SenseButtons(void){
	static T_ULONG playTicks = 0;
	static T_ULONG stopTicks = 0;
	static T_ULONG volUpTicks = 0;
	static T_ULONG volDownTicks = 0;
	static T_BOOL playActive=0,stopActive=0,volDownActive=0, volUpActive=0;


	if(PlayButtonState()){
		playTicks += ticks_per_call;
		if(playTicks > debounce_ticks)
			playActive=1;
		else{}
	}else if(playTicks >= debounce_ticks){
		if((stopActive + volDownActive + volUpActive) == 0 ){
			if(playTicks > longpush_ticks){
				//long push
				PlayPauseReq();
			}else{
				PlayPauseReq();
			}
		}else{
			//				More than one button pressed
		}
		playActive=0,stopActive=0,volDownActive=0, volUpActive=0;
		playTicks = 0; //Reset
	}else{
		playTicks = 0; //Reset
	}

	if(StopButtonState()){
		stopTicks += ticks_per_call;
		if(stopTicks >= debounce_ticks)
			stopActive=1;
		else{}
	}else if(stopTicks >= debounce_ticks){
		if((playActive + volDownActive + volUpActive) == 0){
			if(stopTicks > longpush_ticks){
				//long push
				StopReq();
			}else{
				//normal push
				StopReq();
			}
		}else{
			//				More than one button pressed
		}
		playActive=0,stopActive=0,volDownActive=0, volUpActive=0;
		stopTicks = 0; //Reset
	}else{
		stopTicks = 0; //Reset
	}

	if(VolUpButtonState()){
		volUpTicks += ticks_per_call;
		if(volUpTicks >= debounce_ticks)
			volUpActive=1;
		else{}
	}else if(volUpTicks >= debounce_ticks){
		if((playActive + volDownActive + stopActive) == 0){
			if(volUpTicks > longpush_ticks){
				//long push
				FwdReq();
			}else{
				//normal push
				VolUpReq();
			}
		}else{
			//				More than one button pressed
		}
		playActive=0,stopActive=0,volDownActive=0, volUpActive=0;
		volUpTicks = 0; //Reset
	}else{
		volUpTicks = 0; //Reset
	}

	if(VolDownButtonState()){
		volDownTicks += ticks_per_call;
		if(volDownTicks >= debounce_ticks)
			volDownActive=1;
		else{}
	}else if(volDownTicks >= debounce_ticks){
		if((playActive + stopActive + volUpActive) == 0){
			if(volDownTicks > longpush_ticks){
				//long push
				RwdReq();
			}else{
				//normal push
				VolDownReq();
			}
		}else{
			//				More than one button pressed
		}
		playActive=0,stopActive=0,volDownActive=0, volUpActive=0;
		volDownTicks = 0; //Reset
	}else{
		volDownTicks = 0; //Reset
	}


}
