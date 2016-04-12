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

    void perform_iterative_BFS(int start_node_value);

    vector<Node *> get_found_nodes();

private:
    Graph* _graph;
    queue<Node *> _nodes_queue;
    vector<Node *> _found_nodes;
};

#endif // BFS_H
