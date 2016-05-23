#include "tsp_bruteforce.h"

TSP_Bruteforce::TSP_Bruteforce()
{

}

TSP_Bruteforce::TSP_Bruteforce(Graph *graph_, bool debug_)
{
    _graph = graph_;
    _debug = debug_;
}

void TSP_Bruteforce::perform_tsp_bruteforce(double start_node_value) {

    cout << endl << "recursive TSP bruteforce:" << endl;
    clock_t time_begin = clock();

    _best_weight = INFINITY;

    vector<bool> nodes_visited;
    nodes_visited.resize(_graph->get_nodes().size(),false);

    vector<Node *> tour;

    visit(_graph->get_node(start_node_value), nodes_visited, tour);

    clock_t time_end = clock();

    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;
    cout << "The TSP bruteforce algorithm obtained a hamiltonian circle with a total weight of " << _best_weight << " in " << elapsed_secs << " seconds." << endl;

    cout << "The best tour is: ";
    print_tour(_best_tour);

}

void TSP_Bruteforce::visit(Node* node_, vector<bool> nodes_visited_, vector<Node *> tour_) {

    //cout << node_->get_value();

    tour_.push_back(node_);

    nodes_visited_[node_->get_value()] = true;
    //node->set_visited(true);
    vector<Edge*> cur_edges = node_->get_edges();
    Node* next_node;

    for (uint iE = 0; iE < cur_edges.size(); iE++) {
        next_node = cur_edges[iE]->get_right_node();
        //if (!next_node->get_visited()) {
        if (!nodes_visited_[next_node->get_value()]) {
            //cout << " -> ";
            visit(next_node, nodes_visited_, tour_);
        }
        if(!_graph->is_directed()){
            next_node = cur_edges[iE]->get_left_node();
            //if (!next_node->get_visited()) {
            if (!nodes_visited_[next_node->get_value()]) {
                //cout << " -> ";
                visit(next_node, nodes_visited_, tour_);
            }
        }
    }

    if(tour_.size() == nodes_visited_.size()){
        if(_debug){
            cout << "Found tour: " ;
        }
        double total_weight = print_tour(tour_,_debug);

        if(total_weight < _best_weight){
            _best_weight = total_weight;
            _best_tour = tour_;
        }
    }
}

double TSP_Bruteforce::print_tour(vector<Node*> tour_,bool debug_){

    double total_weight = 0.0;

    if(_debug){
        cout << tour_[0]->get_value();
    }
    for(auto i = 0; i < tour_.size()-1; i++){
        Node * curr_node = tour_[i];
        Node * next_node = tour_[i+1];
        total_weight += curr_node->get_edge_to(next_node)->get_weight();

        if(_debug){
            cout << " -" << total_weight << "-> "<< next_node->get_value();
        }
    }
    total_weight += tour_[tour_.size()-1]->get_edge_to(tour_[0])->get_weight();

    if(_debug){
        cout << " -" << total_weight << "-> " << tour_[0]->get_value() << endl;
    }

    return total_weight;
}

