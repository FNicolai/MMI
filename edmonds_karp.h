#ifndef EDMONDS_KARP_H
#define EDMONDS_KARP_H

#include "graph.h"
#include "dijkstra.h"


class Edmonds_Karp
{
public:
    Edmonds_Karp();
    Edmonds_Karp(Graph * graph_, bool debug_ = true);

    void perform_edmonds_karp(int start_node_, int end_node_);

    double get_flow();
private:
    bool _debug;

    Graph* _graph;

    Graph *generate_residualgraph();
    vector<Node *> calc_shortest_path(Graph * residualgraph_, int start_node_, int end_node_); //Based on edges
    double find_min_residualcapacity_on_path(Graph * residualgraph_, vector<Node *> shortest_path_);
    void update_flow(double min_residualcapacity_, vector<Node *> shortest_path_);

    void print_graph();

    vector<double> _flow; // Return value

    double _max_flow = 0.0;

    void cleanup();

};

#endif // EDMONDS_KARP_H
