#ifndef DFS_H
#define DFS_H

#include "graph.h"
#include "unordered_map"
#include <stack>

// Iterative BFS

class DFS
{
public:
    DFS();
    DFS(Graph * graph);

    void perform_recursive_DFS(double start_node_value);

private:
    Graph* _graph;
    stack<Node*> nodes_queue;
    void visit(Node* node);
};

#endif // DFS_H
