#ifndef PLAYERS_H
#define PLAYERS_H

#include "Defines.h"

struct rock_player : player
{
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history) { return rock; }
};

struct paper_player : player
{
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history) { return paper; }
};

struct scissors_player : player
{
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history) { return scissors; }
};

struct cycle_player : player
{
	state s;
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history)
	{
		s = state((s + 1) % 3);
		return s;

	}
	cycle_player(){
		s = state(0);
	}
};

struct random_player : player
{
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history) { return state(rand()%3); }
};

struct time_player : player
{
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history)
	{
		time_t t = time(0);
		t++;
		srand(unsigned int(t));
		return state(rand() % 3);
	}
};


#include "MarkovPlayer.h"
#include "772player.h"
#include "AlneysPlayer.h"
#include "dazeplayer.h"
#include "miraiPlayer.h"
#include "Newplayer.h"
#include "zzPlayer.h"
#include "PersonificationPlayer.h"

#endif