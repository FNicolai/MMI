#ifndef BRANCH_AND_BOUND_H
#define BRANCH_AND_BOUND_H

#include "graph.h"
#include <algorithm>
#include <limits.h>

class Branch_and_Bound
{
public:
    Branch_and_Bound();
    Branch_and_Bound(Graph *graph_, bool debug_ = true);

    void perform_branch_and_bound(double start_node_value);

private:
    Graph* _graph;

    void visit(Node* node_, vector<bool> nodes_visited_, vector<Node *> tour_, double weight_);
    vector<Node*> _best_tour;
    double _best_weight;

    double print_tour(vector<Node*> tour_, bool debug_ = true);

    bool _debug;

};

#endif // BRANCH_AND_BOUND_H
