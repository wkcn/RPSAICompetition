#include "Defines.h"
struct PersonificationPlayer : player
{
	virtual state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history)
	{
		if (opponent_history.size() <= 3)
		{
			return Translate(rand() % 3);
		}
		else
		{
			vector<size_t> arr;
			arr.push_back(0);
			arr.push_back(0);
			arr.push_back(0);
			arr.push_back(0);
			for (state a : opponent_history)
			{
				++arr[a];
			}
			int i = fmax(arr);
			if (i == -1)
			{
				if (opponent_history.size() <= 9)
				{
					return Translate(rand() % 3);
				}
				else
				{
					size_t L = opponent_history.size() / 10 * 3;
					vector<size_t> arr2;
					arr2.push_back(0);
					arr2.push_back(0);
					arr2.push_back(0);
					arr2.push_back(0);
					for (; L != opponent_history.size(); ++L)
					{
						++arr2[opponent_history.at(L)];
					}
					int j = fmax(arr2);
					return Translate(fswitch(j));
				}
			}
			else
			{
				return Translate(fswitch(i));
			}
		}
	}

	virtual ~PersonificationPlayer() { }
	int fmax(vector<size_t> &arr)
	{
		vector<size_t> a = arr;
		sort(a.begin(), a.end());
		if (a.at(3) == a.at(2))
		{
			return -1;
		}
		for (size_t i = 0; i != 4; ++i)
		{
			if (arr.at(i) == a.at(3))
			{
				return i;
			}
		}
		return 3;
	}

	int fswitch(size_t i)
	{
		switch (i)
		{
		case 0:
			return 1;
			break;
		case 1:
			return 2;
			break;
		case 2:
			return 0;
			break;
		case 3:
			return Translate(rand() % 3);
			break;
		}
		return 3;
	}

	state Translate(size_t i)
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