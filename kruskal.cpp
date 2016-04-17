#include "kruskal.h"

Kruskal::Kruskal()
{

}

Kruskal::Kruskal(Graph *graph_)
{
    _graph = graph_;
}

void Kruskal::perform_kruskal()
{
    DFS dfs(_graph);
    dfs.perform_recursive_DFS(0);

    vector<Node *> found_nodes = dfs.get_found_nodes();

    vector<Edge *> curr_edges;

    _nodes_by_group.resize(found_nodes.size());  //Same amount of groups as found nodes

    //cout << "Found " << _edges_by_edge.size() << " edges." << endl;

//    double * p_group_counter;
//    double group_counter = 0.;

    for(size_t i=0; i<found_nodes.size(); i++){
//        p_group_counter = new double;
//        * p_group_counter = group_counter;
//        _group_by_node.insert(pair<Node *, double *>(found_nodes[i],p_group_counter)); // Save Node* and "Group"/"Color"/"ID"
//        _nodes_by_group.insert(pair<double *,Node *>(p_group_counter,found_nodes[i])); // Save "Group"/"Color"/"ID" and Node *
//        group_counter++;

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



//    _MST_graph = new Graph (_graph->is_weighted(),_graph->is_directed());

//    for(auto i = 0; i < _graph->get_nodes().size(); i++){
//        _MST_graph->insert_node_if_not_exist(i);
//    }

    _MST_graph = new Graph(*_graph);

    _MST_graph->reset_edges();

    for(auto it = _edges_by_weight.begin(); it != _edges_by_weight.end(); ++it){

        Edge * curr_edge = it->second;
        Node * curr_left_node = curr_edge->get_left_node();
        Node * curr_right_node = curr_edge->get_right_node();

        auto curr_left_node_group = curr_left_node->get_group();                    // Get the group the left node belongs to
        auto curr_right_node_group = curr_right_node->get_group();                  // Get the group the right node belongs to
        auto group_size_left_node = _nodes_by_group[curr_left_node_group].size();   // Get the groupsize the left node belongs to
        auto group_size_right_node = _nodes_by_group[curr_right_node_group].size(); // Get the groupsize the right node belongs to

        if( (curr_left_node_group == curr_right_node_group) && (_MST_graph->get_node_visited(curr_left_node) == true && _MST_graph->get_node_visited(curr_right_node) == true) ){
            // Both are in the same group and already visited => loop => do nothing
        }else{
            if(group_size_left_node < group_size_right_node){
                //left group => right group
                _MST_graph->set_node_visited(curr_right_node,true);
                for(auto i = 0; i < group_size_left_node; i++){
                    _nodes_by_group[curr_left_node_group][i]->set_group(curr_right_node_group);                     // Set left group node(s) group to right group
                    _MST_graph->set_node_visited(curr_left_node,true);
                    _nodes_by_group[curr_right_node_group].push_back(_nodes_by_group[curr_left_node_group][i]);     // Move (copy) left group node(s) to right node group
                }
                _nodes_by_group[curr_left_node_group].clear();                                                      // remove nodes from origin (left) group

            }else{
                //right group => left group
                _MST_graph->set_node_visited(curr_left_node,true);
                for(auto i = 0; i < group_size_right_node; i++){
                    _nodes_by_group[curr_right_node_group][i]->set_group(curr_left_node_group);                     // Set right group node(s) group to left group
                    _MST_graph->set_node_visited(curr_right_node,true);
                    _nodes_by_group[curr_left_node_group].push_back(_nodes_by_group[curr_right_node_group][i]);     // Move (copy) right group node(s) to left node group
                }
                _nodes_by_group[curr_right_node_group].clear();                                                      // remove nodes from origin (right) group
            }

            _MST_graph->insert_edge_if_not_exist(curr_left_node,curr_right_node,curr_edge->get_weight());
        }






    }









































//    for(auto it = _edges_by_weight.begin(); it != _edges_by_weight.end(); ++it){
//        Edge * curr_edge = it->second;
//        Node * curr_left_node = curr_edge->get_left_node();
//        Node * curr_right_node = curr_edge->get_right_node();

//        auto it_left_node = _group_by_node.find(curr_left_node);
//        auto it_right_node = _group_by_node.find(curr_right_node);
//        auto group_size_left_node = count(_nodes_by_group.begin(),_nodes_by_group.end(),it_left_node->second);
//        auto group_size_right_node = count(_nodes_by_group.begin(),_nodes_by_group.end(),it_right_node->second);

//        if(group_size_left_node < group_size_right_node){
//            //left group => right group
//            auto ret = _nodes_by_group.equal_range(it_left_node->second);
//            for (auto it=ret.first; it!=ret.second; ++it){
//                it->first
//            }
//        }else{
//            //right group => left group
//        }

//        _MST_graph->insert_edge_if_not_exist(curr_left_node,curr_right_node,curr_edge->get_weight());


//    }


//    for(auto i=0; i < _edges_priority_queue.size(); i++){
//        Edge * curr_edge = _edges_priority_queue.top();
//        _edges_priority_queue.pop();
//        Edge * curr_edge_next = _edges_priority_queue.top();
//        _edges_priority_queue.pop();
//        cout << "Weight: " << curr_edge->get_weight() << " from Edge " << curr_edge->get_left_node()->get_value() << " to " << curr_edge->get_right_node()->get_value() << endl;
//        cout << "Weight: " << curr_edge_next->get_weight() << " from Edge " << curr_edge_next->get_left_node()->get_value() << " to " << curr_edge_next->get_right_node()->get_value() << endl;
//        cout << (*curr_edge < *curr_edge_next) << (*curr_edge > *curr_edge_next) << endl;
//    }


}
