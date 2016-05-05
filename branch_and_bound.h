#ifndef BRANCH_AND_BOUND_H
#define BRANCH_AND_BOUND_H

#include "graph.h"
#include <algorithm>
#include <limits.h>

class Branch_and_Bound
{
public:
    Branch_and_Bound();
    Branch_and_Bound(Graph *graph_);

    double perform_brand_and_bound();
private:
    Graph* _graph;

    int factorial(int x);
};

#endif // BRANCH_AND_BOUND_H
