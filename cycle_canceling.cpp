#include "cycle_canceling.h"

Cycle_Canceling::Cycle_Canceling()
{

}

Cycle_Canceling::Cycle_Canceling(Graph *graph_, bool debug_)
{
    _graph = graph_;
    _debug = debug_;
}
