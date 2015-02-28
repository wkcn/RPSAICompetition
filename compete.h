#include "Defines.h"

//enum resultState { LOSE = 0, BALANCE = 1, WIN = 2 };

resultState judge(state me, state you)
{
	if (me == you) return BALANCE;
	if (me == rock && you == paper) return LOSE;
	if (me == paper && you == scissors) return LOSE;
	if (me == scissors && you == rock) return LOSE;
	return WIN;
};
string Trans(state p1)
{
	if (p1 == rock)return "石头";
	if (p1 == paper)return "布";
	if (p1 == scissors)return "剪刀";
}
/*
int main()
{
	win = 0;
	mirai_player playerMe;
	rock_player playerYou;
	vector<state> me_history, you_history;
	for (int i = 1; i < TOTAL; i++)
	{
		state p1 = playerMe.play(TOTAL - i, me_history, you_history);
		state p2 = playerYou.play(TOTAL - i, you_history, me_history);
		printX(i, p1, p2);
		me_history.push_back(p1);
		you_history.push_back(p2);
	}
	cout << endl << endl << "胜率: " << win*1.0 / TOTAL << endl;
	return 0;
}
*/