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
    DFS(Graph * graph, bool debug_);

    void perform_recursive_DFS(double start_node_value);

    vector<Node *> get_found_nodes();

private:
    Graph* _graph;
    void visit(Node* node);
    vector<Node*> _found_nodes;

    vector<bool> _nodes_visited;
    bool get_node_visited(Node * node_);
    void set_node_visited(Node *node_, bool status_);

    bool _debug;
};

#endif // DFS_H
