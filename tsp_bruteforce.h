#ifndef TSP_BRUTEFORCE_H
#define TSP_BRUTEFORCE_H

#include "graph.h"
#include <algorithm>
#include <limits.h>

class TSP_Bruteforce
{
public:
    TSP_Bruteforce();
    TSP_Bruteforce(Graph* graph_);

    double perform_tsp_bruteforce();
private:
    Graph* _graph;
};

#endif // TSP_BRUTEFORCE_H
