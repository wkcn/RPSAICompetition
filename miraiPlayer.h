#include "Defines.h"
#define MAX_MEMORY 5239
#define SHORT_MEMORY 20
// strategy

enum resultState { LOSE = 0, BALANCE = 1, WIN = 2 };

struct RecorderChild
{
	state Me;
	state You;
	void Set(state me, state you)
	{
		Me = me; You = you;
	}
};

state CorrectX(state s, int n)
{
	int i = s;
	i += n;
	int j = i / 3;
	i -= j * 3;
	while (i < 0)i += 3;
	while (i > 2)i -= 3;
	return state(i);
}

class Recorder
{
private:
	int pointer;
	bool full;
public:
	RecorderChild r[MAX_MEMORY];
	unsigned int MyRec[4];
	unsigned int YourRec[4];
	unsigned int MyShortRec[4];
	unsigned int YourShortRec[4];
	RecorderChild& Get(int id)
	{
		int p = pointer - id;
		if (p < 0)p += MAX_MEMORY;
		return r[p];
	}
	void Push(state me, state you)
	{
		pointer++;
		if (pointer == MAX_MEMORY)full = true;
		MyRec[me]++;	MyShortRec[me]++;
		YourRec[you]++;	YourShortRec[you]++;

		if (pointer > SHORT_MEMORY || full)
		{
			MyShortRec[Get(SHORT_MEMORY).Me]--;
			YourShortRec[Get(SHORT_MEMORY).You]--;
		}
		pointer %= MAX_MEMORY;
		r[pointer].Set(me, you);
	}
	Recorder() :pointer(-1), full(0){
		for (int i = 0; i < 4; i++)
		{
			MyRec[i] = 0;
			YourRec[i] = 0;
			MyShortRec[i] = 0;
			YourShortRec[i] = 0;
		}
	};
};
resultState Judge(state me, state you)
{
	if (me == you) return BALANCE;
	if (me == rock && you == paper) return LOSE;
	if (me == paper && you == scissors) return LOSE;
	if (me == scissors && you == rock) return LOSE;
	return WIN;
};
struct Step
{
	int step;//0~729
	int StepStandard(Recorder &w, int k = 0)
	{
		//int array[6] = {w.r[k+0].Me,w.r[k+0].You,w.r[k+1].Me,w.r[k+1].You,w.r[k+2].Me,w.r[k+2].You};
		RecorderChild &a = w.Get(k + 0);
		RecorderChild &b = w.Get(k + 1);
		RecorderChild &c = w.Get(k + 2);
		int array[6] = { a.Me, a.You, b.Me, b.You, c.Me, c.You };
		int o = array[0];
		int t = 1;
		step = 0;
		for (int i = 5; i >= 0; i--)
		{
			array[i] -= o;
			if (array[i] < 0)array[i] += 3;
			step += t * array[i];
			t *= 3; //3进制
		}
		return o;
	}
};

struct Strategy
{
	state hope[3];//按期望从高到低排序!!!

	Strategy()
	{
		hope[0] = rock;
		hope[1] = paper;
		hope[2] = scissors;
	}
	void Sort(unsigned int *rec)
	{
		int t[3] = { rec[0], rec[1], rec[2] };

		hope[0] = rock;
		hope[1] = paper;
		hope[2] = scissors;

		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3 - j; k++)
			{
				if (t[j] < t[k])
				{
					int o = t[j]; t[j] = t[k]; t[k] = o;
					state s = hope[j]; hope[j] = hope[k]; hope[k] = s;
				}
			}
		}

	}
	void Sort(int *rec)
	{
		int t[3] = { rec[0], rec[1], rec[2] };

		hope[0] = rock;
		hope[1] = paper;
		hope[2] = scissors;

		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3 - j; k++)
			{
				if (t[j] < t[k])
				{
					int o = t[j]; t[j] = t[k]; t[k] = o;
					state s = hope[j]; hope[j] = hope[k]; hope[k] = s;
				}
			}
		}

	}
	void Sort(short *rec)
	{
		int t[3] = { rec[0], rec[1], rec[2] };
		//ope[3] = {rock,paper,scissors};
		hope[0] = rock;
		hope[1] = paper;
		hope[2] = scissors;
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3 - j; k++)
			{
				if (t[j] < t[k])
				{
					int o = t[j]; t[j] = t[k]; t[k] = o;
					state s = hope[j]; hope[j] = hope[k]; hope[k] = s;
				}
			}
		}

	}
	void Solve()
	{
		for (int s = 0; s < 3; s++)
		{
			//hope[s]++;
			//if(hope[s]>2)hope[s]-=3;
			hope[s] = CorrectX(hope[s], 1);
		}
	}
	void Correct(int o)
	{
		for (int s = 0; s < 3; s++)
		{
			//hope[s]+=o;
			//if(hope[s]>2)hope[s]-=3;
			hope[s] = CorrectX(hope[s], o);
		}
	}
};
state protect(Strategy *s)//比较0与1
{
	return (Judge(state(s->hope[0]), state(s->hope[1])) == WIN) ? state(s->hope[0]) : state(s->hope[1]);
}

