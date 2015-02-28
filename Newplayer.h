#include "Defines.h"
//by  ninsun 
int count(std::vector< state > vec, state val)
{
	static int co[4] = { 0, 0, 0, 0 };
	if (!vec.empty())co[vec.back()]++;
	return co[val];
	/*
	int _count = 0;
	std::vector<state>::iterator _i = vec.begin();
	while (_i != vec.end())
	{
		if (*_i == val)
		{
			++_count;
		}
		++_i;
	}

	return _count;
	*/
}

class NewPlayer : public player
{
public:
	state play(std::size_t milisecond_left, const std::vector<state> &self_history, const std::vector<state> &opponent_history)
	{
		srand(time(NULL));
		int _rockCount = count(opponent_history, rock);
		int _paperCount = count(opponent_history, paper);
		int _scissorsCount = count(opponent_history, scissors);
		if (_rockCount > _paperCount && _rockCount > _scissorsCount)
		{
			if (rand() % 100 < 18)
			{
				return rock;
			}
			else
			{
				return paper;
			}
		}
		else if (_paperCount > _rockCount && _paperCount > _scissorsCount)
		{
			if (rand() % 100 < 18)
			{
				return paper;
			}
			else
			{
				return scissors;
			}
		}
		else if (_scissorsCount > _rockCount && _scissorsCount > _paperCount)
		{
			if (rand() % 100 < 18)
			{
				return scissors;
			}
			else
			{
				return rock;
			}
		}
		else
		{
			return state(rand() % 3);
		}
	}
};