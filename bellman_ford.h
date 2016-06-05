#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "graph.h"
#include "dfs.h"


class Bellman_Ford
{
public:
    Bellman_Ford();
    Bellman_Ford(Graph *graph_,bool debug_ = true);

    double perform_bellman_ford(int start_node_);
    vector<Node *> get_negative_cycle();
private:
    bool _debug;

    Graph* _graph;

    multimap<Edge *, double> _edges;            // Edges sorted by pointer-value. Double is placeholder

    void get_edgelist(int start_node_);

    void calc_negative_cycle(Node * start_node_);
    void print_negative_cycle();
    vector<Node *> _negative_cycle;

    vector<Node *> _prev_node;
    vector<double> _distance;
};

#endif // BELLMAN_FORD_H
