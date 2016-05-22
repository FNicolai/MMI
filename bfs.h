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
    BFS(Graph * graph, bool debug_);

    void perform_iterative_BFS(int start_node_value);

    vector<Node *> get_found_nodes();

private:
    Graph* _graph;
    queue<Node *> _nodes_queue;
    vector<Node *> _found_nodes;

    vector<bool> _nodes_visited;
    bool get_node_visited(Node * node_);
    void set_node_visited(Node *node_, bool status_);

    bool _debug;
};

#endif // BFS_H
