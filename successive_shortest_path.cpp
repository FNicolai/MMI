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
    clock_t time_begin = clock();

    calc_start_flow_and_pseudo_balance();

    bool finished;

    Graph * residualgraph = generate_residualgraph(_graph);
    vector<Node *> shortest_path = calc_shortest_path(residualgraph, finished);

    while(!shortest_path.empty()){
        double min_residualcapacity = find_min_residualcapacity_on_path(residualgraph,shortest_path);
        update_flow(min_residualcapacity,shortest_path);

        residualgraph = generate_residualgraph(_graph);
        shortest_path = calc_shortest_path(residualgraph, finished);
    }

    clock_t time_end = clock();
    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;

    if(finished){

        cout << "\nFinal RESULT:" << endl;

        _graph->print_nodes();

        _total_cost = calc_total_cost(_graph);

        cout << "The total cost of the graph are: " << _total_cost << endl;

        cout << "The Successive shortest path algorithm obtained the result in " << elapsed_secs << " seconds." << endl;

    }else{
       cout << "No b-flow!" << endl;
       cout << "STOPPING algorithm here!" << endl;
    }
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

    calc_pseudo_balance();

    if(_debug){
        cout << "\nCalculatet start flow and pseudo-balance. RESULT:" << endl;
        _graph->print_nodes();
    }

}

void Successive_Shortest_Path::calc_pseudo_balance()
{
    vector<Node *> nodes = _graph->get_nodes();

    // Reset pseudo-balance
    for(auto i = 0; i < nodes.size(); i++){
        Node * curr_node = nodes.at(i);
        curr_node->set_pseudo_balance(0.0);
    }

    for(auto i = 0; i < nodes.size(); i++){
        Node * curr_node = nodes.at(i);
        vector<Edge *> curr_edges = curr_node->get_edges();
        for(auto j = 0; j < curr_edges.size(); j++){
            Edge *curr_edge = curr_edges.at(j);
            //if(curr_edge->get_cost() < 0.0){
                curr_node->set_pseudo_balance(curr_node->get_pseudo_balance() + curr_edge->get_flow());
                curr_edge->get_right_node()->set_pseudo_balance(curr_edge->get_right_node()->get_pseudo_balance() - curr_edge->get_flow());
            //}
        }
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

vector<Node *> Successive_Shortest_Path::calc_shortest_path(Graph *residualgraph_, bool &finished_)
{
    Bellman_Ford bellman_ford(residualgraph_,_debug);
    for(auto i = 0; i < residualgraph_->get_nodes().size(); i++){
        Node * curr_start_node = residualgraph_->get_node(i);

        // Check if curr node is a possible start node. b(s) - b'(s) > 0
        // If theres no start node we are finished or there is now b-flow at all
        // We check that down below
        if(curr_start_node->get_balance() - curr_start_node->get_pseudo_balance() > 0){
            // So we found a valid start node. Let's perform the BF to get the
            // shortest path based on c(e)
            bellman_ford.perform_bellman_ford(curr_start_node->get_value(),Bellman_Ford::COST);
            for(auto j = 0; j < residualgraph_->get_nodes().size(); j++){
                Node * curr_goal_node = residualgraph_->get_node(j);
                // Let's check if there is a valid goal node. b(t) - b'(t) < 0
                // If theres no goal node we are there is now b-flow at all
                // We check that down below

                // Goal node shoudn't be the start node itself
                if(curr_start_node != curr_goal_node){
                    // Goal node should be reachable
                    if(bellman_ford.get_distance_to(curr_goal_node->get_value()) != INFINITY){
                        // The criterion b(t) - b'(t) < 0 should be true
                        if(curr_goal_node->get_balance() - curr_goal_node->get_pseudo_balance() < 0){
                            // We found a valid goal node. Let's get the path and return it.
                            return bellman_ford.get_path(curr_start_node, curr_goal_node);
                        }
                    }
                }
            }
        }
    }

    // The algorithem above hasn't found a
    // valid path.
    // Let's check if we are finished or we have no
    // b-flow at all
    // Finished means all b(v) - b'(v) are 0
    vector<Node*> empty;
    if(proof_finish(residualgraph_)){
        finished_ = true;
        return empty;
    }else{
        finished_ = false;
        return empty;
    }
}

double Successive_Shortest_Path::find_min_residualcapacity_on_path(Graph *residualgraph_, vector<Node *> shortest_path_)
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

    calc_pseudo_balance();

    if(_debug){
        cout << "\nUpdated flow and pseudo-balance. RESULT:" << endl;
        _graph->print_nodes();
    }
}

bool Successive_Shortest_Path::proof_finish(Graph *graph_)
{
    // Check if every's node balance == pseudo-balance
    vector<Node *> nodes = graph_->get_nodes();
    for(auto i = 0; i < nodes.size(); i++){
        Node * curr_node = nodes.at(i);
        if(curr_node->get_balance() != curr_node->get_pseudo_balance()){
            return false;
        }
    }
    return true;
}

double Successive_Shortest_Path::calc_total_cost(Graph *graph_)
{
    double total_cost = 0.0;
    for(auto i = 0; i < graph_->get_edgelist().size(); i++){
        Edge * curr_edge = graph_->get_edgelist().at(i);
        total_cost += curr_edge->get_cost() * curr_edge->get_flow();
    }
    return total_cost;
}
