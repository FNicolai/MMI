#include "double_tree.h"

Double_Tree::Double_Tree(Graph* graph, bool debug_)
{
    _graph = graph;
    _debug = debug_;
}

double Double_Tree::perform_double_tree(int start_node_value_) {

    // Graph based on Kruskal required in order to perform BFS
    Graph* graph_for_search;

    _kruskal = Kruskal(_graph);
    graph_for_search = _kruskal.perform_kruskal(start_node_value_);

    clock_t time_begin = clock();

    BFS bfs (graph_for_search);
    bfs.perform_iterative_BFS(start_node_value_);
    vector<Node *> path = bfs.get_found_nodes();

    double total_weight = print_tour(path);

    _tour = path;
    _tour.push_back(path.at(0));

    clock_t time_end = clock();

    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;

    cout << endl << "Total weight gathered by Double Tree is " << total_weight << ". This took " << elapsed_secs << " seconds." << endl;

    return total_weight;
}

double Double_Tree::print_tour(vector<Node*> path_){

    double total_weight = 0.0;

    if(_debug){
        cout << "Found tour: ";
        cout << path_[0]->get_value();
    }
    for(auto i = 0; i < path_.size()-1; i++){
        Node * curr_node = path_[i];
        Node * next_node = path_[i+1];

        // Geth weight of edge in original graph. So shortcuts are done.
        total_weight += _graph->get_node(curr_node->get_value())->get_edge_to(_graph->get_node(next_node->get_value()))->get_weight();

        if(_debug){
            cout << " -" << total_weight << "-> "<< next_node->get_value();
        }
    }
    total_weight += _graph->get_node(path_[path_.size()-1]->get_value())->get_edge_to(_graph->get_node(path_[0]->get_value()))->get_weight();

    if(_debug){
        cout << " -" << total_weight << "-> " << path_[0]->get_value() << endl;
    }

    return total_weight;
}
