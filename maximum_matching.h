#ifndef MAXIMUM_MATCHING_H
#define MAXIMUM_MATCHING_H

#include "graph.h"
#include "edmonds_karp.h"

class Maximum_Matching
{
public:
    Maximum_Matching();
    Maximum_Matching(Graph *graph_,bool debug_ = true);

    void perform_maximum_matching();
private:
    bool _debug;

    Graph* _graph;
};

#endif // MAXIMUM_MATCHING_H
