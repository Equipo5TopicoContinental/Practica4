/*
 * Player_Fsm.c
 *
 *  Created on: Apr 19, 2016
 *      Author: Adrian
 */

#include "Player_Fsm.h"
#include "Player.h"

T_BOOL PlayPause=FALSE, Stop=FALSE, VolUp=FALSE, VolDown=FALSE, Fwd=FALSE, Rwd=FALSE;

void Player_Fsm(void);

void PlayPauseReq(void){
	PlayPause = TRUE;
	Player_Fsm();
}
void StopReq(void){
	Stop = TRUE;
	Player_Fsm();
}
void VolUpReq(void){
	VolUp = TRUE;
	Player_Fsm();
}
void VolDownReq(void){
	VolDown = TRUE;
	Player_Fsm();
}
void FwdReq(void){
	Fwd = TRUE;
	Player_Fsm();
}
void RwdReq(void){
	Rwd = TRUE;
	Player_Fsm();
}


void Player_Fsm(void){
	static E_PLAYER_STATE state = STOP;
	switch(state){
	case PLAY:
		if(TRUE==PlayPause){
			Player_Pause();
			state = PAUSE;
			PlayPause = FALSE;
		}else if(TRUE==Stop){
			Player_Stop();
			state = STOP;
			Stop = FALSE;
		}else if(TRUE==VolUp){
			Player_VolUp();
			state = PLAY;
			VolUp = FALSE;
		}else if(TRUE == VolDown){
			Player_VolDown();
			state = PLAY;
			VolDown = FALSE;
		}else if(TRUE == Fwd){
			Player_Fwd();
			state = PLAY;
			Fwd = FALSE;
		}else if(TRUE == Rwd){
			if (MAX_RWD_TIME > PlayerState.TrackTime){
				Player_Rwd();
			}else{
				Player_ResetTrack();
			}			
			Rwd = FALSE;
			state = PLAY;
		}else{}
		break;
	case PAUSE:
		if(TRUE == PlayPause){
			Player_Play();
			state = PLAY;
			PlayPause = FALSE;
		}else if(TRUE == Stop){
			Player_Stop();
			state = STOP;
			Stop = FALSE;
		}else if(TRUE==VolUp){
			Player_VolUp();
			state = PAUSE;
			VolUp = FALSE;
		}else if(TRUE == VolDown){
			Player_VolDown();
			state = PAUSE;
			VolDown = FALSE;
		}else if(TRUE == Fwd){
			Player_Fwd();
			state = PAUSE;
			Fwd = FALSE;
		}else if(TRUE == Rwd){
			if (MAX_RWD_TIME > PlayerState.TrackTime){
				Player_Rwd();
			}else{
				Player_ResetTrack();
			}			
			Rwd = FALSE;
			state = PAUSE;
		}else{}
		break;
	case STOP:
		if(TRUE == PlayPause){
			Player_Play();
			state = PLAY;
			PlayPause = FALSE;
		}else if(TRUE == Stop){
			Player_ResetPlaylist();
			state = STOP;
			Stop = FALSE;
		}else if(TRUE==VolUp){
			Player_VolUp();
			state = STOP;
			VolUp = FALSE;
		}else if(TRUE == VolDown){
			Player_VolDown();
			state = STOP;
			VolDown = FALSE;
		}else if(TRUE == Fwd){
			Player_Fwd();
			state = STOP;
			Fwd = FALSE;
		}else if(TRUE == Rwd){
			Player_Rwd();			
			state = STOP;
			Rwd = FALSE;
		}else{}
		
		break;
	default:
		Player_Init();
		break;
	}
	
}
