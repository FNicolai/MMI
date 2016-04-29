#include "prim.h"

Prim::Prim()
{

}

Prim::Prim(Graph *graph_)
{
    _graph = graph_;
}

multimap<Edge *, double> Prim::perform_prim(double start_node_)
{
    clock_t time_begin = clock();

    _nodes_visited.resize(_graph->get_nodes().size(),false);

    double total_MST_weight = 0.;

    int nodes_counter = _graph->get_nodes().size();

//    _MST_graph = new Graph (_graph->is_weighted(),_graph->is_directed());

//    for(auto i = 0; i < _graph->get_nodes().size(); i++){
//        _MST_graph->insert_node_if_not_exist(i);
//    }

    Node * curr_node = _graph->get_node(start_node_); // Start node
    set_node_visited(curr_node,true);
    vector <Edge *> curr_edges = curr_node->get_edges();
    nodes_counter--;

    insert_edges(curr_edges);                                           // Insert starting edges

    while(nodes_counter != 0){
        Edge * curr_edge = _sorted_edges.top().first;                   // Get Edge with minimal weight (original graph)
        _sorted_edges.pop();
        Node * curr_left_node = curr_edge->get_left_node();             // Get left node (original graph)
        Node * curr_right_node = curr_edge->get_right_node();           // Get right node (original graph)

        if(!get_node_visited(curr_left_node)){
            insert_edges(curr_left_node->get_edges());
            set_node_visited(curr_left_node,true);
            //_MST_graph->insert_edge_if_not_exist(curr_left_node,curr_right_node,curr_edge->get_weight());
            _MST_edges.insert(pair<Edge*, double>(curr_edge, NAN));     // Add Edge* to MST, second is placeholder.
            total_MST_weight += curr_edge->get_weight();
            nodes_counter--;
        }

        if(!get_node_visited(curr_right_node)){
            insert_edges(curr_right_node->get_edges());
            set_node_visited(curr_right_node,true);
            //_MST_graph->insert_edge_if_not_exist(curr_left_node,curr_right_node,curr_edge->get_weight());
            _MST_edges.insert(pair<Edge*, double>(curr_edge, NAN));     // Add Edge* to MST, second is placeholder.
            total_MST_weight += curr_edge->get_weight();
            nodes_counter--;
        }

    }

    clock_t time_end = clock();

    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;
    cout << "The MST calculated by PRIM has a total weight of " << total_MST_weight << ". That was calculated in " << elapsed_secs << " seconds." << endl;

    return _MST_edges;

}

void Prim::insert_edges(vector<Edge *> edges_)
{
    for(auto i=0; i < edges_.size(); i++){
        // For all edges of the node
        // Insert to map to check if edge is already inserted
        // If NOT, insert it into map and priority qeue
        auto it = _edges.find(edges_[i]);
        if( it == _edges.end() ){   //No edge found
            _edges.insert(pair<Edge*, double>(edges_[i], NAN)); // Save Edge*, second is placeholder
            _sorted_edges.push(pair<Edge *,double>(edges_[i],edges_[i]->get_weight()));
        }
    }
}

bool Prim::get_node_visited(Node *node_)
{
    return _nodes_visited[node_->get_value()];
}

void Prim::set_node_visited(Node *node_, bool status_)
{
    _nodes_visited[node_->get_value()] = status_;
}
