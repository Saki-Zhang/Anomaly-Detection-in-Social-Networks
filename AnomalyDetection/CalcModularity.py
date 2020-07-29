# -*- coding: utf-8 -*-

# Created by saki on 2017/5/5.

import sys
import csv
import networkx as nx

def getGraph(path):
    graph = nx.Graph()
    file = open(path, 'rb')
    reader = csv.reader(file)
    for line in reader:
        if line[0] <= line[1]:
            graph.add_edge(line[0], line[1])
        else:
            graph.add_edge(line[1], line[0])
    print '# of Nodes:', len(graph.nodes())
    print '# of Edges:', len(graph.edges())
    return graph

def getCommunity(path):
    dict = {}
    file = open(path, 'rb')
    reader = csv.reader(file)
    for line in reader:
        dict[line[0]] = line[1]
    print '# of Communities:', len(set(dict.values()))
    return dict

def modularity(graph, partition):
    """
    Compute the modularity of a partition of a graph

    Parameters
    ----------
    partition : dict
        the partition of the nodes, i.e a dictionary where keys are their nodes and values the communities
    graph : networkx.Graph
        the networkx graph which is decomposed

    Returns
    -------
    modularity : float
        The modularity

    Raises
    ------
    KeyError
        If the partition is not a partition of all graph nodes
    ValueError
        If the graph has no link
    TypeError
        If graph is not a networkx.Graph

    References
    ----------
    .. 1. Newman, M.E.J. & Girvan, M. Finding and evaluating community structure in networks. Physical Review E 69, 26113(2004).

    Examples
    --------
    >>> G = nx.erdos_renyi_graph(100, 0.01)
    >>> part = best_partition(G)
    >>> modularity(part, G)
    """

    if type(graph) != nx.Graph:
        raise TypeError('Bad graph type, use only non directed graph')

    inc = dict([])
    deg = dict([])
    links = graph.size()
#    links = graph.size(weight = 'weight')

    if links == 0:
        raise ValueError('A graph without link has an undefined modularity')

    for node in graph:
        com = partition[node]
        deg[com] = deg.get(com, 0.0) + graph.degree(node)
#        deg[com] = deg.get(com, 0.0) + graph.degree(node, weight = 'weight')

        for neighbor, datas in graph[node].iteritems():
            weight = datas.get('weight', 1)
            if partition[neighbor] == com:
                if neighbor == node:
                    inc[com] = inc.get(com, 0.0) + float(weight)
                else:
                    inc[com] = inc.get(com, 0.0) + float(weight) / 2.0

    res = 0.0
    for com in set(partition.values()):
        res += (inc.get(com, 0.0) / links) - (deg.get(com, 0.0) / (2.0 * links)) ** 2
    return res

if __name__ == '__main__':
    # Graph File Path
    path1 = '/Users/saki/Desktop/AnomalyDetection/edges/enron.csv' # sys.argv[1]
#    path1 = '/Users/saki/Desktop/AnomalyDetection/cut/enron.csv' # sys.argv[1]
    # Community File Path
    path2 = '/Users/saki/Desktop/AnomalyDetection/comm/enron_kmeans.csv' # sys.argv[2]
#    path2 = '/Users/saki/Desktop/AnomalyDetection/cut/enron_kmeans.csv' # sys.argv[2]

    G = getGraph(path1)
    comm = getCommunity(path2)

    Q = modularity(G, comm)
    print "Modularity Q:", Q