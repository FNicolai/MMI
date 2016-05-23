#include "kruskal.h"

Kruskal::Kruskal()
{

}

Kruskal::Kruskal(Graph *graph_, bool debug_)
{
    _graph = graph_;
    _debug = debug_;
}

Graph* Kruskal::perform_kruskal(double start_node_)
{
    //Init MST graph to return it later
    Graph* MST = new Graph (true,false);
    for(auto i = 0; i < _graph->get_nodes().size(); i++){
        MST->insert_node_if_not_exist(i);
    }

    _nodes_visited.resize(_graph->get_nodes().size(),false);

    DFS dfs(_graph, _debug);
    dfs.perform_recursive_DFS(start_node_);

    vector<Node *> found_nodes = dfs.get_found_nodes();

    vector<Edge *> curr_edges;

    _groups.resize(found_nodes.size());  //Same amount of groups as found nodes

    for(size_t i=0; i<found_nodes.size(); i++){


        found_nodes[i]->set_group((double)i);

        _groups[i].push_back(found_nodes[i]);

        curr_edges = found_nodes[i]->get_edges();
        for(size_t j=0; j<curr_edges.size() ;j++){
            auto it = _edges.find(curr_edges[j]);
            if( it == _edges.end() ){   //No edge found
                _edges.insert(pair<Edge*, double>(curr_edges[j], NAN));                                     // Save Edge*, second is placeholder
                _sorted_edges.insert(pair<double, Edge *>(curr_edges[j]->get_weight(),curr_edges[j]));      // Save weight and Edge*
            }
        }
    }

    if(_debug){
        cout << "Found " << _edges.size() << " edges." << endl;
    }

    clock_t time_begin = clock();

    double total_MST_weight = 0.;

    for(auto it = _sorted_edges.begin(); it != _sorted_edges.end(); ++it){

        Edge * curr_edge = it->second;                                              // Get edge with smalles weight (original graph)
        Node * curr_left_node = curr_edge->get_left_node();                         // Get left node (original graph)
        Node * curr_right_node = curr_edge->get_right_node();                       // Get right node (original graph)

        auto curr_left_node_group = curr_left_node->get_group();                    // Get the group the left node belongs to (original graph)
        auto curr_right_node_group = curr_right_node->get_group();                  // Get the group the right node belongs to (original graph)
        auto group_size_left_node = _groups[curr_left_node_group].size();           // Get the groupsize the left node belongs to (original graph)
        auto group_size_right_node = _groups[curr_right_node_group].size();         // Get the groupsize the right node belongs to (original graph)

        // Both are NOT in the same group => NO loop => do something
        if( curr_left_node_group != curr_right_node_group ){
            if(group_size_left_node < group_size_right_node){
                //left group => right group
                set_node_visited(curr_right_node,true);
                for(auto i = 0; i < group_size_left_node; i++){
                    _groups[curr_left_node_group][i]->set_group(curr_right_node_group);                             // Set left group node(s) group to right group (original graph)
                    set_node_visited(curr_left_node,true);
                    _groups[curr_right_node_group].push_back(_groups[curr_left_node_group][i]);                     // Move (copy) left group node(s) to right node group (original graph)
                }
                _groups[curr_left_node_group].clear();                                                              // remove nodes from origin (left) group (original graph)

            }else{
                //right group => left group
                set_node_visited(curr_left_node,true);
                for(auto i = 0; i < group_size_right_node; i++){
                    _groups[curr_right_node_group][i]->set_group(curr_left_node_group);                             // Set right group node(s) group to left group (original graph)
                    set_node_visited(curr_right_node,true);
                    _groups[curr_left_node_group].push_back(_groups[curr_right_node_group][i]);                     // Move (copy) right group node(s) to left node group (original graph)
                }
                _groups[curr_right_node_group].clear();                                                             // remove nodes from origin (right) group (original graph)
            }

            //_MST_graph->insert_edge_if_not_exist(curr_left_node,curr_right_node,curr_edge->get_weight());         // Insert new Edge in _MST_graph
            MST->insert_edge_if_not_exist(MST->get_node(curr_left_node->get_value()),
                                          MST->get_node(curr_right_node->get_value()),
                                          curr_left_node->get_edge_to(curr_right_node)->get_weight());              // Insert new Edge in MST graph

            _MST_edges.insert(pair<Edge*, double>(curr_edge, NAN));                                                 // Add Edge* to MST, second is placeholder.
            total_MST_weight += curr_edge->get_weight();
        }

    }

    clock_t time_end = clock();

    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;

    cout << "The MST calculated by KRUSKAL has a total weight of " << total_MST_weight << ". That was calculated in " << elapsed_secs << " seconds." << endl;

    return MST;
}

bool Kruskal::get_node_visited(Node *node_)
{
    return _nodes_visited[node_->get_value()];
}

void Kruskal::set_node_visited(Node *node_, bool status_)
{
    _nodes_visited[node_->get_value()] = status_;
}
