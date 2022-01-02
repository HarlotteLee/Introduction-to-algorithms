#pragma once
#include<iostream>
#include<time.h>
#include<cstring>
#include <vector>
#include<fstream>
using namespace std;

#define cityNum 16			//城市数量（基因数量）（染色体长度）
#define popSize 16				//种群大小（尺寸）
#define croRate 0.85			//交叉概率
#define mutRate 0.1				//变异概率
#define MAX 90000					//进化代数
//定义城市的结构
struct City
{
	char name;
	int x;
	int y;
};

//定义染色体的结构
struct Chrom
{
	int cityArr[cityNum];		//染色体的基因编码
	char name;					//染色体的名称
	float adapt;				//染色体的适应度
	int dis;					//染色体的路径长度
};


class GeneticAlgorithm
{
public:
	struct Chrom genes[popSize];	//定义基因库（结构体数组）
	struct Chrom genesNew[popSize]; //重新建立一个新的种群
	struct Chrom temp;				//定义临时公用结点
	
	double distance[cityNum][cityNum];
	struct City cities[cityNum];
public:
	void read();
	void initGroup();
	void popFitness();
	int chooseBest();
	void _select();
	void cross();
	void mutation();

};




#include "GeneticAlgorithm.h"

void GeneticAlgorithm::read()
{
	ifstream myfile("graph12.txt");
	if (!myfile.is_open())
	{
		cout << "未成功打开文件" << endl;
	}
	//开始读文件
	int count;
	char name;
	int x, y;
	int i = 0;
	myfile >> count;
	while (count != 0)
	{
		myfile >> name >> x >> y;
		cities[i].name = name;
		cities[i].x = x;
		cities[i].y = y;
		i++;
		count--;
	}
	

	myfile.close();
}

void GeneticAlgorithm::initGroup()
{

	//初始化基因库	
	int i, j, k;
	int t = 0;
	int flag = 0;
	for (i = 0; i < cityNum; i++)
	{
		for (j = 0; j <= i; j++)
		{
			if (i == j)
				distance[i][j] = 0.0;
			else
			{

				distance[i][j] = sqrt(pow(cities[i].x - cities[j].x, 2.0) + pow(cities[i].y - cities[j].y, 2.0));
				distance[j][i] = distance[i][j];
			}
		}
	}
	srand(time(NULL));//初始化随机种子,防止随机数每次重复，常常使用系统时间来初始化,当srand()的参数值固定的时候，rand()获得的数也是固定的
	for (i = 0; i < popSize; i++)
	{
		//使用临时结点开始赋值
		temp.name = cities[i].name;
		temp.adapt = 0.0f;
		temp.dis = 0;
		//产生10个不相同的数字
		for (j = 0; j < cityNum;)
		{
			t = rand() % cityNum;	//随机产生0-11的数
			flag = 1;
			for (k = 0; k < j; k++)
			{
				if (genes[i].cityArr[k] == t)
				{
					flag = 0;
					break;
				}
			}
			if (flag)
			{
				temp.cityArr[j] = t;
				genes[i] = temp;//存入结构体数组，产生一个个体
				j++;
			}
		}
	}
}

void GeneticAlgorithm::popFitness()
{
	int i, n1, n2;
	for (i = 0; i < popSize; i++)
	{
		genes[i].dis = 0;
		for (int j = 1; j < cityNum; j++)
		{
			n1 = genes[i].cityArr[j - 1];
			n2 = genes[i].cityArr[j];
			genes[i].dis += distance[n1][n2];
		}
		genes[i].dis += distance[genes[i].cityArr[0]][genes[i].cityArr[cityNum - 1]];
		genes[i].adapt = (float)1 / genes[i].dis;	//每条染色体的路径总和(个体适应度)		
	}
}

