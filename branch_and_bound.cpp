#include "branch_and_bound.h"

Branch_and_Bound::Branch_and_Bound()
{

}

Branch_and_Bound::Branch_and_Bound(Graph *graph_, bool debug_)
{
    _graph = graph_;
    _debug = debug_;
}

void Branch_and_Bound::perform_branch_and_bound(double start_node_value) {

    cout << endl << "recursive TSP Branch and Bound:" << endl;
    clock_t time_begin = clock();

    _best_weight = INFINITY;

    vector<bool> nodes_visited;
    nodes_visited.resize(_graph->get_nodes().size(),false);

    vector<Node *> tour;

    double weight = 0.0;

    visit(_graph->get_node(start_node_value), nodes_visited, tour, weight);

    clock_t time_end = clock();

    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;
    cout << "The TSP branch and bound algorithm obtained a hamiltonian circle with a total weight of " << _best_weight << " in " << elapsed_secs << " seconds." << endl;

    cout << "The best tour is: ";
    print_tour(_best_tour);

}

void Branch_and_Bound::visit(Node* node_, vector<bool> nodes_visited_, vector<Node *> tour_, double weight_) {

    if(weight_ > _best_weight){
        if(_debug){
            cout << "BREAK: Costs of " << weight_
                 << " are higher than the best found tour with costs of "
                 << _best_weight  << "."<< endl;
        }
        return;
    }

    tour_.push_back(node_);

    nodes_visited_[node_->get_value()] = true;

    vector<Edge*> cur_edges = node_->get_edges();
    Node* next_node;

    // TODO: MAKE COUNTER, CHANGE PARAMS TO REFERENCE,
    if(tour_.size() == nodes_visited_.size()){
        if(_debug){
            cout << "Found tour: " ;
        }
        double total_weight = print_tour(tour_,_debug);

        if(total_weight < _best_weight){
            _best_weight = total_weight;
            _best_tour = tour_;
        }
    }else{
        for (uint iE = 0; iE < cur_edges.size(); iE++) {
            next_node = cur_edges[iE]->get_right_node();

            if (!nodes_visited_[next_node->get_value()]) {
                visit(next_node, nodes_visited_, tour_, weight_+node_->get_edge_to(next_node)->get_weight() );
            }
            if(!_graph->is_directed()){
                next_node = cur_edges[iE]->get_left_node();

                if (!nodes_visited_[next_node->get_value()]) {
                    visit(next_node, nodes_visited_, tour_, weight_+node_->get_edge_to(next_node)->get_weight() );
                }
            }
        }
    }


}

double Branch_and_Bound::print_tour(vector<Node*> tour_,bool debug_){

    double total_weight = 0.0;

    if(debug_){
        cout << tour_[0]->get_value();
    }
    for(auto i = 0; i < tour_.size()-1; i++){
        Node * curr_node = tour_[i];
        Node * next_node = tour_[i+1];
        total_weight += curr_node->get_edge_to(next_node)->get_weight();

        if(debug_){
            cout << " -" << total_weight << "-> "<< next_node->get_value();
        }
    }
    total_weight += tour_[tour_.size()-1]->get_edge_to(tour_[0])->get_weight();

    if(total_weight > _best_weight){
        if(_debug){
            cout << endl << "BREAK: Costs of " << total_weight
                 << " are higher than the best found tour with costs of "
                 << _best_weight  << "."<< endl;
        }
    }else if(debug_){
        cout << " -" << total_weight << "-> " << tour_[0]->get_value() << endl;
    }

    return total_weight;
}

