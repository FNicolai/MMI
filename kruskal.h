#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graph.h"
#include "bfs.h"
#include "dfs.h"
#include <map>
#include <queue>
#include <functional>

class Kruskal
{
public:
    Kruskal();
    Kruskal(Graph* graph_);

    void perform_kruskal();

private:
    Graph* _graph;
    Graph* _MST_graph;
    multimap<Edge *> _edges_by_edge; // Edge
    multimap<Node *, double> _group_by_node; // Node and "group"/"color"/"id"
    multimap<double,Edge *> _edges_by_weight; // Weight and Edge
    priority_queue<Edge *,vector<Edge *>, greater<Edge*> > _edges_priority_queue;
};

#endif // KRUSKAL_H
