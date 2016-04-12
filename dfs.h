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

    vector<Node *> get_found_nodes();

private:
    Graph* _graph;
    void visit(Node* node);
    vector<Node*> _found_nodes;
};

#endif // DFS_H
