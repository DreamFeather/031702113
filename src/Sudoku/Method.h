#pragma once
#include<fstream>
using namespace std;
void file_output(int **, int);					//输出数独解
void file_unsolved();							//多阶无解
bool check_float(char *);						//检查浮点数
void input(int ac, char *av[]);					//读取文件
void finish();