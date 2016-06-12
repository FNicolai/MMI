#ifndef CYCLECANCELING_H
#define CYCLECANCELING_H

#include "graph.h"
#include "bellman_ford.h"
#include "edmonds_karp.h"
#include <algorithm>


class Cycle_Canceling
{
public:
    Cycle_Canceling();
    Cycle_Canceling(Graph * graph_, bool debug_ = false);

    void perform_cycle_canceling();

    double get_total_cost() const;

private:
    bool _debug;

    Graph *_graph;

    double _total_cost = 0.0;

    double _max_flow = 0.0;

    Graph *calc_b_flow();
    Graph *add_super_source_and_sink();
    Graph *remove_super_source_and_sink(Graph *super_graph_);
    Graph *generate_residualgraph(Graph *graph_);
    vector<Node *> get_negative_cycle(Graph *graph_);
    double find_min_residualcapacity_on_cycle(Graph * residualgraph_, vector<Node *> negative_cycle_);
    void update_flow(double min_residualcapacity_, vector<Node *> negative_cycle_);

    double calc_total_cost(Graph *graph_);
    double calc_total_negative_balance(Graph *graph_);
};

#endif // CYCLECANCELING_H
