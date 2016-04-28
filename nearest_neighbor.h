#ifndef NEAREST_NEIGHBOR_H
#define NEAREST_NEIGHBOR_H

#include "graph.h"
#include <queue>

class Nearest_Neighbor
{
public:
    Nearest_Neighbor();
    Nearest_Neighbor(Graph* graph_);

    double perform_nearest_neighbor(double start_node_);
private:
    struct compare
    {
        bool operator()(pair<Edge*,double> n1,pair<Edge*,double> n2) {
            return n1.second > n2.second;
        }
    };

    void insert_edges(vector<Edge *> edges_);

    Graph* _graph;
    Graph* _MST_graph;

    multimap<Edge *, double> _edges_by_edge; // Edge

    priority_queue<pair<Edge*,double>,vector<pair<Edge*,double>>,compare> _prio_edge_by_weight;

    vector<bool> _nodes_visited;
    bool get_node_visited(Node * node_);
    void set_node_visited(Node *node_, bool status_);
};

#endif // NEAREST_NEIGHBOR_H
