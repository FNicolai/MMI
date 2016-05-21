#ifndef TSP_BRUTEFORCE_H
#define TSP_BRUTEFORCE_H

#include "graph.h"
#include "dfs.h"
#include <algorithm>
#include <limits.h>


class TSP_Bruteforce
{
public:
    TSP_Bruteforce();
    TSP_Bruteforce(Graph* graph_);

    void perform_tsp_bruteforce(double start_node_value);

private:
    Graph* _graph;

    void visit(Node* node_, vector<bool> nodes_visited_, vector<Node *> tour_);
    vector<Node*> _best_tour;
    double _best_weight;

    double print_tour(vector<Node*> tour_, bool debug_ = true);

    bool _debug;
};

#endif // TSP_BRUTEFORCE_H