int GeneticAlgorithm::chooseBest()
{
	int choose = 0;
	float best = 0.0f;
	best = genes[0].adapt;
	for (int i = 0; i < popSize; i++)
	{
		if (genes[i].adapt < best)
		{
			best = genes[i].adapt;
			choose = i;
		}
	}
	return choose;
}

void GeneticAlgorithm::_select()
{
	float biggestSum = 0.0f;
	float adapt_pro[popSize];
	float pick = 0.0f;
	int i;
	for (i = 0; i < popSize; i++)
	{
		biggestSum += genes[i].adapt; // 总概率
	}
	for (i = 0; i < popSize; i++)
	{
		adapt_pro[i] = genes[i].adapt / biggestSum; // 概率数组
	}
	// 轮盘赌
	for (i = 0; i < popSize; i++)
	{
		pick = (float)rand() / RAND_MAX; // 0到1之间的随机数

		for (int j = 0; j < popSize; j++)
		{
			pick = pick - adapt_pro[j];
			if (pick <= 0)
			{
				genesNew[i] = genes[j];
				break;
			}
		}
	}
	for (i = 0; i < popSize; i++)
	{
		genes[i] = genesNew[i];
	}
}

void GeneticAlgorithm::cross()
{
	float pick;
	int choice1, choice2;
	int pos1, pos2;
	int temp;
	int conflict1[popSize];	// 冲突位置
	int conflict2[popSize];
	int num1;
	int num2;
	int index1, index2;
	int move = 0;				// 当前移动的位置
	while (move < popSize - 1)
	{
		pick = (float)rand() / RAND_MAX; // 用于决定是否进行交叉操作

		if (pick > croRate)		//两条染色体是否相爱
		{
			move += 2;
			continue;			// 本次不进行交叉
		}

		// 采用部分映射杂交
		choice1 = move;			// 用于选取杂交的两个父代
		choice2 = move + 1;		// 注意避免下标越界

		pos1 = rand() % popSize;
		pos2 = rand() % popSize;

		while (pos1 > popSize - 2 || pos1 < 1)//如果位置在开头或结尾(因为全部交换无意义)
		{
			pos1 = rand() % popSize;
		}
		while (pos2 > popSize - 2 || pos2 < 1)
		{
			pos2 = rand() % popSize;
		}

		if (pos1 > pos2)
		{
			temp = pos1;
			pos1 = pos2;
			pos2 = temp; // 交换pos1和pos2的位置
		}

		for (int j = pos1; j <= pos2; j++)// 逐个交换顺序
		{
			temp = genes[choice1].cityArr[j];
			genes[choice1].cityArr[j] = genes[choice2].cityArr[j];
			genes[choice2].cityArr[j] = temp;
		}

		num1 = 0;
		num2 = 0;

		if (pos1 > 0 && pos2 < popSize - 1)//分三段
		{
			for (int j = 0; j < pos1; j++)
			{
				for (int k = pos1; k <= pos2; k++)
				{
					if (genes[choice1].cityArr[j] == genes[choice1].cityArr[k])
					{
						conflict1[num1] = j;
						num1++;
					}
					if (genes[choice2].cityArr[j] == genes[choice2].cityArr[k])
					{
						conflict2[num2] = j;
						num2++;
					}
				}
			}

			for (int j = pos2 + 1; j < popSize; j++)
			{
				for (int k = pos1; k <= pos2; k++)
				{
					if (genes[choice1].cityArr[j] == genes[choice1].cityArr[k])
					{
						conflict1[num1] = j;
						num1++;
					}
					if (genes[choice2].cityArr[j] == genes[choice2].cityArr[k])
					{
						conflict2[num2] = j;
						num2++;
					}
				}

			}
		}
		if ((num1 == num2) && num1 > 0)
		{
			for (int j = 0; j < num1; j++)
			{
				index1 = conflict1[j];
				index2 = conflict2[j];
				temp = genes[choice1].cityArr[index1]; // 交换冲突的位置
				genes[choice1].cityArr[index1] = genes[choice2].cityArr[index2];
				genes[choice2].cityArr[index2] = temp;
			}
		}
		move += 2;
	}
}

