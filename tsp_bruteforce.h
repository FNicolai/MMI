#ifndef TSP_BRUTEFORCE_H
#define TSP_BRUTEFORCE_H

#include "graph.h"
#include <algorithm>
#include <limits.h>


class TSP_Bruteforce
{
public:
    TSP_Bruteforce();
    TSP_Bruteforce(Graph* graph_, bool debug_ = true);

    void perform_tsp_bruteforce(double start_node_value);

private:
    Graph* _graph;
    bool _debug;

    void visit(Node* node_, vector<bool> nodes_visited_, vector<Node *> tour_);
    vector<Node*> _best_tour;
    double _best_weight;

    double print_tour(vector<Node*> tour_, bool debug_ = true);    
};

#endif // TSP_BRUTEFORCE_H
