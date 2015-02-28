#include "Players.h"
player * GetPlayer(int i){
	switch (i)
	{
	case 0:
		return new JLM_Player;
	case 1:
		return new Do_the_same_as_the_opponent;
	case 2:
		return new Beat_the_opponent_last_move;
	case 3:
		return new Beat_the_opponent_last_time;
	case 4:
		return new EasyAI;
	case 5:
		return new EasyAI2;
	case 6:
		return new EasyAI3;
	case 7:
		return new EasyAI4;
	case 8:
		return new EasyAI4_1;
	case 9:
		return new EasyAI4_2;
	case 10:
		return new daze_player;
	case 11:
		return new NoloopPlayer;
	case 12:
		return new MarkovPlayer;
	case 13:
		return new MarkovPlayer2;
	case 14:
		return new mirai_player;
	case 15:
		return new NewPlayer;
	case 16:
		return new PersonificationPlayer;
	case 17:
		return new zzRetarded;
	case 18:
		return new rock_player;
	case 19:
		return new paper_player;
	case 20:
		return new scissors_player;
	case 21:
		return new cycle_player;
	case 22:
		return new random_player;
	case 23:
		return new time_player;
	default:
		break;
	}
}