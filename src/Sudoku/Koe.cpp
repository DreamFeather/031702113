#include"pch.h"
#include"Koe.h"
#include"Method.h"
#include"WAE.h"
extern bool multiSolution, unlimited;
extern int solutions;
extern fstream fout;
int rest_answer;
Koe::Koe(int k, int **array) :solved(false), divided(false),no_solutions(false)
{
	max = k;
	rest_answer = solutions;
	switch (k)
	{
	case 3:
	case 5:
	case 7:block_x = 0, block_y = 0;		break;
	case 4:div_x = 0.5, div_y = 0.5;		block_x = 2, block_y = 2; break;
	case 6:div_x = 0.5, div_y = 1.01 / 3;	block_x = 3, block_y = 2; break;
	case 8:div_x = 0.25, div_y = 0.5;		block_x = 2, block_y = 4; break;
	case 9:div_x = 1.01 / 3, div_y = 1.01 / 3;	block_x = 3, block_y = 3; break;
	default:block_x = 0, block_y = 0;		break;
	}
	initial_block();
	number = new int*[max];
	for (int i = 0; i != max; ++i)
	{
		number[i] = new int[max];
		for (int j = 0; j != max; ++j)
		{
			number[i][j] = array[i][j];
			if (number[i][j] == 0)space_x.push(i), space_y.push(j);
			else if (divided)block[int(i*div_x)][int(j*div_y)][number[i][j]] = 1;
		}
	}
	//printf(Tip_koe_init_status);
	//display();						//初始状态显示
}
void Koe::initial_block()				//初始化宫块
{
	if (block_x == 0)return;
	divided = true;
	int m = max + 1, k;
	block = new int **[block_x];
	for (int i = 0; i != block_x; ++i)
	{
		block[i] = new int *[block_y];
		for (int j = 0; j != block_y; ++j)
		{
			block[i][j] = new int[m];
			for (k = 0; k != m; ++k)
			{
				block[i][j][k] = 0;
			}
		}
	}
}

void Koe::display()						//屏幕显示
{
	for (int i = 0; i != max; ++i)
	{
		for (int j = 0; j != max; ++j)
		{
			printf("%d ", number[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Koe::available(int i, int j, queue<int> &rest)			//可用数字队列
{
	int m = 0, max_ = max + 1;
	int *exist = new int[max_];
	while (m != max_)exist[m++] = 0;
	for (m = 0; m != max; ++m)
	{
		exist[number[i][m]] = 1;
		exist[number[m][j]] = 1;
	}
	if (divided)
	{
		int x = int(i *div_x), y = int(j *div_y);
		for (int z = 1; z != max_; ++z)
		{
			if (block[x][y][z] == 1)exist[z] = 1;
		}
	}
	m = 1;
	while (m != max_)
	{
		if (exist[m] == 0)rest.push(m);
		++m;
	}
	delete []exist;
}

Koe::~Koe()
{
	if (number != NULL)
	{
		for (int i = 0; i != max; ++i)
			if (number[i] != NULL)delete number[i];
		delete number;
	}
	if (block != NULL)
	{
		for (int i = 0; i != block_x; ++i)
			if (block[i] != NULL)
			{
				for (int j = 0; j != block_y; ++j)
					if (block[i][j] != NULL)
						delete block[i][j];
				delete block[i];
			}
		delete block;
	}
}

int Koe::deduce(queue <int> s_x, queue <int> s_y)			//深度搜索解
{
	int x = s_x.front(), y = s_y.front();
	queue<int> rest;
	available(x, y, rest);
	if (rest.empty())return 0;
	s_x.pop(), s_y.pop();
	int blk_x = int(x *div_x), blk_y = int(y * div_y);
	int record = number[x][y];
	int answer = 0;
	while (!rest.empty())
	{
		number[x][y] = rest.front();
		//display();
		rest.pop();
		if (divided)block[blk_x][blk_y][number[x][y]] = 1;
		if (!s_x.empty())answer += deduce(s_x, s_y);
		if (!multiSolution and solved)break;
		if (multiSolution and !unlimited and rest_answer == 0)return answer;
		if (divided)block[blk_x][blk_y][number[x][y]] = 0;
	}
	if (s_x.empty())
	{
		//printf(Tip_koe_solved);
		//display();								//找到解显示
		file_output(number, max);
		++answer;
		--rest_answer;
		solved = true;
		if (multiSolution and !unlimited and rest_answer == 0)return answer;
	}
	number[x][y] = record;
	return answer;
}

void Koe::start()
{
	printf(Tip_deal_wait2);
	if (no_solutions) { file_unsolved(); return; }
	int answers = deduce(space_x, space_y);
	if (!solved)printf(Tip_koe_unsolved),file_unsolved();
	if (multiSolution and !unlimited)						//多解且限制
	{
		if (answers < solutions)fout << Tip_koe_ans1_1 << answers << Tip_koe_ans1_2;
		else fout << Tip_koe_ans2_1 << answers << Tip_koe_ans2_2;
	}
	if (multiSolution and unlimited)
	{
		fout << Tip_koe_ans3_1 << answers << Tip_koe_ans1_2;
	}
}

void Koe::check()											//搜索前检查
{
	int i, j;
	int b_x, b_y;
	int lft, rgt;
	int top, btm;
	queue<int > rest, empty;
	for (i = 0; i != max; ++i)
	{
		for (j = 0; j != max; ++j)
		{
			if (number[i][j] == 0)
			{
				available(i, j, rest);
				if (rest.empty())
				{
					printf(Error_fake_sudoku, i + 1, j + 1), printf(Tip_check_content), no_solutions = true;
					return;
				}
				rest = empty;
				continue;
			}
			for (int m = 0; m != max; m++)
			{
				if (m == i || m == j)continue;
				if (number[i][m] == number[i][j])
				{
					printf(Error_koe_row, i + 1, m + 1, j + 1, number[i][j]);
					exit(1);
				}
				if (number[m][j] == number[i][j])
				{
					printf(Error_koe_column, j + 1, m + 1, i + 1, number[i][j]);
					exit(1);
				}
			}

			if (divided)
			{
				b_x = int(i*div_x), b_y = int(j*div_y);
				lft = b_x * block_y, rgt = (b_x + 1)*block_y;
				top = b_y * block_x, btm = (b_y + 1)*block_x;
				for (int k = lft; k != rgt; ++k)
				{
					for (int p = top; p != btm; ++p)
					{

						if (k == i || p == j)continue;
						if (number[k][p] == number[i][j])
						{
							printf(Error_koe_block, lft + 1, top + 1, rgt, btm, i + 1, j + 1, k + 1, p + 1, number[i][j]);
							exit(1);
						}
					}
				}
			}
		}
	}
	printf(Tip_koe_checked);
}