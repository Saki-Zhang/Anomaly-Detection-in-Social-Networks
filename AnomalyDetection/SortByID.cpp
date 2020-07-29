//
//  SortByID.cpp
//  AnomalyDetection
//
//  Created by ZHANG Zuoqi on 2017/5/5.
//  Copyright © 2017年 ZHANG Zuoqi. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;

bool cmp(string str1, string str2)
{
    size_t pos1 = str1.find_first_of(' ');
    size_t pos2 = str2.find_first_of(' ');
    string s1 = str1.substr(0, pos1);
    string s2 = str2.substr(0, pos2);
    int id1 = atoi(s1.c_str());
    int id2 = atoi(s2.c_str());
    return id1 < id2;
}

string lines[36692];

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream input;
    ofstream output;
    string str;
    input.open("/Users/saki/Desktop/AnomalyDetection/emb/enron_node2vec.txt");
    int cnt = 0;
    while (getline(input, str)) {
        lines[cnt ++] = str;
    }
    input.close();
    sort(lines, lines + 36692, cmp);
    output.open("/Users/saki/Desktop/AnomalyDetection/emb/enron_emb.txt");
    for (int i = 0; i < 36692; i ++) {
        output << lines[i] << endl;
    }
    //    std::cout << "Hello, World!\n";
    return 0;
}