struct  mData
{
	//+3偏移
	int d[7];
	void Push(int o)
	{
		d[o + 3]++;
	}

	bool Available(int total)
	{
		int maxn = 0;
		int mid = 0;
		for (int i = 0; i < 7; i++)
		{
			if (mid < d[i])
			{
				if (maxn < d[i])
				{
					maxn = d[i];
				}
				else
				{
					mid = d[i];
				}

			}
		}

		return (((maxn - mid) > (total / 2)) || (maxn > total - 10));
	}
	int GetE()
	{
		int maxn = 0;
		for (int i = 0; i < 7; i++)
		{
			if (maxn < d[i])
			{
				maxn = d[i];
			}

		}
		return maxn;
	}
	int GetOffset()
	{
		int maxn = 0;
		int o;
		int mid = 0;
		for (int i = 0; i < 7; i++)
		{
			if (mid < d[i])
			{
				if (maxn < d[i])
				{
					maxn = d[i];
					o = i;
				}
				else
				{
					mid = d[i];
				}

			}
		}


		return o - 3;
	}
	mData()
	{
		for (int i = 0; i < 7; i++)
		{
			d[i] = 0;
		}
	}
};


struct expData
{
	state yourState;//对方状态
	bool balance;
	expData()
	{
		balance = true;
		yourState = blank;
	}
};

struct mirai_player : public player
{
	mData recData[2][3];

	int game;
	int cute;
	int val;

	Recorder recorder;
	Step stepTest;

	expData exp[730];//[3];
	state considerHope;

	state play(std::size_t milisecond_left, const std::vector< state > & self_history, const std::vector< state > & opponent_history)
	{

		//已进行局数，当前+1局
		game = self_history.size();

		if (game == 0){
			char mirai[16] = "I like Miku";
			return state((mirai[3] * mirai[9]) % 3);
		}

		if (cute != game - 1)
		{

			cute = game - 1;
			if (opponent_history[cute] != blank)
			{
				//记录上一局局势
				recorder.Push(self_history[cute], opponent_history[cute]);
				val++;

				state lastYou = opponent_history[cute];

				//模拟
				Strategy tempSt;
				tempSt.Sort(recorder.MyRec);
				recData[0][0].Push(lastYou - tempSt.hope[0]);
				recData[0][1].Push(lastYou - tempSt.hope[1]);
				recData[0][2].Push(lastYou - tempSt.hope[0]);

				tempSt.Sort(recorder.YourRec);

				recData[1][0].Push(lastYou - tempSt.hope[0]);
				recData[1][1].Push(lastYou - tempSt.hope[1]);
				recData[1][2].Push(lastYou - tempSt.hope[0]);

				//遍历寻找最优解
				int bx = 0, by = 0;
				int e = -1, teste;
				for (int x = 0; x < 2; x++)
				{
					for (int y = 0; y < 3; y++)
					{
						teste = recData[x][y].GetE();
						if (e < teste)
						{
							e = teste;
							bx = x; by = y;
						}
					}

				}

				//模拟当前状态
				if (recData[bx][by].Available(game))
				{
					Strategy hope;
					state otherthink;
					if (bx == 0)
					{
						hope.Sort(recorder.MyRec);

						otherthink = CorrectX(hope.hope[by], recData[bx][by].GetOffset() + 1);

					}
					else
					{

						hope.Sort(recorder.YourRec);

						otherthink = CorrectX(hope.hope[by], recData[bx][by].GetOffset() + 1);

					}
					considerHope = otherthink;
				}


				if (val > 3)
				{
					int o = stepTest.StepStandard(recorder, 1);

					resultState lastState = Judge(self_history[cute], opponent_history[cute]);

					state m = self_history[cute];

					m = CorrectX(m, -o);
					int step = stepTest.step;

					if (lastState == LOSE)
					{
						if (exp[step].balance)
						{
							exp[step].yourState = m;
							exp[step].balance = false;
						}
						else
						{
							exp[step].yourState = CorrectX(exp[step].yourState, 1);//弱一位
						}
					}

					if (lastState == BALANCE)
					{
						if (exp[step].balance)
						{
							//if (exp[step].yourState == blank)
							//{

							//}

							//exp[step].yourState = m;
							exp[step].yourState = CorrectX(m, -1);
						}
						else
						{
							//exp[step].yourState = CorrectX(exp[step].yourState,1);//弱一位
						}
					}

				}
			}
		}

		//启用EXP
		if (val > 3)
		{
			int o = stepTest.StepStandard(recorder, 1);
			int step = stepTest.step;
			//似曾相识
			if (exp[step].yourState != blank)
			{
				return CorrectX(exp[step].yourState, o + 1);
			}

		}
		return considerHope;

	}
	mirai_player() :cute(-1), val(0){};
};
