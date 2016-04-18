#include "kruskal.h"

Kruskal::Kruskal()
{

}

Kruskal::Kruskal(Graph *graph_)
{
    _graph = graph_;
}

double Kruskal::perform_kruskal()
{
    DFS dfs(_graph);
    dfs.perform_recursive_DFS(0);

    vector<Node *> found_nodes = dfs.get_found_nodes();

    vector<Edge *> curr_edges;

    _nodes_by_group.resize(found_nodes.size());  //Same amount of groups as found nodes

    for(size_t i=0; i<found_nodes.size(); i++){


        found_nodes[i]->set_group((double)i);

        _nodes_by_group[i].push_back(found_nodes[i]);

        curr_edges = found_nodes[i]->get_edges();
        for(size_t j=0; j<curr_edges.size() ;j++){
            auto it = _edges_by_edge.find(curr_edges[j]);
            if( it == _edges_by_edge.end() ){   //No edge found
                _edges_by_edge.insert(pair<Edge*, double>(curr_edges[j], NAN)); // Save Edge*, second is placeholder
                _edges_by_weight.insert(pair<double, Edge *>(curr_edges[j]->get_weight(),curr_edges[j])); // Save weight and Edge*
            }
        }
    }

    cout << "Found " << _edges_by_edge.size() << " edges." << endl;

//    for(auto it = _edges_by_weight.begin(); it != _edges_by_weight.end(); ++it){
//        cout << "Weight: " << it->first << " from Edge " << it->second->get_left_node()->get_value() << " to " << it->second->get_right_node()->get_value() << endl;
//        //auto it_next = next(it,2);
//        //cout << (*it->second > *it_next->second) <<endl;

//    }

    clock_t time_begin = clock();

    _MST_graph = new Graph (_graph->is_weighted(),_graph->is_directed());

    for(auto i = 0; i < _graph->get_nodes().size(); i++){
        _MST_graph->insert_node_if_not_exist(i);
    }

    double total_MST_weight = 0.;

    for(auto it = _edges_by_weight.begin(); it != _edges_by_weight.end(); ++it){

        Edge * curr_edge = it->second;                                              // Get edge with smalles weight (original graph)
        Node * curr_left_node = curr_edge->get_left_node();                         // Get left node (original graph)
        Node * curr_right_node = curr_edge->get_right_node();                       // Get right node (original graph)

        auto curr_left_node_group = curr_left_node->get_group();                    // Get the group the left node belongs to (original graph)
        auto curr_right_node_group = curr_right_node->get_group();                  // Get the group the right node belongs to (original graph)
        auto group_size_left_node = _nodes_by_group[curr_left_node_group].size();   // Get the groupsize the left node belongs to (original graph)
        auto group_size_right_node = _nodes_by_group[curr_right_node_group].size(); // Get the groupsize the right node belongs to (original graph)

        if( (curr_left_node_group == curr_right_node_group) && (_MST_graph->get_node_visited(curr_left_node) == true && _MST_graph->get_node_visited(curr_right_node) == true) ){
            // Both are in the same group and already visited => loop => do nothing
        }else{
            if(group_size_left_node < group_size_right_node){
                //left group => right group
                _MST_graph->set_node_visited(curr_right_node,true);
                for(auto i = 0; i < group_size_left_node; i++){
                    _nodes_by_group[curr_left_node_group][i]->set_group(curr_right_node_group);                     // Set left group node(s) group to right group (original graph)
                    _MST_graph->set_node_visited(curr_left_node,true);
                    _nodes_by_group[curr_right_node_group].push_back(_nodes_by_group[curr_left_node_group][i]);     // Move (copy) left group node(s) to right node group (original graph)
                }
                _nodes_by_group[curr_left_node_group].clear();                                                      // remove nodes from origin (left) group (original graph)

            }else{
                //right group => left group
                _MST_graph->set_node_visited(curr_left_node,true);
                for(auto i = 0; i < group_size_right_node; i++){
                    _nodes_by_group[curr_right_node_group][i]->set_group(curr_left_node_group);                     // Set right group node(s) group to left group (original graph)
                    _MST_graph->set_node_visited(curr_right_node,true);
                    _nodes_by_group[curr_left_node_group].push_back(_nodes_by_group[curr_right_node_group][i]);     // Move (copy) right group node(s) to left node group (original graph)
                }
                _nodes_by_group[curr_right_node_group].clear();                                                     // remove nodes from origin (right) group (original graph)
            }

            _MST_graph->insert_edge_if_not_exist(curr_left_node,curr_right_node,curr_edge->get_weight());           // Insert new Edge in _MST_graph
            total_MST_weight += curr_edge->get_weight();
        }

    }

    clock_t time_end = clock();

    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;

    cout << "The MST has a total weight of " << total_MST_weight << ". That was calculated in " << elapsed_secs << " seconds." << endl;

    _graph->reset_visited();

    return total_MST_weight;
}
