# -*- coding: utf-8 -*-

# Created by saki on 2017/4/30.

import networkx as nx
import matplotlib.pyplot as plt

DG = nx.DiGraph()
file = open('/Users/saki/Desktop/AnomalyDetection/graph/enron_edgelist.txt', 'r')
cnt = 0
for line in file.readlines():
    cnt += 1
    print cnt
    # if cnt >= 1000:
    #     break
    array = line.split('\t')
    DG.add_edge(array[0], array[1])
nx.draw(DG)
# nx.draw_networkx(DG)
plt.show()
file.close()