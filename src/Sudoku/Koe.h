#pragma once
#include<queue>
using namespace std;
class Koe										//宫格
{
	int **number;								//数字
	int max;									//最大值
	int ***block, block_x, block_y;				//划分块
	double div_x, div_y;						//划分系数
	queue <int> space_x, space_y;				//待填数字位置
	bool solved,no_solutions, divided;			//是否找到解，是否无解，是否划分
public:
	Koe(int, int **);							//初始化
	int deduce(queue <int> s_x, queue <int> s_y);	//推算（深度优先）
	~Koe();
	void display();									//窗口内输出当前数独状态
	void available(int i, int j, queue<int> &rest);	//寻找i，j处可填数字，存放正在rest里
	void initial_block();							//分块初始化
	void start();									//开始推算
	void check();									//检查盘面是否合法
};