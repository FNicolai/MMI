#include "edmonds_karp.h"

Edmonds_Karp::Edmonds_Karp()
{

}

Edmonds_Karp::Edmonds_Karp(Graph * graph_, bool debug_)
{
    _graph = graph_;
    _debug = debug_;
    _flow.resize(_graph->get_nodes().size(), 0.0);
}

void Edmonds_Karp::perform_edmonds_karp(int start_node_,int end_node_)
{
    // Initializations
    clock_t time_begin = clock();
    Graph * residualgraph = generate_residualgraph();
    vector<Node *> shortest_path = calc_shortest_path(residualgraph, start_node_, end_node_);

    while(!shortest_path.empty()){

        double min_residualcapacity = find_min_residualcapacity_on_path(residualgraph, shortest_path);
        update_flow(min_residualcapacity, shortest_path);
        if(_debug){
            print_graph();
        }
        residualgraph = generate_residualgraph();
        shortest_path = calc_shortest_path(residualgraph, start_node_, end_node_);
    }

    clock_t time_end = clock();

    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;

    print_graph();

    cout << "Maximum flow of graph is: " << _max_flow << endl;

    cout << "The Edmonds-Karp algorithm obtained the result in " << elapsed_secs << " seconds." << endl;

    cleanup();
}

Graph * Edmonds_Karp::generate_residualgraph()
{
    //Init residualgraph graph to return it later
    Graph* residualgraph = new Graph (true,true);
    residualgraph->insert_n_nodes(_graph->get_nodes().size());

    vector<Edge *> edgelist = _graph->get_edgelist();

    for(auto i = 0; i < edgelist.size(); i++){
        Edge * curr_edge = edgelist.at(i);
        Node * start_node = residualgraph->get_node(curr_edge->get_left_node()->get_value());
        Node * end_node = residualgraph->get_node(curr_edge->get_right_node()->get_value());
        double weight = curr_edge->get_weight();
        double flow = curr_edge->get_flow();

        // Insert forward edge into residualgraph if residualcapacity not 0
        // residualcapacity(flow) = weight - flow
        if(weight - flow != 0){
            residualgraph->insert_edge_if_not_exist(start_node,end_node,weight,weight-flow);
            //start_node->get_edge_to(end_node)->set_flow(weight-flow);
        }

        // Insert backwards edge into residualgraph if residualcapacity not 0
        // residualcapacity(flow) = flow
        if(flow != 0){
            residualgraph->insert_edge_if_not_exist(end_node, start_node, weight,flow);
            //end_node->get_edge_to(start_node)->set_flow(flow);
        }
    }
    return residualgraph;
}

vector<Node *> Edmonds_Karp::calc_shortest_path(Graph *residualgraph_, int start_node_, int end_node_)
{
    //Init calc_graph to perform dijkstra
    Graph* calc_graph = residualgraph_->create_copy();

    vector<Edge *> edgelist = calc_graph->get_edgelist();
    for(auto i = 0; i < edgelist.size(); i++){
        Edge * curr_edge = edgelist.at(i);
        curr_edge->set_weight(1);
    }

    Dijkstra dijkstra(calc_graph, _debug);
    dijkstra.perform_dijkstra(start_node_, end_node_);
    vector<Node *> shortest_path = dijkstra.get_path();

    if(_debug){
        cout << "Shortest path: ";
        for (auto i: shortest_path){
            cout << i->get_value() << " ";
        }
        cout << endl;
    }

    return shortest_path;
}

double Edmonds_Karp::find_min_residualcapacity_on_path(Graph *residualgraph_, vector<Node *> shortest_path_)
{
    double min_residualcapacity = INFINITY;

    for(auto i = 0; i < shortest_path_.size()-1; i++){
        Node * curr_node = residualgraph_->get_node(shortest_path_[i]->get_value());
        Node * next_node = residualgraph_->get_node(shortest_path_[i+1]->get_value());
        Edge * curr_edge = curr_node->get_edge_to(next_node);
        if(curr_edge->get_flow() < min_residualcapacity){
            min_residualcapacity = curr_edge->get_flow();
        }
    }

    if(_debug){
        cout << "Minimum residualcapacity on given path is: " << min_residualcapacity << endl;
    }

    return min_residualcapacity;
}

void Edmonds_Karp::update_flow(double min_residualcapacity_, vector<Node *> shortest_path_)
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

    _max_flow += min_residualcapacity_;
}

void Edmonds_Karp::print_graph()
{
    if (_debug){
        cout << "Node\t#Edges\tadjacent_nodes (flow/capacity)" << endl;

        for (auto i = 0; i < _graph->get_nodes().size(); i++) {
            vector<Edge*> cur_edges = _graph->get_node(i)->get_edges();
            cout << i << "\t" << cur_edges.size() << "\t";

            for (auto j = 0; j < cur_edges.size(); j++) {
                if (cur_edges[j]->get_right_node()->get_value() == _graph->get_node(i)->get_value()){
                    cout << cur_edges[j]->get_left_node()->get_value();
                }else{
                    cout << cur_edges[j]->get_right_node()->get_value();
                }

                cout << " (" << cur_edges[j]->get_flow() << "/" << cur_edges[j]->get_weight() << ")";

                cout <<  "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void Edmonds_Karp::cleanup()
{
    vector<Edge *> edgelist = _graph->get_edgelist();
    for(auto i = 0; i < edgelist.size(); i++){
        Edge * curr_edge = edgelist.at(i);
        curr_edge->set_flow(0.0);
    }
}
