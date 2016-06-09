#include "successive_shortest_path.h"

Successive_Shortest_Path::Successive_Shortest_Path()
{

}

Successive_Shortest_Path::Successive_Shortest_Path(Graph *graph_, bool debug_)
{
    _graph = graph_->create_copy();
    _debug = debug_;
}

void Successive_Shortest_Path::perform_successive_shortest_path()
{
    calc_start_flow_and_pseudo_balance();
    Graph * residualgraph = generate_residualgraph(_graph);
    vector<Node *> shortest_path = calc_shortest_path(residualgraph);
    double min_residualcapacity = find_min_residualcapacity_on_cycle(residualgraph,shortest_path);
    update_flow(min_residualcapacity,shortest_path);

}

void Successive_Shortest_Path::calc_start_flow_and_pseudo_balance()
{
    vector<Edge *> edgelist = _graph->get_edgelist();
    for(auto i = 0; i < edgelist.size(); i++){
        Edge * curr_edge = edgelist.at(i);
        if(curr_edge->get_cost() < 0.0){
            curr_edge->set_flow(curr_edge->get_weight());
        }//else(cost >= 0.0){flow = 0.0} //Pre-Initialized
    }

    vector<Node *> nodes = _graph->get_nodes();
    for(auto i = 0; i < nodes.size(); i++){
        Node * curr_node = nodes.at(i);
        vector<Edge *> curr_edges = curr_node->get_edges();
        for(auto j = 0; j < curr_edges.size(); j++){
            Edge *curr_edge = curr_edges.at(j);
            if(curr_edge->get_cost() < 0.0){
                curr_node->set_pseudo_balance(curr_node->get_pseudo_balance() + curr_edge->get_flow());
                curr_edge->get_right_node()->set_pseudo_balance(curr_edge->get_right_node()->get_pseudo_balance() - curr_edge->get_flow());
            }
        }
    }

    if(_debug){
        cout << "\nCalculatet start flow and pseudo-balance. RESULT:" << endl;
        _graph->print_nodes();
    }

}

Graph *Successive_Shortest_Path::generate_residualgraph(Graph *graph_)
{
    //Init residualgraph graph to return it later
    Graph* residualgraph = new Graph (true,true,Graph::BALANCE);
    residualgraph->insert_n_nodes(graph_->get_nodes().size());
    residualgraph->transfer_balance(graph_);

    vector<Edge *> edgelist = graph_->get_edgelist();

    for(auto i = 0; i < edgelist.size(); i++){
        Edge * curr_edge = edgelist.at(i);
        Node * start_node = residualgraph->get_node(curr_edge->get_left_node()->get_value());
        Node * end_node = residualgraph->get_node(curr_edge->get_right_node()->get_value());
        double weight = curr_edge->get_weight();
        double flow = curr_edge->get_flow();
        double cost = curr_edge->get_cost();

        // Insert forward edge into residualgraph if residualcapacity not 0
        // residualcapacity(flow) = weight - flow
        // cost = cost
        if(weight - flow != 0){
            residualgraph->insert_edge_if_not_exist(start_node,end_node,weight,weight-flow,cost);
            //start_node->get_edge_to(end_node)->set_flow(weight-flow);
        }

        // Insert backwards edge into residualgraph if residualcapacity not 0
        // residualcapacity(flow) = flow
        // cost = cost * -1
        if(flow != 0){
            residualgraph->insert_edge_if_not_exist(end_node, start_node, weight,flow,(cost * -1));
            //end_node->get_edge_to(start_node)->set_flow(flow);
        }
    }

    if(_debug){
        cout << "\nGenerated residualgraph. RESULT:" << endl;
        residualgraph->print_nodes();
    }

    return residualgraph;
}

