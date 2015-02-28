#include "Defines.h"

struct Do_the_same_as_the_opponent : player
{
	state s;
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history)
	{
		if (opponent_history.size() <= 3)
		{
			return state(1);
		}
		else
		{
			return state((opponent_history[opponent_history.size() - 1]));
		}
	}
};
struct Beat_the_opponent_last_move : player
{
	state s;
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history)
	{
		if (opponent_history.size() <= 3)
		{
			return state(1);
		}
		else
		{
			return state((opponent_history[opponent_history.size() - 1] + 1) % 3);
		}
	}
};

struct Beat_the_opponent_last_time : player
{
	state s;
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history)
	{
		if (opponent_history.size() <= 3)
		{
			return state(1);
		}
		else
		{
			return state((opponent_history[opponent_history.size() - 2] + 1) % 3);
		}
	}
};

struct EasyAI : player
{
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history)
	{
		int num = opponent_history.size();

		if (num <= 19) return rock;
		if (num <= 39) return scissors;
		if (num <= 59) return paper;

		state best;
		int i, decide1, decide2, decide3;
		decide1 = decide2 = decide3 = 0;
		for (i = num - 51; i < num; i++)
		{
			if (opponent_history[i] == self_history[i - 1]) decide1++;
			if (opponent_history[i] == beat(self_history[i - 1]))decide2++;
			if (beat(opponent_history[i]) == self_history[i - 1])decide3++;
		}
		if (decide1 >= decide2&&decide1 >= decide3)
			return beat(self_history[num - 1]);

		if (decide2 >= decide1&&decide2 >= decide3)
			return beat(beat(self_history[num - 1]));

		return self_history[num - 1];
	};
	state beat(state x)
	{
		switch (x)
		{
		case scissors:
			return rock; break;

		case rock:
			return paper; break;

		case paper:
			return scissors; break;
		}
		return rock;
	}
};

struct EasyAI2 : player
{
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history)
	{
		int num = opponent_history.size();

		if (num < 5) return rock;
		if (num < 10) return scissors;
		if (num < 15) return paper;

		int i, decide1, decide2, decide3;
		int decide4, decide5, decide6;
		int best;
		decide1 = decide2 = decide3 = 0;
		decide4 = decide5 = decide6 = 0;
		for (i = num - 51; i < num; i++)
		{
			if (i < 3) i = 3;
			if (opponent_history[i] == self_history[i - 1]) decide1++;
			if (opponent_history[i] == beat(self_history[i - 1]))decide2++;
			if (beat(opponent_history[i]) == self_history[i - 1])decide3++;
			if (opponent_history[i] == opponent_history[i - 1]) decide4++;
			if (opponent_history[i] == beat(opponent_history[i - 1]))decide5++;
			if (beat(opponent_history[i]) == opponent_history[i - 1])decide6++;
		}
		best = 0;
		if (best < decide1) best = decide1;
		if (best < decide2) best = decide2;
		if (best < decide3) best = decide3;
		if (best < decide4) best = decide4;
		if (best < decide5) best = decide5;
		if (best < decide6) best = decide6;

		if (best == decide1)
			return beat(self_history[num - 1]);
		if (best == decide2)
			return beat(beat(self_history[num - 1]));
		if (best == decide3)
			return self_history[num - 1];
		if (best == decide4)
			return beat(opponent_history[num - 1]);
		if (best == decide5)
			return beat(beat(opponent_history[num - 1]));
		if (best == decide6)
			return opponent_history[num - 1];


	};
	state beat(state x)
	{
		switch (x)
		{
		case scissors:
			return rock; break;

		case rock:
			return paper; break;

		case paper:
			return scissors; break;

		case blank:
			return rock; break;
		}
		return rock;
	}
};

