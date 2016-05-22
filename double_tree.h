#ifndef DOUBLE_TREE_H
#define DOUBLE_TREE_H

#include "graph.h"
#include "kruskal.h"
#include <queue>
#include "bfs.h"

// Iterative BFS

class Double_Tree
{
public:
    Double_Tree(Graph * graph, bool debug_);

    double perform_double_tree(int start_node_value);

    vector<Node *> get_tour;

    Kruskal _kruskal;

private:
    Graph* _graph;

    vector<Node *> _tour;

    bool _debug;

    double print_tour(vector<Node*> path_);
};

#endif // DOUBLE_TREE_H
