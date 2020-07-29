# -*- coding: utf-8 -*-

# Created by saki on 2017/4/30.

from sklearn.cluster import KMeans
import numpy as np
import string

file = open('/Users/saki/Desktop/AnomalyDetection/feat/enron_feat.txt', 'r')

n_nodes = 0
nodes = []
vectors = []
for line in file.readlines():
    n_nodes += 1
    array = line.split(' ')
    nodes.append([array[0], array[17].strip()])
    vec = []
    for i in range(1, 18):
        vec.append(string.atof(array[i]))
    # print n_nodes, vec
    vectors.append(vec)
file.close()
emb = np.array(vectors)
k_clusters = 70
print 'Nodes:', n_nodes
print 'Clusters:', k_clusters
kmeans = KMeans(n_clusters = k_clusters).fit(emb)
print kmeans.cluster_centers_

outFile = open('/Users/saki/Desktop/AnomalyDetection/comm/enron_kmeans.csv', 'w')
num = 0
for label in kmeans.labels_:
    outFile.write(nodes[num][0] + ',' + str(label) + '\n')
    num += 1
outFile.close()