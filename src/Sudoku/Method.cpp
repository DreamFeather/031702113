#include"pch.h"
#include"Method.h"
#include"Koe.h"
#include"WAE.h"
#include<iostream>
#include<stdlib.h>
extern fstream fin, fout;
extern int ***arr;
extern char inpath[1000], outpath[1000];
extern int order, quantity, solutions;
extern bool multiSolution, unlimited;
void file_output(int **arr, int m)
{
	for (int i = 0; i != m; ++i)
	{
		for (int j = 0; j != m; ++j)
		{
			fout << arr[i][j];
			if (j != m - 1)fout << " ";
			else fout << "\n";
		}
	}
	fout << "\n";
}
void input(int ac, char *av[])
{
	double o, q;
	/*if (ac < 2)
	{
		o = 5 ,q = 1;
		fin.open("D:\\.DATA\\Desktop\\input.txt",ios::in);
		fout.open("D:\\.DATA\\Desktop\\output.txt",ios::out);
		multiSolution = true; unlimited = false;
		solutions = 10000;
	}
	else*/ if (ac != 9 && ac != 10 && ac != 11)
	{
		printf(Error_parameter1);
		printf(Std_form1), printf(Std_form2), printf(Std_form3), printf(Std_form);
		exit(1);
	}
	else
	{
		int i(1), slt = 0;
		bool ord = false, qua = false, ipa = false, opa = false, muls = false;
		if (ac == 9)
		{
			i = 1;
			while (i < ac - 1)
			{
				if (strcmp(av[i], _m) == 0)o = atoi(av[i + 1]), ord = true;
				else	if (strcmp(av[i], _n) == 0)q = atoi(av[i + 1]), qua = true;
				else	if (strcmp(av[i], _in) == 0)strcpy_s(inpath, av[i + 1]), ipa = true;
				else	if (strcmp(av[i], _out) == 0)strcpy_s(outpath, av[i + 1]), opa = true;
				++i;
			}
			if (!ord or !qua or !ipa or !opa)printf(Error_parameter2), printf(Std_form1), printf(Std_form2), printf(Std_form3), printf(Std_form), exit(1);
		}
		if (ac == 10)
		{
			i = 0;
			while (i < ac - 1)
			{
				if (strcmp(av[i], _m) == 0)o = atoi(av[i + 1]), ord = true;
				else	if (strcmp(av[i], _n) == 0)q = atoi(av[i + 1]), qua = true;
				else	if (strcmp(av[i], _in) == 0)strcpy_s(inpath, av[i + 1]), ipa = true;
				else	if (strcmp(av[i], _out) == 0)strcpy_s(outpath, av[i + 1]), opa = true;
				else	if (strcmp(av[i], _s) == 0)muls = true;
				++i;
			}
			if (muls == false)
			{
				if (strcmp(av[i], _s) == 0)muls = true;
			}
			if (!ord or !qua or !ipa or !opa or !muls)printf(Error_parameter2), printf(Std_form1), printf(Std_form2), printf(Std_form3), printf(Std_form), exit(1);
		}

		if (ac == 11)
		{
			i = 0;
			while (i < ac - 1)
			{
				if (strcmp(av[i], _m) == 0)o = atoi(av[i + 1]), ord = true;
				else	if (strcmp(av[i], _n) == 0)q = atoi(av[i + 1]), qua = true;
				else	if (strcmp(av[i], _in) == 0)strcpy_s(inpath, av[i + 1]), ipa = true;
				else	if (strcmp(av[i], _out) == 0)strcpy_s(outpath, av[i + 1]), opa = true;
				else	if (strcmp(av[i], _s) == 0)slt = atoi(av[i + 1]), muls = true;
				++i;
			}
			if (!ord or !qua or !ipa or !opa or !muls)printf(Error_parameter2), printf(Std_form1), printf(Std_form2), printf(Std_form3), printf(Std_form), exit(1);
		}
		if (ac == 10)
		{
			if (muls)multiSolution = true, unlimited = true;

		}
		if (ac == 11)
		{
			if (slt <= 0)printf(Error_slt), exit(1);
			solutions = slt;
			multiSolution = true;
			unlimited = false;
		}
		if (strcmp(outpath, _s) == 0)printf(Error_outfile), printf(Std_form), exit(1);
		if (strcmp(outpath, _in) == 0)printf(Error_outfile), printf(Std_form), exit(1);
		if (strcmp(outpath, _out) == 0)printf(Error_outfile), printf(Std_form), exit(1);
		if (strcmp(outpath, _m) == 0)printf(Error_outfile), printf(Std_form), exit(1);
		if (strcmp(outpath, _n) == 0)printf(Error_outfile), printf(Std_form), exit(1);
		if (strcmp(inpath, outpath) == 0)
		{
			printf(Error_same_path), printf(Tip_check_f), exit(1);
		}
		fin.open(inpath, ios::in);
		fout.open(outpath, ios::out);
	}
	order = int(o), quantity = int(q);
	if (double(order) != o || double(quantity) != q)
	{
		printf(Warn_float);
		exit(1);
	}
	if (order < 3 || order>9)
	{
		printf(Error_order);
		exit(1);
	}
	if (quantity < 1)
	{
		printf(Error_quantity);
		exit(1);
	}
	if (!fin)
	{
		printf(Error_infile, inpath);
		printf(Tip_check_f);
		printf(Tip_file_length);
		exit(1);
	}
	if (order > 6 && quantity > 20)printf(Tip_deal_wait1);
	arr = new int**[quantity];
	for (int i = 0; i != quantity; ++i)
	{
		arr[i] = new int*[order];
		for (int j = 0; j != order; ++j)
		{
			arr[i][j] = new int[order];
			for (int f = 0; f != order; ++f)
			{
				fin >> arr[i][j][f];
				if (fin.eof())
				{
					printf(Error_read_eof), printf(Tip_check_s, order, quantity);
					exit(1);
				}
				if (fin.fail())
				{
					printf(Error_file_input, i + 1, j + 1, f + 1);
					exit(1);
				}
				if (arr[i][j][f]<0 || arr[i][j][f]>order)
				{
					printf(Error_input_number, i + 1, j + 1, f + 1, order);
					printf(Tip_check_order);
					exit(1);
				}
			}
		}
	}
}
void finish()
{
	if (arr != NULL)
	{
		for (int i = 0; i != quantity; ++i)
			if (arr[i] != NULL)
			{
				for (int j = 0; j != order; ++j)
					if (arr[i][j] != NULL)delete arr[i][j];
				delete arr[i];
			}
		delete arr;
	}
}
void file_unsolved()
{
	fout << Tip_koe_unsolved;
	fout << endl;
}