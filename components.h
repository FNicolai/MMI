#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "graph.h"
#include "unordered_map"
#include "bfs.h"
#include "dfs.h"

// ### Connected compontents


class Components
{
public:
    Components();
    Components(Graph* graph_, bool debug_  = true);

    enum SearchInputType {enum_DFS, enum_BFS};

    double perform_connected_compontents(SearchInputType search_input_type_);
public:
    Graph* _graph;
    bool _debug;
};

#endif // COMPONENTS_H
