// Sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"pch.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include"Koe.h"
#include"Method.h"
#include"WAE.h"
using namespace std;
fstream fin, fout;
int ***arr;
char inpath[1000], outpath[1000];
int order, quantity, solutions = 0;
bool multiSolution = false, unlimited = false;
int main(int argc, char *argv[])
{
	input(argc, argv);
	if (multiSolution)fout << Tip_attan_ans1;
	for (int i = 0; i != quantity; ++i)
	{
		if (multiSolution)fout << Tip_attan_ans2 << i + 1 << Tip_attan_ans3;
		Koe sudoku(order, arr[i]);
		printf(Tip_checking, i + 1);
		sudoku.check();
		sudoku.start();
		printf(Tip_scheduled, i + 1, quantity);
	}
	printf(Tip_data_output, outpath);
	printf(Tip_finished);
	finish();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