struct EasyAI3 :public player
{
	virtual state play(std::size_t milisecond_left,
		const std::vector < state > &self_history,
		const std::vector < state > &opponent_history)
	{
		int num = opponent_history.size();
		if (num < 3) return out((rand() + rand()) % 3);

		int i, decide1, decide2, decide3;
		int decide4, decide5, decide6;
		int best;
		decide1 = decide2 = decide3 = 0;
		decide4 = decide5 = decide6 = 0;
		best = 0;
		for (i = num - 30; i < num; i++)
		{
			if (i < 1) i = 1;
			if (opponent_history[i] == self_history[i - 1])          decide1++;
			if (opponent_history[i] == beat(self_history[i - 1]))    decide2++;
			if (beat(opponent_history[i]) == self_history[i - 1])    decide3++;
			if (opponent_history[i] == opponent_history[i - 1])      decide4++;
			if (opponent_history[i] == beat(opponent_history[i - 1]))decide5++;
			if (beat(opponent_history[i]) == opponent_history[i - 1])decide6++;
		}

		if (best < decide1)best = decide1;
		if (best < decide2)best = decide2;
		if (best < decide3)best = decide3;
		if (best < decide4)best = decide4;
		if (best < decide5)best = decide5;
		if (best < decide6)best = decide6;

		if (best < 16 && num > 30)
		{
			return out((rand() + rand()) % 3);
		}

		if (best == decide1)
			return beat(self_history[num - 1]);
		if (best == decide2)
			return beat(beat(self_history[num - 1]));
		if (best == decide3)
			return self_history[num - 1];
		if (best == decide4)
			return beat(opponent_history[num - 1]);
		if (best == decide5)
			return beat(beat(opponent_history[num - 1]));
		if (best == decide6)
			return opponent_history[num - 1];

	};
	state out(int x)
	{
		switch (x)
		{
		case 0:return rock;    break;
		case 1:return paper;   break;
		case 2:return scissors; break;
		case 3:return rock;    break;
		}
		return rock;
	}
	state beat(state x)
	{
		switch (x)
		{
		case scissors:return rock;    break;
		case rock:    return paper;   break;
		case paper:   return scissors; break;
		case blank:   return rock;    break;
		}
		return rock;
	}
};

struct EasyAI4 :public player
{
	virtual state play(std::size_t milisecond_left,
		const std::vector < state > &self_history,
		const std::vector < state > &opponent_history)
	{
		int num = opponent_history.size();
		if (num < 3) return out((rand() + rand()) % 3);
		int i, loop;

		for (loop = 5; loop <= 100; loop++)
		{
			if (num > loop + loop)
			{
				for (i = 1; i <= loop; i++)
				{
					if (opponent_history[num - i] != opponent_history[num - loop - i]) break;
				}
				if (i > loop)
				{
					return opponent_history[num - loop];
				}
			}
		}

		int decide1, decide2, decide3;
		int decide4, decide5, decide6;
		int best;
		decide1 = decide2 = decide3 = 0;
		decide4 = decide5 = decide6 = 0;
		best = 0;
		for (i = num - 30; i < num; i++)
		{
			if (i < 1) i = 1;
			if (opponent_history[i] == self_history[i - 1])          decide1++;
			if (opponent_history[i] == beat(self_history[i - 1]))    decide2++;
			if (beat(opponent_history[i]) == self_history[i - 1])    decide3++;
			if (opponent_history[i] == opponent_history[i - 1])      decide4++;
			if (opponent_history[i] == beat(opponent_history[i - 1]))decide5++;
			if (beat(opponent_history[i]) == opponent_history[i - 1])decide6++;
		}

		if (best < decide1)best = decide1;
		if (best < decide2)best = decide2;
		if (best < decide3)best = decide3;
		if (best < decide4)best = decide4;
		if (best < decide5)best = decide5;
		if (best < decide6)best = decide6;

		if (best < 15 && num > 30)
		{
			return out((rand() + rand()) % 3);
		}

		if (best == decide1)
			return beat(self_history[num - 1]);
		if (best == decide2)
			return beat(beat(self_history[num - 1]));
		if (best == decide3)
			return self_history[num - 1];
		if (best == decide4)
			return beat(opponent_history[num - 1]);
		if (best == decide5)
			return beat(beat(opponent_history[num - 1]));
		if (best == decide6)
			return opponent_history[num - 1];

	};
	state out(int x)
	{
		switch (x)
		{
		case 0:return rock;    break;
		case 1:return paper;   break;
		case 2:return scissors; break;
		case 3:return rock;    break;
		}
		return rock;
	}
	state beat(state x)
	{
		switch (x)
		{
		case scissors:return rock;    break;
		case rock:    return paper;   break;
		case paper:   return scissors; break;
		case blank:   return rock;    break;
		}
		return rock;
	}
};

