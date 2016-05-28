#ifndef EDMONDS_KARP_H
#define EDMONDS_KARP_H

#include "graph.h"


class EDMONDS_KARP
{
public:
    EDMONDS_KARP();
    EDMONDS_KARP(Graph * graph_, bool debug_);

    void perform_edmonds_karp(Node * start_node_, Node * end_node_);
private:
    bool _debug;

    Graph* _graph;

    Graph * generate_residualgraph(Graph * graph_);

};

#endif // EDMONDS_KARP_H
