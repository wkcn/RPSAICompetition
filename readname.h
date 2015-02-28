#include "Players.h"
string GetName(int i){
	switch (i)
	{
	case 0:
		return "JLM_Player";
	case 1:
		return "Do_the_same_as_the_opponent";
	case 2:
		return "Beat_the_opponent_last_move";
	case 3:
		return "Beat_the_opponent_last_time";
	case 4:
		return "EasyAI";
	case 5:
		return "EasyAI2";
	case 6:
		return "EasyAI3";
	case 7:
		return "EasyAI4";
	case 8:
		return "EasyAI4_1";
	case 9:
		return "EasyAI4_2";
	case 10:
		return "daze_player";
	case 11:
		return "NoloopPlayer";
	case 12:
		return "MarkovPlayer";
	case 13:
		return "MarkovPlayer2";
	case 14:
		return "mirai_player";
	case 15:
		return "NewPlayer";
	case 16:
		return "PersonificationPlayer";
	case 17:
		return "zzRetarded";
	case 18:
		return "rock_player";
	case 19:
		return "paper_player";
	case 20:
		return "scissors_player";
	case 21:
		return "cycle_player";
	case 22:
		return "random_player";
	case 23:
		return "time_player";
	case 24:
		return "";

	default:
		break;
	}
}