vector<Node *> Successive_Shortest_Path::calc_shortest_path(Graph *residualgraph_)
{
    //TODO INSERT STOP HERE---SEE PDF
    Bellman_Ford bellman_ford(residualgraph_,_debug);
    for(auto i = 0; i < residualgraph_->get_nodes().size(); i++){
        Node * curr_start_node = residualgraph_->get_node(i);
        if(curr_start_node->get_balance() - curr_start_node->get_pseudo_balance() > 0){
            bellman_ford.perform_bellman_ford(curr_start_node->get_value(),Bellman_Ford::COST);
            for(auto j = 0; j < residualgraph_->get_nodes().size(); j++){
                Node * curr_goal_node = residualgraph_->get_node(j);
                if(curr_start_node != curr_goal_node){
                    if(bellman_ford.get_distance_to(curr_goal_node->get_value()) != INFINITY){
                        if(curr_goal_node->get_balance() - curr_goal_node->get_pseudo_balance() < 0){
                            return bellman_ford.get_path_to(curr_goal_node);
                        }
                    }
                }
            }
        }
    }
}

double Successive_Shortest_Path::find_min_residualcapacity_on_cycle(Graph *residualgraph_, vector<Node *> shortest_path_)
{
    double min_residualcapacity = INFINITY;

    Node * start_node = residualgraph_->get_node(shortest_path_[0]->get_value());
    Node * end_node = residualgraph_->get_node(shortest_path_[shortest_path_.size()-1]->get_value());

    for(auto i = 0; i < shortest_path_.size()-1; i++){
        Node * curr_node = residualgraph_->get_node(shortest_path_[i]->get_value());
        Node * next_node = residualgraph_->get_node(shortest_path_[i+1]->get_value());
        Edge * curr_edge = curr_node->get_edge_to(next_node);

        // Find min( flow, b(s)-b'(s), b'(t)-b(t) )
        double curr_min = min(curr_edge->get_flow(),start_node->get_balance()-start_node->get_pseudo_balance());
        curr_min = min(curr_min,end_node->get_pseudo_balance()-end_node->get_balance());

        if(curr_min < min_residualcapacity){
            min_residualcapacity = curr_min;
        }
    }

    if(_debug){
        cout << "Minimum residualcapacity on given path is: " << min_residualcapacity << endl;
    }

    return min_residualcapacity;
}

void Successive_Shortest_Path::update_flow(double min_residualcapacity_, vector<Node *> shortest_path_)
{
    for(auto i = 0; i < shortest_path_.size()-1; i++){
        Node * curr_node = _graph->get_node(shortest_path_[i]->get_value());
        Node * next_node = _graph->get_node(shortest_path_[i+1]->get_value());
        Edge * curr_edge = curr_node->get_edge_to(next_node);


        if(curr_edge != NULL){
            // Forward edge! Found in orig. graph
            curr_edge->set_flow(curr_edge->get_flow()+min_residualcapacity_);
        }else{
            // Backward edge! Push back flow
            curr_edge = next_node->get_edge_to(curr_node);
            curr_edge->set_flow(curr_edge->get_flow()-min_residualcapacity_);
        }
    }

    // Reset pseudo-balance
    for(auto i = 0; i < shortest_path_.size(); i++){
        Node * curr_node = _graph->get_node(shortest_path_[i]->get_value());
        curr_node->set_pseudo_balance(0.0);
    }

    //TODO:  reset 0,2 but update 4 from 2 ATM. CHANGE THAT!
    vector<Node *> nodes = shortest_path_;
    for(auto i = 0; i < nodes.size(); i++){
        Node * curr_node = _graph->get_node(nodes[i]->get_value());
        vector<Edge *> curr_edges = curr_node->get_edges();
        for(auto j = 0; j < curr_edges.size(); j++){
            Edge *curr_edge = curr_edges.at(j);
            if(curr_edge->get_cost() < 0.0){
                curr_node->set_pseudo_balance(curr_node->get_pseudo_balance() + curr_edge->get_flow());
                curr_edge->get_right_node()->set_pseudo_balance(curr_edge->get_right_node()->get_pseudo_balance() - curr_edge->get_flow());
            }
        }
    }

    _max_flow += min_residualcapacity_;

    if(_debug){
        cout << "\nUpdated flow and pseudo-balance. RESULT:" << endl;
        _graph->print_nodes();
    }
}
