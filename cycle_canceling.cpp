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
    clock_t time_begin = clock();

    Graph *b_flow = calc_b_flow();

    if(b_flow != NULL){

        _graph = b_flow;

        Graph * residualgraph = generate_residualgraph(_graph);
        vector<Node *> negative_cycle = get_negative_cycle(residualgraph);

        while(!negative_cycle.empty()){
            double min_residualcapacity = find_min_residualcapacity_on_cycle(residualgraph,negative_cycle);
            update_flow(min_residualcapacity,negative_cycle);
            residualgraph = generate_residualgraph(_graph);
            negative_cycle = get_negative_cycle(residualgraph);
        }
    }

    clock_t time_end = clock();
    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;

    cout << "\nFinal RESULT:" << endl;

    _graph->print_nodes();

    _total_cost = calc_total_cost(_graph);

    cout << "Maximum flow of the graph is: " << _max_flow << endl;

    cout << "The total cost of the graph are: " << _total_cost << endl;

    cout << "The Cycle-Canceling algorithm obtained the result in " << elapsed_secs << " seconds." << endl;
}

double Cycle_Canceling::get_total_cost() const
{
    return _total_cost;
}

Graph *Cycle_Canceling::calc_b_flow()
{
    Graph * super_graph = add_super_source_and_sink();

    Node * super_start_node = super_graph->get_node((super_graph->get_nodes().size())-2);
    Node * super_end_node = super_graph->get_node((super_graph->get_nodes().size())-1);

    Edmonds_Karp edmonds_karp(super_graph,_debug);
    Graph * b_flow = edmonds_karp.perform_edmonds_karp(super_start_node->get_value(),super_end_node->get_value());
    _max_flow = edmonds_karp.get_max_flow();

    if(_debug){
        cout << "\nCalculatet b flow. RESULT:" << endl;
        b_flow->print_nodes();
    }

    double max_negative_balance = calc_max_negative_balance(b_flow);

    if(max_negative_balance < (_max_flow * -1) ){
        // NO b-flow !
        // BREAK
        cout << "\nNO b-flow! Max negative balance is " << max_negative_balance
             << " and smaller than (max flow * -1) which is: " << _max_flow * -1 << " !" << endl;

        cout << "STOPPING algorithm here!" << endl;
        return NULL;
    }

    b_flow = remove_super_source_and_sink(b_flow);

    return b_flow;
}

Graph *Cycle_Canceling::add_super_source_and_sink()
{
    Graph * super_graph = _graph->create_copy();

    super_graph->insert_n_nodes(2);
    Node * super_start_node = super_graph->get_node((super_graph->get_nodes().size())-2);
    Node * super_end_node = super_graph->get_node((super_graph->get_nodes().size())-1);

    for(auto i = 0; i < super_graph->get_nodes().size()-2;i++){
        if(super_graph->get_node(i)->get_balance() > 0){
            // Add to super source
            super_graph->insert_edge_if_not_exist(super_start_node,super_graph->get_node(i),super_graph->get_node(i)->get_balance(),0.0,0.0);
        }else if(super_graph->get_node(i)->get_balance() < 0){
            // Add to super sink
            super_graph->insert_edge_if_not_exist(super_graph->get_node(i),super_end_node,super_graph->get_node(i)->get_balance()*-1,0.0,0.0);
        }
    }

    if(_debug){
        cout << "\nAdded super source and super sink. RESULT:" << endl;
        super_graph->print_nodes();
    }

    return super_graph;
}

