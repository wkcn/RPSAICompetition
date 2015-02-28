#include "Defines.h"
#include "Players.h"
#include "compete.h"
#include "readname.h"
#include "readplayer.h"

int main12(){
	cout << "一年一度的RPS大赛现在开始啦" << endl << endl;
	cout << "比赛规则：" << endl;
	cout << "采取循环赛制，大局赢了3分，输了0分，平了各1分" << endl;
	cout << "小局每一次出拳，胜1分，败0分，和0.5分,每小局猜拳10000次 O _ O" << endl;
	cout << "冠军只有一个，如果有平分，继续进行循环赛制，直到决出冠军" << endl;

	//载入选手
	vector<player*> players;
	vector<string> names;
	/*
	players.push_back(new JLM_Player); names.push_back("JLM");
	players.push_back(new Do_the_same_as_the_opponent); names.push_back("dosame");
	players.push_back(new Beat_the_opponent_last_move); names.push_back("dolastmove");
	players.push_back(new Beat_the_opponent_last_time); names.push_back("dolasttime");
	players.push_back(new EasyAI); names.push_back("easyai1");
	players.push_back(new EasyAI2); names.push_back("easyai2");
	players.push_back(new EasyAI3); names.push_back("easyai3");
	players.push_back(new EasyAI4); names.push_back("easyai4");
	players.push_back(new EasyAI4_1); names.push_back("easyai4_1");
	players.push_back(new EasyAI4_2); names.push_back("easyai4_2");
	players.push_back(new daze_player); names.push_back("daze");
	players.push_back(new NoloopPlayer); names.push_back("noloo");
	players.push_back(new MarkovPlayer); names.push_back("markov1");
	players.push_back(new MarkovPlayer2); names.push_back("markov2");
	players.push_back(new mirai_player); names.push_back("mirai");
	players.push_back(new NewPlayer); names.push_back("newp");
	players.push_back(new PersonificationPlayer); names.push_back("personification");
	players.push_back(new zzRetarded); names.push_back("zzR");
	players.push_back(new rock_player); names.push_back("rock");
	players.push_back(new paper_player); names.push_back("paper");
	players.push_back(new scissors_player); names.push_back("scissor");
	players.push_back(new cycle_player); names.push_back("cycle");
	players.push_back(new random_player); names.push_back("rand");
	players.push_back(new time_player); names.push_back("time");
	int playerSize = players.size();
	*/
	int playerSize = 24;
	cout <<endl<< "共" << playerSize << "位选手参赛！" << endl;
	cout << "比赛准备开始" << endl;

	string temp;
	cin >> temp;
	cout << "开始!" << endl;
	const int TOTAL = 10000;
	ofstream fout("result.txt");
	//playerSize = 2;
	int havei, havej;
	havei = 16;
	havej = 20;
	for (int i = 0; i < playerSize;i++){
		for (int j = i + 1; j < playerSize; j++){
			if (i<havei){
				continue;
			}
			else{
				if (i==havei && j <= havej){
					continue;
				}
			}

			player &a = *(GetPlayer(i));
			player &b = *(GetPlayer(j));
			string aname = GetName(i);//names[i];
			string bname = GetName(j);//names[j];
			vector<state> me_history, you_history;
			int win[2], combo[2], maxcombo[2];
			int ban;
			ban = 0;
			for (int i = 0; i < 2; i++){
				win[i] = combo[i] = maxcombo[i] = 0;
			}
			bool lastwin;
			bool first = true;
			int id;
			cout << aname << "和" << bname << "开始比赛 " << i << " " << j << endl;
			int lastTime = clock();
			for (int i = 1; i <= TOTAL; i++)
			{
				state p1 = a.play(TOTAL - i, me_history, you_history);
				state p2 = b.play(TOTAL - i, you_history, me_history);
				resultState res = judge(p1, p2);
				if (res != BALANCE){
					if (res == WIN){
						//a win
						id = 0;
					}
					else{
						id = 1;
					}

					if (!first){
						if (lastwin == id){
							combo[id] ++;
							if (combo[id]>maxcombo[id]){
								maxcombo[id] = combo[id];
							}
						}
						else{
							combo[1 - id] = 0;
							combo[id] = 1;
						}
					}
					else{
						combo[id] = 1;
						maxcombo[id] = 1;
						first = false;
					}
					win[id] ++;
					lastwin = id;

				}
				else{
					ban++;
				}
				me_history.push_back(p1);
				you_history.push_back(p2);
			}
			int useTime = clock() - lastTime;
			cout << aname << " " << bname << " " << win[0] << " " << win[1] << " " << ban << " " << maxcombo[0] << " " << maxcombo[1] << " " << useTime << endl;
			fout << aname << " " << bname << " " << win[0] << " " << win[1] << " " << ban << " " << maxcombo[0] << " " << maxcombo[1] << " " << useTime << endl;
			delete &a;
			delete &b;
		}
	}
	fout.close();
	cout << "比赛结束！"<<endl;
	while (1){
		cin >> temp;
	}
	return 0;
}

struct playerGrade{
	string name;
	int score;
	//int maxCombo;
	long long useTime;
	playerGrade(string na){
		score = 0;
		//maxCombo = 0;
		useTime = 0;
		name = na;
	}
	bool operator < (const playerGrade &b) const{
		if (score!=b.score){
			return score < b.score;
		}
		return useTime > b.useTime;
	}

};
int findID(vector<playerGrade>& l, string &u){
	int o = 0;
	for (; o < l.size();o++){
		if (l[o].name == u){
			return o;
		}
	}
	l.push_back(playerGrade(u));
	return o;
}
int main(){
	cout << "RPS比赛结果-新版20150227-22:28" << endl;
	fstream fin("resultNew.txt");
	//map<string,playerGrade> players;
	//set<playerGrade> players;
	vector<playerGrade> players;
	string aname, bname;
	int awin, bwin, ban, ac, bc, t;
	int rank = 0;
	while (!fin.eof()){
		fin >> aname >> bname >> awin >> bwin >> ban >> ac >> bc >> t;
		int aid = findID(players, aname);
		int bid = findID(players, bname);
		//players[aid].score += awin * 1 + ban*0.5;
		players[aid].useTime += t;
		//players[bid].score += bwin * 1 + ban*0.5;
		players[bid].useTime += t;
		double as = awin * 1 + ban*0.5;
		double bs = bwin * 1 + ban*0.5;
		if (as == bs){
			players[aid].score += 1;
			players[bid].score += 1;
		}
		else{
			if (as > bs){
				players[aid].score += 3;
			}
			else{
				players[bid].score += 3;
			}
		}

	}
	rank = players.size();
	sort(players.begin(), players.end());
	cout << "共" << rank << "名选手" << endl<<endl;
	for (int i = 0; i < rank; i++){
		playerGrade &g = players[i];
		cout << "第" <<setw(2)<< rank - i << "名：" << setw(20) << g.name << "    " << setw(16)<< g.score << "分  用时：" << g.useTime << "ms" << endl;
	}
	string temp;
	while (1){
		cin >> temp;
	}
	return 0;
}
int main4(){
	vector<string> v;
	ifstream fin("list.txt");
	ofstream fout("q.txt");
	int i = 0;
	while (!fin.eof())
	{
		string u;
		fin >> u;
		fout << "case " << i++ << ":" << endl;
		//fout << "return new " << u << ";" << endl;
		fout << "return \"" << u << "\";" << endl;
	}
	return 0;
}