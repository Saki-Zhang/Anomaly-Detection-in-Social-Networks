//
//  CalcDegree.cpp
//  AnomalyDetection
//
//  Created by ZHANG Zuoqi on 2017/5/1.
//  Copyright © 2017年 ZHANG Zuoqi. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include <utility>
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream input;
    ofstream output;
    string str, s1, s2;
    map<int, int> degree;
    input.open("/Users/saki/Desktop/AnomalyDetection/graph/enron_all_edgelist.txt");
//    output.open("/Users/saki/Desktop/AnomalyDetection/graph/enron_edgelist.txt");
    cout << "Reading edgelist..." << endl;
    while (getline(input, str)) {
        size_t pos = str.find_first_of('\t');
        s1 = str.substr(0, pos);
        s2 = str.substr(pos + 1, str.length());
        int id1 = atoi(s1.c_str());
        int id2 = atoi(s2.c_str());
        if (id1 > id2)
        {
            continue;
        }
        degree[id1] += 1;
        degree[id2] += 1;
//        output << str << endl;
    }
    input.close();
//    output.close();
    cout << "Finish degree calculation." << endl;
    cout << "# of nodes = " << degree.size() << endl;
    int max_degree = -1;
    map<int, int> :: iterator it = degree.begin();
    while (it != degree.end()) {
        cout << "[" << it->first << "] degree: " << it->second << endl;
        if (max_degree < it->second)
        {
            max_degree = it->second;
        }
        it ++;
    }
    cout << "Max Degree = " << max_degree << endl;
    input.open("/Users/saki/Desktop/AnomalyDetection/emb/enron_emb.txt");
    output.open("/Users/saki/Desktop/AnomalyDetection/feat/enron_feat.txt");
    cout << "Reading embedding file..." << endl;
    while (getline(input, str)) {
        size_t pos = str.find_first_of(' ');
        int id = atoi(str.substr(0, pos).c_str());
        string newStr = str + " " + to_string(degree[id] / (max_degree * 1.0));
        output << newStr << endl;
    }
    input.close();
    output.close();
    cout << "Output feauture file created." << endl;
    cout << "Finished." << endl;
    //    std::cout << "Hello, World!\n";
    return 0;
}