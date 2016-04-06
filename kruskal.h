#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graph.h"

class KRUSKAL
{
public:
    KRUSKAL();
    KRUSKAL(Graph* graph_);

    void perform_krukal();

private:
    Graph* _graph;
};

#endif // KRUSKAL_H