Graph * Cycle_Canceling::remove_super_source_and_sink(Graph *super_graph_)
{

    Node * super_start_node = super_graph_->get_node((super_graph_->get_nodes().size())-2);
    Node * super_end_node = super_graph_->get_node((super_graph_->get_nodes().size())-1);

    Graph * copy = new Graph (super_graph_->is_weighted(),super_graph_->is_directed(),super_graph_->get_input_type());
    copy->insert_n_nodes(super_graph_->get_nodes().size()-2);

    for(auto x = 0; x < copy->get_nodes().size(); x++){
        copy->get_node(x)->set_balance(super_graph_->get_node(x)->get_balance());
    }

    vector<Edge *> edgelist = super_graph_->get_edgelist();
    for(auto i = 0; i < edgelist.size(); i++){
        Edge * curr_edge = edgelist.at(i);
        if(curr_edge->get_left_node()->get_value() != super_start_node->get_value()
                && curr_edge->get_right_node()->get_value() != super_start_node->get_value()
                && curr_edge->get_left_node()->get_value() != super_end_node->get_value()
                && curr_edge->get_right_node()->get_value() != super_end_node->get_value()){

            Node * start_node = copy->get_node(curr_edge->get_left_node()->get_value());
            Node * end_node = copy->get_node(curr_edge->get_right_node()->get_value());
            double weight = curr_edge->get_weight();
            double flow = curr_edge->get_flow();
            double cost = curr_edge->get_cost();

            copy->insert_edge_if_not_exist(start_node, end_node, weight, flow, cost);
        }
    }

    if(_debug){
        cout << "\nRemoved super source and super sink. RESULT:" << endl;
        copy->print_nodes();
    }

    return copy;
}

Graph *Cycle_Canceling::generate_residualgraph(Graph *graph_)
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

vector<Node *> Cycle_Canceling::get_negative_cycle(Graph *graph_)
{
    Bellman_Ford bellman_ford(graph_,_debug);
    vector<Node*> negative_cycle;
    for(auto i = 0; i < graph_->get_nodes().size(); i++){
        bellman_ford.perform_bellman_ford(i,Bellman_Ford::COST);
        negative_cycle = bellman_ford.get_negative_cycle();
        if(!negative_cycle.empty()){
            break;
        }
    }
    return negative_cycle;
}

double Cycle_Canceling::find_min_residualcapacity_on_cycle(Graph *residualgraph_, vector<Node *> negative_cycle_)
{
    double min_residualcapacity = INFINITY;

    for(auto i = 0; i < negative_cycle_.size()-1; i++){
        Node * curr_node = residualgraph_->get_node(negative_cycle_[i]->get_value());
        Node * next_node = residualgraph_->get_node(negative_cycle_[i+1]->get_value());
        Edge * curr_edge = curr_node->get_edge_to(next_node);
        if(curr_edge->get_flow() < min_residualcapacity){
            min_residualcapacity = curr_edge->get_flow();
        }
    }

    if(_debug){
        cout << "Minimum residualcapacity on given cycle is: " << min_residualcapacity << endl;
    }

    return min_residualcapacity;
}

void Cycle_Canceling::update_flow(double min_residualcapacity_, vector<Node *> negative_cycle_)
{
    for(auto i = 0; i < negative_cycle_.size()-1; i++){
        Node * curr_node = _graph->get_node(negative_cycle_[i]->get_value());
        Node * next_node = _graph->get_node(negative_cycle_[i+1]->get_value());
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

    if(_debug){
        cout << "\nUpdated flow. RESULT:" << endl;
        _graph->print_nodes();
    }
}

double Cycle_Canceling::calc_total_cost(Graph * graph_)
{
    double total_cost = 0.0;
    for(auto i = 0; i < graph_->get_edgelist().size(); i++){
        Edge * curr_edge = graph_->get_edgelist().at(i);
        total_cost += curr_edge->get_cost() * curr_edge->get_flow();
    }
    return total_cost;
}

double Cycle_Canceling::calc_max_negative_balance(Graph * graph_)
{
    double max_negative_balance = 0.0;
    for(auto i = 0; i < graph_->get_nodes().size(); i++){
        Node * curr_node = graph_->get_node(i);
        if(curr_node->get_balance() < 0){
            max_negative_balance += curr_node->get_balance();
        }
    }

    if(_debug){
        cout << "\nMax negative balance is: " << max_negative_balance << endl;
    }

    return max_negative_balance;
}
