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

    multimap<Edge *, double> perform_prim(double start_node_);
private:
    struct compare
    {
        bool operator()(pair<Edge*,double> n1,pair<Edge*,double> n2) {
            return n1.second > n2.second;
        }
    };

    void insert_edges(vector<Edge *> edges_);

    Graph* _graph;

    multimap<Edge *, double> _MST_edges;        // To return all found edges that build the MST
    //Graph* _MST_graph;

    multimap<Edge *, double> _edges_by_edge; // Edge

    priority_queue<pair<Edge*,double>,vector<pair<Edge*,double>>,compare> _prio_edge_by_weight;

    vector<bool> _nodes_visited;
    bool get_node_visited(Node * node_);
    void set_node_visited(Node *node_, bool status_);
};

#endif // PRIM_H
