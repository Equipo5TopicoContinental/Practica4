/*
 * Player.h
 *
 *  Created on: Apr 19, 2016
 *      Author: Adrian
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include "stdtypedef.h"
#include "Player_Fsm.h"

#define ticks_per_call 5
#define MAX_RWD_TIME 5
#define MAX_VOL 10
#define MIN_VOL 2
#define NUM_TRACKS 5
#define MAX_TRACK_TIME 30
#define TICS_PER_SEC 1200


typedef enum {
	PLAY=0,
	PAUSE=1,
	STOP=2
} E_PLAYER_STATE;

typedef struct{
	E_PLAYER_STATE State;
	T_UBYTE Track;
	T_UBYTE Volume;
	T_UWORD TrackTime;
	T_ULONG Ticks;
} Player;

Player PlayerState;

void Player_Play(void);
void Player_Pause(void);
void Player_Stop(void);
void Player_VolUp(void);
void Player_VolDown(void);
void Player_Fwd(void);
void Player_Rwd(void);
void Player_ResetTrack(void);
void Player_Init(void);
void Player_ResetPlaylist(void);
void Player_Update(void);



#endif /* PLAYER_H_ */
