#ifndef CYCLECANCELING_H
#define CYCLECANCELING_H

#include "graph.h"
#include "bellman_ford.h"

class Cycle_Canceling
{
public:
    Cycle_Canceling();
    Cycle_Canceling(Graph * graph_, bool debug_ = false);

    void perform_cycle_canceling();
private:
    bool _debug;

    Graph* _graph;
};

#endif // CYCLECANCELING_H
