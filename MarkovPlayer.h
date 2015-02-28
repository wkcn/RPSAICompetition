#include "Defines.h"
//by BZ___
struct MarkovPlayer2 : player
{
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history)
	{
		return(translate((int)decide_markov_3_2(self_history, opponent_history)));
	}


	float decide_markov_3_2(const std::vector<state>& self, const std::vector<state>& opponent)
	{
		long moves[4096] = { 0 };
		long s = opponent.size();
		if (s < 30)
		{
			return(rand() % 3);
		}
		for (vector<int>::size_type a = 4; a < opponent.size(); a = a + 1)
		{
			++moves[opponent.at(a - 4) * 1024 + self.at(a - 3) * 256 + opponent.at(a - 3) * 64 + opponent.at(a - 2) * 16 + self.at(a - 2) * 4 + opponent.at(a - 1)];
		}
		long times_rock = moves[opponent.at(s - 3) * 1024 + self.at(s - 2) * 256 + opponent.at(s - 2) * 64 + opponent.at(s - 1) * 16 + self.at(s - 1) * 4 + 0];
		long times_paper = moves[opponent.at(s - 3) * 1024 + self.at(s - 2) * 256 + opponent.at(s - 2) * 64 + opponent.at(s - 1) * 16 + self.at(s - 1) * 4 + 1];
		long times_scissors = moves[opponent.at(s - 3) * 1024 + self.at(s - 2) * 256 + opponent.at(s - 2) * 64 + opponent.at(s - 1) * 16 + self.at(s - 1) * 4 + 2];
		float prob_rock = (float)times_rock / opponent.size();
		float prob_paper = (float)times_paper / opponent.size();
		float prob_scissors = (float)times_scissors / opponent.size();
		return(decide_expectation(prob_rock, prob_paper, prob_scissors));
	}


	float decide_expectation(float prob_rock, float prob_paper, float prob_scissors)
	{
		float self_win_rock = prob_scissors - prob_paper;
		float self_win_paper = prob_rock - prob_scissors;
		float self_win_scissors = prob_paper - prob_rock;
		if ((self_win_rock >= self_win_paper) && (self_win_rock >= self_win_scissors))
			return(0 + self_win_rock);
		if ((self_win_paper >= self_win_rock) && (self_win_paper >= self_win_scissors))
			return(1 + self_win_paper);
		if ((self_win_scissors >= self_win_paper) && (self_win_scissors >= self_win_rock))
			return(2 + self_win_scissors);
	}

	state translate(int i)
	{
		switch (i)
		{
		case 0:
			return rock;
			break;
		case 1:
			return paper;
			break;
		case 2:
			return scissors;
			break;
		case 3:
			return blank;
			break;
		}
		return blank;
	}
};
struct MarkovPlayer : player
{
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history)
	{
		return(translate((int)decide_markov_3_2(self_history, opponent_history)));
	}


	float decide_markov_3_2(const vector<state>& self, const vector<state>& opponent)
	{
		int moves[7290] = { 0 };
		int s = opponent.size();
		if (s < 30)
		{
			srand(rand() * 53);
			return(rand() % 3);
		}
		for (vector<int>::size_type a = 4; a < opponent.size(); a = a + 1)
		{
			++moves[opponent.at(a - 4) * 243 + self.at(a - 3) * 81 + opponent.at(a - 3) * 27 + opponent.at(a - 2) * 9 + self.at(a - 2) * 3 + opponent.at(a - 1)];
		}
		int times_rock = moves[opponent.at(s - 3) * 243 + self.at(s - 2) * 81 + opponent.at(s - 2) * 27 + opponent.at(s - 1) * 9 + self.at(s - 1) * 3 + 0];
		int times_paper = moves[opponent.at(s - 3) * 243 + self.at(s - 2) * 81 + opponent.at(s - 2) * 27 + opponent.at(s - 1) * 9 + self.at(s - 1) * 3 + 1];
		int times_scissors = moves[opponent.at(s - 3) * 243 + self.at(s - 2) * 81 + opponent.at(s - 2) * 27 + opponent.at(s - 1) * 9 + self.at(s - 1) * 3 + 2];
		float prob_rock = (float)times_rock / opponent.size();
		float prob_paper = (float)times_paper / opponent.size();
		float prob_scissors = (float)times_scissors / opponent.size();
		return(decide_expectation(prob_rock, prob_paper, prob_scissors));
	}


	float decide_expectation(float prob_rock, float prob_paper, float prob_scissors)//Ò»´ÎÆÚÍûµÃ·Ö
	{
		float self_win_rock = prob_scissors - prob_paper;
		float self_win_paper = prob_rock - prob_scissors;
		float self_win_scissors = prob_paper - prob_rock;
		if ((self_win_rock >= self_win_paper) && (self_win_rock >= self_win_scissors))
			return(0 + self_win_rock);
		if ((self_win_paper >= self_win_rock) && (self_win_paper >= self_win_scissors))
			return(1 + self_win_paper);
		if ((self_win_scissors >= self_win_paper) && (self_win_scissors >= self_win_rock))
			return(2 + self_win_scissors);
	}


	int win(int a)//Ó®µÄÅÐ¶¨
	{
		return((a + 1) % 3);
	}


	state translate(int i)
	{
		switch (i)
		{
		case 0:
			return rock;
			break;
		case 1:
			return paper;
			break;
		case 2:
			return scissors;
			break;
		case 3:
			return blank;
			break;
		}
		return blank;
	}
};
struct NoloopPlayer : player
{
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history)
	{
		return(translate((int)aperiodic(self_history, opponent_history)));
	}


	state aperiodic(const std::vector<state>& self, const std::vector<state>& opponent)
	{
		long s = opponent.size();
		int a = 0;
		int k = 0;
		while (s % 2 == 0&&k<100)
		{
			a = (a + 1) % 3;
			s = s / 2;
			k++;
		}
		return(translate(a));
	}

	state translate(int i)
	{
		switch (i)
		{
		case 0:
			return rock;
			break;
		case 1:
			return paper;
			break;
		case 2:
			return scissors;
			break;
		case 3:
			return blank;
			break;
		}
		return blank;
	}
};