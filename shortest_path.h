#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include "graph.h"
#include "node.h"
#include <queue>

class Shortest_Path
{
public:
    Shortest_Path(Graph* graph_);
    void perform_dijkstra(int start_node_, int end_node_);

private:
    Graph* _graph;
    int _nodes_count;
    vector<double> distances;
    vector<int> prev_nodes;
    vector<bool> nodes_visited;

    bool every_node_visited();
    int get_unvisited_node_with_least_dist();
    void print_table();
};

#endif // SHORTEST_PATH_H
