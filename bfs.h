#ifndef BFS_H
#define BFS_H

#include "graph.h"
#include "unordered_map"
#include <queue>

// Iterative BFS

class BFS
{
public:
    BFS();
    BFS(Graph * graph);

    void perform_iterative_BFS(double start_node_value);

private:
    Graph* _graph;
    queue<Node*> nodes_queue;
};

#endif // BFS_H
