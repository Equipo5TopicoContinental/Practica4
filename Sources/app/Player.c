/*
 * Player.c
 *
 *  Created on: Apr 19, 2016
 *      Author: Adrian
 */

#include "Player.h"
#include "stdtypedef.h"
#include "RGB_LEDs.h"
#include "string.h"
#include "../Common/libs.h"

COLOR tracks[NUM_TRACKS][MAX_TRACK_TIME] = {
		{ LED_RED, LED_YELLOW, LED_GREEN, LED_RED, LED_YELLOW, LED_GREEN, LED_RED, LED_YELLOW, LED_GREEN, LED_RED, LED_YELLOW, LED_GREEN, LED_RED, LED_YELLOW, LED_GREEN, LED_RED, LED_YELLOW, LED_GREEN, LED_RED, LED_YELLOW, LED_GREEN, LED_RED, LED_YELLOW, LED_GREEN, LED_RED, LED_YELLOW, LED_GREEN, LED_RED, LED_YELLOW, LED_WHITE},
		{ LED_BLUE, LED_CYAN, LED_MAGENTA, LED_WHITE, LED_BLUE, LED_CYAN, LED_MAGENTA, LED_WHITE, LED_BLUE, LED_CYAN, LED_MAGENTA, LED_WHITE, LED_BLUE, LED_CYAN, LED_MAGENTA, LED_WHITE, LED_BLUE, LED_CYAN, LED_MAGENTA, LED_WHITE, LED_BLUE, LED_CYAN, LED_MAGENTA, LED_WHITE, LED_BLUE, LED_CYAN, LED_MAGENTA, LED_WHITE, LED_CYAN, LED_MAGENTA},
		{ LED_YELLOW, LED_CYAN, LED_RED, LED_MAGENTA, LED_YELLOW, LED_GREEN, LED_BLUE, LED_CYAN, LED_RED, LED_MAGENTA, LED_YELLOW, LED_GREEN, LED_BLUE, LED_CYAN, LED_RED, LED_MAGENTA, LED_YELLOW, LED_GREEN, LED_BLUE, LED_CYAN, LED_RED, LED_MAGENTA, LED_YELLOW, LED_GREEN, LED_BLUE, LED_CYAN, LED_RED, LED_MAGENTA, LED_YELLOW, LED_GREEN},
		{ LED_GREEN, LED_WHITE, LED_RED, LED_CYAN, LED_YELLOW, LED_BLUE, LED_WHITE, LED_RED, LED_CYAN, LED_YELLOW, LED_BLUE, LED_WHITE, LED_RED, LED_CYAN, LED_YELLOW, LED_BLUE, LED_WHITE, LED_RED, LED_CYAN, LED_YELLOW, LED_BLUE, LED_WHITE, LED_RED, LED_CYAN, LED_YELLOW, LED_BLUE, LED_WHITE, LED_RED, LED_CYAN, LED_YELLOW},
		{LED_WHITE, LED_YELLOW, LED_CYAN, LED_BLUE, LED_GREEN, LED_MAGENTA, LED_RED, LED_WHITE, LED_YELLOW, LED_CYAN, LED_BLUE, LED_GREEN, LED_MAGENTA, LED_RED, LED_WHITE, LED_YELLOW, LED_CYAN, LED_BLUE, LED_GREEN, LED_MAGENTA, LED_RED, LED_WHITE, LED_YELLOW, LED_CYAN, LED_BLUE, LED_GREEN, LED_MAGENTA, LED_RED, LED_MAGENTA, LED_GREEN}
};


void Player_Play(void){
	PlayerState.State = PLAY;
}
void Player_Pause(void){
	PlayerState.State = PAUSE;
}
void Player_Stop(void){
	PlayerState.State = STOP;
	PlayerState.Ticks = 0;
	PlayerState.TrackTime = 0;
}
void Player_VolUp(void){
	if(PlayerState.Volume < MAX_VOL)
	{
		PlayerState.Volume++;
	}else{}

}
void Player_VolDown(void){
	if(PlayerState.Volume > MIN_VOL){
		PlayerState.Volume--;
	}else{}
}
void Player_Fwd(void){
	PlayerState.Track++;
	PlayerState.Track %= NUM_TRACKS;
	PlayerState.Ticks = 0;
	PlayerState.TrackTime = 0;
}
void Player_Rwd(void){
	if(PlayerState.Track == 0){
		PlayerState.Track = NUM_TRACKS-1;
	}else{
		PlayerState.Track--;
		PlayerState.Track %= NUM_TRACKS;
	}

	PlayerState.Ticks = 0;
	PlayerState.TrackTime = 0;
}
void Player_ResetTrack(void){
	PlayerState.Ticks = 0;
	PlayerState.TrackTime = 0;
}
void Player_Init(void){
	PlayerState.Track=0;
	PlayerState.Ticks = 0;
	PlayerState.TrackTime = 0;
	PlayerState.Volume = 5;
	PlayerState.State = STOP;
}
void Player_ResetPlaylist(void){
	PlayerState.Track=0;
}
void Player_Update(void){
	COLOR c;
	if(PlayerState.State == PLAY){
		PlayerState.Ticks += ticks_per_call;
		PlayerState.TrackTime = PlayerState.Ticks / TICS_PER_SEC;
		if(PlayerState.TrackTime>= MAX_TRACK_TIME){
			Player_Fwd();
		}
		//Show color
		c = tracks[PlayerState.Track][PlayerState.TrackTime % MAX_TRACK_TIME];
		set_color(c,PlayerState.Volume);

	}else if(PlayerState.State == STOP){
		//LEdsOFF
		leds_off();
	}else if(PlayerState.State == PAUSE){
		//Show color
		c = tracks[PlayerState.Track][PlayerState.TrackTime % MAX_TRACK_TIME];
		set_color(c,PlayerState.Volume);
	}else{

	}


}

void Player_SendStatus(void){
	put("#");
	put("Estado:");
	switch(PlayerState.State){
	case PLAY:
		put("Play");
		break;
	case PAUSE:
		put("Pause");
		break;
	case STOP:
		put("Stop");
		break;
	}
	put(",Track:");
	char num[3];
	num[0] ='0'+ PlayerState.Track / 10;
	num[1] = '0' + PlayerState.Track % 10;
	num[2] = '\0';
	put(num);
	put(",Vol:");
	num[0] ='0'+ PlayerState.Volume / 10;
		num[1] = '0' + PlayerState.Volume % 10;
		put(num);
	put("\n");
	//sprintf(buff,"Track: %d",PlayerState.Track);
	//put(buff);
}
	
