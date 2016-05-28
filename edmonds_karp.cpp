#include "edmonds_karp.h"

EDMONDS_KARP::EDMONDS_KARP()
{

}

EDMONDS_KARP::EDMONDS_KARP(Graph * graph_, bool debug_)
{
    _graph = graph_;
    _debug = debug_;
    _flow.resize(_graph->get_nodes().size(), 0.0);
}

void EDMONDS_KARP::perform_edmonds_karp(Node *start_node_, Node *end_node_)
{

}

Graph * EDMONDS_KARP::generate_residualgraph(Graph *graph_)
{
    //Init residualgraph graph to return it later
    Graph* residualgraph = new Graph (true,true);
    residualgraph->insert_n_nodes(_graph->get_nodes().size());

    vector<Edge *> edgelist = graph_->get_edgelist();

    for(auto i = 0; i < edgelist.size(); i++){
        Edge * curr_edge = edgelist.at(i);
        Node * start_node = residualgraph->get_node(curr_edge->get_left_node()->get_value());
        Node * end_node = residualgraph->get_node(curr_edge->get_right_node()->get_value());
        double weight = curr_edge->get_weight();
        double flow = curr_edge->get_flow();

        // Insert forward edge into residualgraph if residualcapacity not 0
        // residualcapacity = weight - flow
        if(weight - flow != 0){
            residualgraph->insert_edge_if_not_exist(start_node,end_node,weight-flow);
        }

        // Insert backwards edge into residualgraph if residualcapacity not 0
        // residualcapacity = flow
        if(flow != 0){
            residualgraph->insert_edge_if_not_exist(end_node, start_node, flow);
        }
    }

}
