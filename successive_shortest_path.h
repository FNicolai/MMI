#ifndef SUCCESSIVE_SHORTEST_PATH_H
#define SUCCESSIVE_SHORTEST_PATH_H

#include "graph.h"
#include "bellman_ford.h"
#include "edmonds_karp.h"
#include <algorithm>

class Successive_Shortest_Path
{
public:
    Successive_Shortest_Path();
    Successive_Shortest_Path(Graph * graph_, bool debug_ = false);

    void perform_successive_shortest_path();

private:
    bool _debug;

    Graph *_graph;

    double _total_cost = 0.0;

    double _max_flow = 0.0;

    void calc_start_flow_and_pseudo_balance();
    Graph *generate_residualgraph(Graph *graph_);
    vector<Node *> calc_shortest_path(Graph * residualgraph_);
    double find_min_residualcapacity_on_cycle(Graph * residualgraph_, vector<Node *> shortest_path_);
    void update_flow(double min_residualcapacity_, vector<Node *> shortest_path_);
};

#endif // SUCCESSIVE_SHORTEST_PATH_H
