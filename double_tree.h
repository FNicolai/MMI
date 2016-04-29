#ifndef DOUBLE_TREE_H
#define DOUBLE_TREE_H

#include "graph.h"
#include "kruskal.h"
#include <queue>

// Iterative BFS

class Double_Tree
{
public:
    Double_Tree(Graph * graph);

    void perform_doubleTree(int start_node_value);

    vector<Node *> get_found_nodes();

    Edge* locate_edge_in_orig_graph(int start_node, int end_node);

    void print_tree();

    Kruskal my_kruskal;

private:
    Graph* _graph;
    queue<Node *> _nodes_queue;
    vector<Node *> _found_nodes;
//    vector<Edge*> double_tree_edges;
};

#endif // DOUBLE_TREE_H
