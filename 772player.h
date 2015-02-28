#include "Defines.h"
//By 772807886
struct JLM_Player : player
{
	virtual state play(
		size_t milisecond_left,
		const vector< state > & self_history,
		const vector< state > & opponent_history)
	{
		unsigned int num = self_history.size();
		if (num == 0)//1Rock is for Rookies
			return paper;


		else if (num == 1)//2
			return scissors;


		double r = 0, p = 0, s = 0;
		for (unsigned int i = 0; i < num; i++)
			switch (opponent_history[i])
		{
			case rock:r++; break;
			case paper:p++; break;
			case scissors:s++; break;
		}
		r /= num;
		p /= num;
		s /= num;


		if (r == p || r == s || p == s)
			if (r == 0)
				if (p == 0)
					return rock;
				else
					return scissors;
			else if (p == 0)
				return paper;


		if (opponent_history[num - 1] == opponent_history[num - 2])//3Double Run
			switch (opponent_history[num - 1])
		{
			case rock:return scissors;
			case paper:return rock;
			case scissors:return paper;
		}


		if (r >= 0.5)
			return paper;
		else if (p >= 0.5)
			return scissors;
		else if (s >= 0.5)
			return rock;


		if (opponent_history[num - 1] == rock && self_history[num - 1] != scissors)//5
			return scissors;
		else if (opponent_history[num - 1] == paper && self_history[num - 1] != rock)
			return rock;
		else if (opponent_history[num - 1] == scissors && self_history[num - 1] != paper)
			return paper;


		return paper;
	}
};