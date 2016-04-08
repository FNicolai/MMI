#ifndef PRIM_H
#define PRIM_H

#include "graph.h"

class Prim
{
public:
    Prim();
    Prim(Graph* graph_);

    void perform_prim();
private:
    Graph* _graph;
};

#endif // PRIM_H
