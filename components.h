#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "graph.h"
#include "unordered_map"
#include <stack>
#include "bfs.h"
#include "dfs.h"

// ### Connected compontents


class Components
{
public:
    Components();
    Components(Graph* graph_);

    double perform_connected_compontents();
public:
    Graph* _graph;
};

#endif // COMPONENTS_H
