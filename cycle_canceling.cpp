#include "cycle_canceling.h"

Cycle_Canceling::Cycle_Canceling()
{

}

Cycle_Canceling::Cycle_Canceling(Graph *graph_, bool debug_)
{
    _graph = graph_->create_copy();
    _debug = debug_;
}

void Cycle_Canceling::perform_cycle_canceling()
{
    add_super_source_and_sink();
}

void Cycle_Canceling::add_super_source_and_sink()
{
    _graph->insert_n_nodes(2);
    _start_node = _graph->get_node((_graph->get_nodes().size())-2);
    _end_node = _graph->get_node((_graph->get_nodes().size())-1);

    for(auto i = 0; i < _graph->get_nodes().size()-2;i++){
        if(_graph->get_node(i)->get_balance() > 0){
            // Add to super source
            _graph->insert_edge_if_not_exist(_start_node,_graph->get_node(i),_graph->get_node(i)->get_balance(),0.0,0.0);
        }else if(_graph->get_node(i)->get_balance() < 0){
            // Add to super sink
            _graph->insert_edge_if_not_exist(_graph->get_node(i),_end_node,_graph->get_node(i)->get_balance()*-1,0.0,0.0);
        }
    }

    if(_debug){
        _graph->print_nodes();
    }
}