struct EasyAI4_1 :player
{
	virtual state play(std::size_t milisecond_left,
		const std::vector < state > &self_history,
		const std::vector < state > &opponent_history)
	{
		int num = opponent_history.size();
		if (num < 3) return out((rand() + rand()) % 3);
		int i, loop;

		for (loop = 5; loop <= 100; loop++)
		{
			if (num > loop + loop)
			{
				for (i = 1; i <= loop; i++)
				{
					if (opponent_history[num - i] != opponent_history[num - loop - i]) break;
				}
				if (i > loop)
				{
					return beat(opponent_history[num - loop]);
				}
			}
		}

		int decide1, decide2, decide3;
		int decide4, decide5, decide6;
		int best;
		decide1 = decide2 = decide3 = 0;
		decide4 = decide5 = decide6 = 0;
		best = 0;
		for (i = num - 30; i < num; i++)
		{
			if (i < 1) i = 1;
			if (opponent_history[i] == self_history[i - 1])          decide1++;
			if (opponent_history[i] == beat(self_history[i - 1]))    decide2++;
			if (beat(opponent_history[i]) == self_history[i - 1])    decide3++;
			if (opponent_history[i] == opponent_history[i - 1])      decide4++;
			if (opponent_history[i] == beat(opponent_history[i - 1]))decide5++;
			if (beat(opponent_history[i]) == opponent_history[i - 1])decide6++;
		}

		if (best < decide1)best = decide1;
		if (best < decide2)best = decide2;
		if (best < decide3)best = decide3;
		if (best < decide4)best = decide4;
		if (best < decide5)best = decide5;
		if (best < decide6)best = decide6;

		if (best < 15 && num > 30)
		{
			return out((rand() + rand()) % 3);
		}

		if (best == decide1)
			return beat(self_history[num - 1]);
		if (best == decide2)
			return beat(beat(self_history[num - 1]));
		if (best == decide3)
			return self_history[num - 1];
		if (best == decide4)
			return beat(opponent_history[num - 1]);
		if (best == decide5)
			return beat(beat(opponent_history[num - 1]));
		if (best == decide6)
			return opponent_history[num - 1];

	};
	state out(int x)
	{
		switch (x)
		{
		case 0:return rock;    break;
		case 1:return paper;   break;
		case 2:return scissors; break;
		case 3:return rock;    break;
		}
		return rock;
	}
	state beat(state x)
	{
		switch (x)
		{
		case scissors:return rock;    break;
		case rock:    return paper;   break;
		case paper:   return scissors; break;
		case blank:   return rock;    break;
		}
		return rock;
	}
};

struct EasyAI4_2 :player
{
	virtual state play(std::size_t milisecond_left,
		const std::vector < state > &self_history,
		const std::vector < state > &opponent_history)
	{
		int num = opponent_history.size();
		if (num < 3) return out((rand() + rand()) % 3);
		int i, loop;

		for (loop = 4; loop <= 100; loop++)
		{
			if (num > loop + loop)
			{
				for (i = 1; i <= loop; i++)
				{
					if (opponent_history[num - i] != opponent_history[num - loop - i]) break;
				}
				if (i > loop)
				{
					return beat(opponent_history[num - loop]);
				}
			}
		}

		int decide1, decide2, decide3;
		int decide4, decide5, decide6;
		int best;
		decide1 = decide2 = decide3 = 0;
		decide4 = decide5 = decide6 = 0;
		best = 0;
		for (i = num - 30; i < num; i++)
		{
			if (i < 1) i = 1;
			if (opponent_history[i] == self_history[i - 1])          decide1++;
			if (opponent_history[i] == beat(self_history[i - 1]))    decide2++;
			if (beat(opponent_history[i]) == self_history[i - 1])    decide3++;
			if (opponent_history[i] == opponent_history[i - 1])      decide4++;
			if (opponent_history[i] == beat(opponent_history[i - 1]))decide5++;
			if (beat(opponent_history[i]) == opponent_history[i - 1])decide6++;
		}

		if (best < decide1)best = decide1;
		if (best < decide2)best = decide2;
		if (best < decide3)best = decide3;
		if (best < decide4)best = decide4;
		if (best < decide5)best = decide5;
		if (best < decide6)best = decide6;

		if (best < 16 && num > 30)
		{
			return out((rand() + rand()) % 3);
		}

		if (best == decide1)
			return beat(self_history[num - 1]);
		if (best == decide2)
			return beat(beat(self_history[num - 1]));
		if (best == decide3)
			return self_history[num - 1];
		if (best == decide4)
			return beat(opponent_history[num - 1]);
		if (best == decide5)
			return beat(beat(opponent_history[num - 1]));
		if (best == decide6)
			return opponent_history[num - 1];

	};
	state out(int x)
	{
		switch (x)
		{
		case 0:return rock;    break;
		case 1:return paper;   break;
		case 2:return scissors; break;
		case 3:return rock;    break;
		}
		return rock;
	}
	state beat(state x)
	{
		switch (x)
		{
		case scissors:return rock;    break;
		case rock:    return paper;   break;
		case paper:   return scissors; break;
		case blank:   return rock;    break;
		}
		return rock;
	}
};
