# -*- coding: utf-8 -*-

# Created by saki on 2017/5/5.

import string

def calc(avg, max, cnt):
    return 1.0 * avg / max * cnt

k = 70
thre = 45

Y = []
delete_nodes = []

file = open('/Users/saki/Desktop/AnomalyDetection/membership/enron_pr.txt', 'r')
for line in file.readlines():
    array = line.split(' ')
    vector = []
    for i in range(0, k):
        pr = string.atof(array[i])
        vector.append(pr)
    Y.append(vector)
file.close()

maxScore = 0

for i in range(0, len(Y)):
    sum = 0
    max = 0
    nonzero = 0
    for j in range(0, len(Y[i])):
        pr = string.atof(Y[i][j])
        sum += pr
        if pr > 0:
            nonzero += 1
        if max < pr:
            max = pr
    avg = 1.0 * sum / nonzero
    cnt = 0
    for j in range(0, len(Y[i])):
        pr = string.atof(Y[i][j])
        if pr >= avg:
            cnt += 1
    score = calc(avg, max, cnt)
    if score > maxScore:
        maxScore = score
    if score >= thre:
#        print i
        delete_nodes.append(str(i))

print maxScore
print len(delete_nodes)

# Update edges.csv and comm.csv
file = open('/Users/saki/Desktop/AnomalyDetection/edges/enron.csv', 'r')
outFile = open('/Users/saki/Desktop/AnomalyDetection/cut/enron.csv', 'w')
for line in file.readlines():
    array = line.split(',')
    if array[0] in delete_nodes or array[1].strip() in delete_nodes:
        continue;
    outFile.write(array[0] + ',' + array[1])
file.close()
outFile.close()

file = open('/Users/saki/Desktop/AnomalyDetection/comm/enron_kmeans.csv', 'r')
outFile = open('/Users/saki/Desktop/AnomalyDetection/cut/enron_kmeans.csv', 'w')
for line in file.readlines():
    array = line.split(',')
    if array[0] in delete_nodes:
        continue;
    outFile.write(array[0] + ',' + array[1])
file.close()
outFile.close()