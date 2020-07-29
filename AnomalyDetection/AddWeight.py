# -*- coding: utf-8 -*-

# Created by saki on 2017/4/30.

input = open('/Users/saki/Desktop/AnomalyDetection/graph/enron_edgelist.txt','r')
output = open('/Users/saki/Desktop/AnomalyDetection/graph/enron_edgelist_weighted.txt','w')


for lines in input.readlines():
    output.write(lines.strip() + ' 1\n')

output.close()
input.close()