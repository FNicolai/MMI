#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "node.h"
#include <queue>

class Dijkstra
{
public:
    Dijkstra(Graph* graph_, bool debug_ = true);
    void perform_dijkstra(int start_node_, int end_node_);

    vector<Node *> get_path();

private:
    Graph* _graph;
    bool _debug;
    int _nodes_count;
    vector<double> distances;
    vector<int> prev_nodes;
    vector<bool> nodes_processed;

    vector<Node *> _path;

    bool every_node_processed();
    int get_unvisited_node_with_least_dist();
    void print_table();
};

#endif // DIJKSTRA_H
