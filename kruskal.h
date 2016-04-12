#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graph.h"
#include "bfs.h"
#include <map>

class Kruskal
{
public:
    Kruskal();
    Kruskal(Graph* graph_);

    void perform_kruskal();

private:
    Graph* _graph;
    map<Edge*,double> _edges;
};

#endif // KRUSKAL_H