void GeneticAlgorithm::mutation()
{
	double pick;
	int pos1, pos2, temp;
	for (int i = 0; i < popSize; i++)
	{
		pick = (float)rand() / RAND_MAX; // 用于判断是否进行变异操作
		if (pick > mutRate)
		{
			continue;
		}
		pos1 = rand() % popSize;
		pos2 = rand() % popSize;
		while (pos1 > popSize - 1)
		{
			pos1 = rand() % popSize;
		}
		while (pos2 > popSize - 1)
		{
			pos2 = rand() % popSize;
		}

		int a = genes[i].dis;
		temp = genes[i].cityArr[pos1];
		genes[i].cityArr[pos1] = genes[i].cityArr[pos2];
		genes[i].cityArr[pos2] = temp;

		popFitness();//更新数据
		//此步骤的作用在于检查是否变异后得到的个体比变异前更优秀了，如若往坏的方向变化了，那还不如不变异了
		//（强制返回，虽然有点违背事物的客观发展规律，但为了增强程序的收敛性，该操作还是有必要的）（偷笑）
		if (genes[i].dis > a)
		{
			temp = genes[i].cityArr[pos1];
			genes[i].cityArr[pos1] = genes[i].cityArr[pos2];
			genes[i].cityArr[pos2] = temp;
		}
	}
}

#include "GeneticAlgorithm.h"

int main()
{
	GeneticAlgorithm genetic;
	genetic.read();
	char c = 0;
	cout << "\n\t\t******************************** 遗传算法求解TSP(旅行商)问题 *********************************\n";
	genetic.initGroup();	//初始化
	genetic.popFitness();	//更新数据
	cout << "\n\t\t基因长度:" << cityNum;
	cout << "\t种群大小:" << popSize;
	cout << "\t交叉概率:" << croRate;
	cout << "\t进化代数:" << MAX;
	cout << "\t预设最优解：18";
	cout << "\n\n\t\t**********************************************************************************************\n";

	cout << "--------------------------------- 城市坐标信息--------------------------------------- ---------\n";
	for (int i = 0; i < cityNum; i++)
	{
		cout <<genetic.cities[i].name<<"  " << genetic.cities[i].x << " " << genetic.cities[i].y << endl;
	}
	cout << "--------------------------------- 城市距离矩阵--------------------------------------- ---------\n";
	for (int i = 0; i < cityNum; i++)
	{
		for (int j = 0; j < cityNum; j++)
		{
			cout << genetic.distance[i][j] << "      ";
		}
		cout << endl;
	}
	cout << "-------------------------------------------------------------" << endl;
	cout << "--------------初始种群基因库-----------------------------------" << endl;
	
	for (int i = 0; i < cityNum; i++)
	{
		for (int j = 0; j < cityNum; j++)
		{
			cout << genetic.genes[i].cityArr[j] << "   ";
		}
		cout << endl;
	}
	cout << "------------------------------------------------------------------" << endl;
	cout << "寻找最优解中：-----------" << endl;
	while (1)
	{
		for (int i = 0; i < MAX; i++)
		{
			genetic._select();
			genetic.cross();
			genetic.popFitness();//更新数据
			genetic.mutation();
			genetic.popFitness();//更新数据
			int temp = (int)MAX / 20;
		}
		cout << "完成" << endl;
		cout << "最优路径为：   ";
		for (int i = 0; i < cityNum; i++)
		{
			cout << genetic.genes[genetic.chooseBest()].cityArr[i]<<"  ";
		}
		cout << "   ";
		cout << "路径长度:  " << genetic.genes[genetic.chooseBest()].dis << endl;
		cout << "是否再试一次：是（Y），否（N）：";
		char c;
		cin >> c;
		if (c == 'N')
			break;
	}
	
	return 0;

}
