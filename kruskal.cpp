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

    cout << "Found " << _edges_by_edge.size() << " edges." << endl;

    double group_counter = 0;

    for(size_t i=0; i<found_nodes.size(); i++){
        _group_by_node.insert(pair<Node *, double>(found_nodes[i],group_counter)); //Save Node* and group/color/id
        group_counter++;
        curr_edges = found_nodes[i]->get_edges();
        for(size_t j=0; j<curr_edges.size() ;j++){
            auto it = _edges_by_edge.find(curr_edges[j]);
            if( it == _edges_by_edge.end() ){   //No edge found
                _edges_by_edge.insert(pair<Edge*>(curr_edges[j])); // Save Edge*
                _edges_by_weight.insert(pair<double, Edge *>(curr_edges[j]->get_weight(),curr_edges[j])); // Save weight and Edge*
                //_edges_priority_queue.push(curr_edges[j]);
            }
        }
    }

    cout << "Found " << _edges_by_edge.size() << " edges." << endl;

//    for(auto it = _edges_by_weight.begin(); it != _edges_by_weight.end(); ++it){
//        cout << "Weight: " << it->first << " from Edge " << it->second->get_left_node()->get_value() << " to " << it->second->get_right_node()->get_value() << endl;
//        //auto it_next = next(it,2);
//        //cout << (*it->second > *it_next->second) <<endl;

//    }

    _MST_graph = new Graph (_graph->is_weighted(),_graph->is_directed());

    for(auto i = 0; i < _graph->get_nodes().size(); i++){
        _MST_graph->insert_node_if_not_exist(i);
    }

    for(auto it = _edges_by_weight.begin(); it != _edges_by_weight.end(); ++it){
        Edge * curr_edge = it->first;
        Node * curr_left_node = curr_edge->get_left_node();
        Node * curr_right_node = curr_edge->get_right_node();

        _MST_graph->insert_edge_if_not_exist(curr_left_node,curr_right_node,curr_edge->get_weight());
        auto it_left_node = _group_by_node.find(curr_left_node);
        auto it_right_node = _group_by_node.find(curr_right_node);
        it_left_node->second = it_right_node->second;

    }


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
