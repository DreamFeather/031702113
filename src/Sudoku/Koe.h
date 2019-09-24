#pragma once
#include<queue>
using namespace std;
class Koe										//����
{
	int **number;								//����
	int max;									//���ֵ
	int ***block, block_x, block_y;				//���ֿ�
	double div_x, div_y;						//����ϵ��
	queue <int> space_x, space_y;				//��������λ��
	bool solved,no_solutions, divided;			//�Ƿ��ҵ��⣬�Ƿ��޽⣬�Ƿ񻮷�
public:
	Koe(int, int **);							//��ʼ��
	int deduce(queue <int> s_x, queue <int> s_y);	//���㣨������ȣ�
	~Koe();
	void display();									//�����������ǰ����״̬
	void available(int i, int j, queue<int> &rest);	//Ѱ��i��j���������֣��������rest��
	void initial_block();							//�ֿ��ʼ��
	void start();									//��ʼ����
	void check();									//��������Ƿ�Ϸ�
};