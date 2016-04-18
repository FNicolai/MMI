#ifndef PRIM_H
#define PRIM_H

#include "graph.h"
#include "bfs.h"
#include "dfs.h"
#include <queue>

class Prim
{
public:
    Prim();
    Prim(Graph* graph_);

    double perform_prim();
private:
    struct compare
    {
        bool operator()(pair<Edge*,double> n1,pair<Edge*,double> n2) {
            return n1.second > n2.second;
        }
    };

    void insert_edges(vector<Edge *> edges_);

    Graph* _graph;
    Graph* _MST_graph;

    multimap<Edge *, double> _edges_by_edge; // Edge

    priority_queue<pair<Edge*,double>,vector<pair<Edge*,double>>,compare> _prio_edge_by_weight;
};

#endif // PRIM_H
