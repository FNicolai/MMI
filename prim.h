#ifndef PRIM_H
#define PRIM_H

#include "graph.h"

class PRIM
{
public:
    PRIM();
    PRIM(Graph* graph_);
private:
    Graph* _graph;
};

#endif // PRIM_H
