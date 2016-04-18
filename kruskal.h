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

    double perform_kruskal();

private:
    Graph* _graph;
    Graph* _MST_graph;
    multimap<Edge *, double> _edges_by_edge; // Edge
    multimap<double,Edge *> _edges_by_weight; // Weight and Edge

    vector<vector<Node *> > _nodes_by_group; // "Group"/"Color"/"ID" and Node with his group membership
};

#endif // KRUSKAL_H
