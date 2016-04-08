#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graph.h"

class Kruskal
{
public:
    Kruskal();
    Kruskal(Graph* graph_);

    void perform_kruskal();

private:
    Graph* _graph;
};

#endif // KRUSKAL_H
