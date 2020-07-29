//
//  CalcProb.cpp
//  AnomalyDetection
//
//  Created by ZHANG Zuoqi on 2017/5/5.
//  Copyright © 2017年 ZHANG Zuoqi. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

const int dimension = 17;
const int nodes = 36692;
const int clusters = 70;
int t_max = 2;
double alpha = 1;
int labels[nodes] = {0};
int nodes_in_comm[clusters] = {0};
vector<vector<double> > X(nodes, vector<double>(dimension));
vector<vector<double> > Y(nodes, vector<double>(clusters));
vector<vector<double> > M(clusters, vector<double>(dimension));

vector<string> split(string &str, const char *c)
{
	char *cstr, *p;
	vector<string> res;
	cstr = new char[str.size() + 1];
	strcpy(cstr, str.c_str());
	p = strtok(cstr, c);
	while(p != NULL)
	{
		res.push_back(p);
		p = strtok(NULL, c);
	}
	return res;
}

//vector1 - vector2
vector<double> minusVec(vector<double> vec1, vector<double> vec2)
{
	int len = vec1.size();
	vector<double> result(len);
	for(int i = 0;i < len;i ++)
	{
		result[i] = vec1[i] - vec2[i];
	}
	return result;
}

//||vector|| ^ 2
double normVec(vector<double> vec)
{
	int len = vec.size();
	double result = 0;
	for(int i = 0;i < len;i ++)
	{
		result += vec[i] * vec[i];
	}
	return result;
}

void init()
{
	for(int i = 0;i < nodes;i ++)
	{
		for(int j = 0;j < clusters;j ++)
		{
			if(j == labels[i])
			{
				nodes_in_comm[j] ++;
				for(int d = 0;d < dimension;d ++)
				{
					M[j][d] += X[i][d];
				}
				Y[i][j]= 1;
			}
		}
	}
	for(int j = 0;j < clusters;j ++)
	{
		for(int d = 0;d < dimension;d ++)
		{
			M[j][d] /= nodes_in_comm[j];
		}
	}
}

double objFunc()
{
	double first = 0, second = 0;
	for(int i = 0;i < nodes;i ++)
	{
		for(int j = 0;j < clusters;j ++)
		{
			first += Y[i][j] * normVec(minusVec(X[i], M[j]));
		}
	}
	for(int i = 0;i < nodes;i ++)
	{
		second += normVec(Y[i]);
	}
	double sum = first + alpha * second;
	return sum;
}

void updateM()
{
	for(int j = 0;j < clusters;j ++)
	{
		double total = 0;
		for(int i = 0;i < nodes;i ++)
		{
			for(int d = 0;d < dimension;d ++)
			{
				M[j][d] += Y[i][j] * X[i][d];
			}
			total += Y[i][j];
		}
		for(int d = 0;d < dimension;d ++)
		{
			M[j][d] /= total;
		}
	}
}

void updateY()
{
	for(int i = 0;i < nodes;i ++)
	{
		double total = 0;
		for(int j = 0;j < clusters;j ++)
		{
			total += normVec(minusVec(X[i], M[j]));
		}
		double miny = 0;
		for(int j = 0;j < clusters;j ++)
		{
			Y[i][j] = (2 * alpha + total - clusters * normVec(minusVec(X[i], M[j]))) / (2 * clusters * alpha);
			if(Y[i][j] < miny)
			{
				miny = Y[i][j];
			}
		}
//		0 <= y[i][j] <= 1, sum = 1
		for(int j = 0;j < clusters;j ++)
		{
		    Y[i][j] = (Y[i][j] - miny) / (1 - miny * clusters);
		}
	}
}

int main(int argc, const char * argv[]) {
	// insert code here...
	ifstream input;
	string str;
	int lines;
	
	lines = 0;
	input.open("/Users/saki/Desktop/AnomalyDetection/feat/enron_feat.txt");
	while(getline(input, str))
	{
		vector<string> items = split(str, " ");
		for(int d = 1;d < dimension + 1;d ++)
		{
			X[lines][d - 1] = atof(items[d].c_str());
		}
		lines ++;
	}
	input.close();
	
	lines = 0;
	input.open("/Users/saki/Desktop/AnomalyDetection/comm/enron_kmeans.csv");
	while(getline(input, str))
	{
		vector<string> items = split(str, ",");
		int id = atoi(items[0].c_str());
		int label = atoi(items[1].c_str());
		labels[id] = label;
		lines ++;
	}
	input.close();
	
	init();
	int t = 0;
	while(t < t_max)
	{
		t ++;
		cout << "Iteration time: " << t << endl;
		cout << "Updating M..." << endl;
		updateM();
		cout << "Updating Y..." << endl;
		updateY();
		cout << "Value of O: " << fixed << setprecision(7) << objFunc() << endl;
	}
	
	ofstream output;
	output.open("/Users/saki/Desktop/AnomalyDetection/membership/enron_pr.txt");
	for(int i = 0;i < nodes;i ++)
	{
		for(int j = 0;j < clusters;j ++)
		{
			if(j > 0)
			{
				output << " ";
			}
			output << Y[i][j];
		}
		output << endl;
	}
	output.close();
	//    std::cout << "Hello, World!\n";
	return 0;
}