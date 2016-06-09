#include "bellman_ford.h"

Bellman_Ford::Bellman_Ford()
{

}

Bellman_Ford::Bellman_Ford(Graph *graph_, bool debug_)
{
    _graph = graph_;
    _debug = debug_;
}

double Bellman_Ford::perform_bellman_ford(int start_node_, Criterion criterion_)
{
    // Initializations
    clock_t time_begin = clock();

    _distance.resize(_graph->get_nodes().size(),INFINITY);  // Distance to Node [i]
    _prev_node.resize(_graph->get_nodes().size(),NULL);     // Previus node from Node [i]

    //Init node_description
//    for(auto i = 0; i < _graph->get_nodes().size(); i++) {
//        // INFINITY = Distance to Node i is INFINITE
//        // NULL = Node i has no prev node at start
//        _distance[i] = INFINITY;
//        _prev_node[i] = NULL;
//    }

    // Init startnode
    _distance[start_node_] = 0;
    _prev_node[start_node_] = _graph->get_node(start_node_);

    // Get edgelist "E" and write it to _edges
    get_edgelist(start_node_);

    // Do it n-1 times
    for(auto i = 0; i < _graph->get_nodes().size()-1; i++) {
        // For each (u,v) from E
        for(auto it = _edges.begin(); it != _edges.end(); ++it){

            Edge * curr_edge = it->first;
            Node * u = curr_edge->get_left_node();  // Start node
            Node * v = curr_edge->get_right_node(); // Goal node
            double weight;
            if(criterion_ == COST){
                weight = u->get_edge_to(v)->get_cost();
            }else {
                weight = u->get_edge_to(v)->get_weight();
            }

            // IF (Distance(u) + Weight(u,v)) < Distance(v)
            if ( (_distance[u->get_value()] + weight ) < _distance[v->get_value()] ){
                // Distance(v) := Distance(u) + Weight(u,v)
                _distance[v->get_value()] = _distance[u->get_value()] + weight;
                // Prev(v) := u
                _prev_node[v->get_value()] = u;
            }

            // If graph is undirected, look at E the other way round too
            if(!_graph->is_directed()){

                Node * v = curr_edge->get_left_node();  // Start node
                Node * u = curr_edge->get_right_node(); // Goal node
                double weight;
                if(criterion_ == COST){
                    weight = u->get_edge_to(v)->get_cost();
                }else {
                    weight = u->get_edge_to(v)->get_weight();
                }

                // IF (Distance(u) + Weight(u,v)) < Distance(v)
                if ( (_distance[u->get_value()] + weight ) < _distance[v->get_value()] ){
                    // Distance(v) := Distance(u) + Weight(u,v)
                    _distance[v->get_value()] = _distance[u->get_value()] + weight;
                    // Prev(v) := u
                    _prev_node[v->get_value()] = u;
                }
            }
        }
    }

    // For each (u,v) from E
    for(auto it = _edges.begin(); it != _edges.end(); ++it){

        Edge * curr_edge = it->first;
        Node * u = curr_edge->get_left_node();  // Start node
        Node * v = curr_edge->get_right_node(); // Goal node
        double weight;
        if(criterion_ == COST){
            weight = u->get_edge_to(v)->get_cost();
        }else {
            weight = u->get_edge_to(v)->get_weight();
        }

        // IF (Distance(u) + Weight(u,v)) < Distance(v)
        if ( (_distance[u->get_value()] + weight ) < _distance[v->get_value()] ){
            // STOPP and print out that e cycle with negative weight exists
            cout << "Negative cycle found at: (" << u->get_value() << "," << v->get_value() << ")"
                 << " where distance[" << u->get_value() << "] = " << _distance[u->get_value()] << " + "
                 << weight << " < " << "distance[" << v->get_value() << "] = "
                 << _distance[v->get_value()] <<  endl;
            calc_negative_cycle(u);
            break;
        }

        // If graph is undirected, look at E the other way round too
        if(!_graph->is_directed()){

            Node * v = curr_edge->get_left_node();  // Start node
            Node * u = curr_edge->get_right_node(); // Goal node
            double weight;
            if(criterion_ == COST){
                weight = u->get_edge_to(v)->get_cost();
            }else {
                weight = u->get_edge_to(v)->get_weight();
            }

            // IF (Distance(u) + Weight(u,v)) < Distance(v)
            if ( (_distance[u->get_value()] + weight ) < _distance[v->get_value()] ){
                // STOPP and print out that e cycle with negative weight exists
                cout << "Negative cycle found at: (" << u->get_value() << "," << v->get_value() << ")"
                     << " where distance[" << u->get_value() << "] = " << _distance[u->get_value()] << " + "
                     << weight << " < " << "distance[" << v->get_value() << "] = "
                     << _distance[v->get_value()] <<  endl;
                calc_negative_cycle(u);
                break;
            }
        }
    }

    clock_t time_end = clock();

    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;

    if(_debug){
        cout << "Node\tDistance\tPrevious Node" << endl;
        for(int i = 0; i < _graph->get_nodes().size(); i++){
            cout << i << "\t" << _distance[i];

            if(_prev_node[i] != NULL){
                cout << "\t" << _prev_node[i]->get_value() << endl;
            }else{
                cout << "\t" << "-" << endl;
            }
        }
    }

    cout << "The Moore-Bellman-Ford algorithm needed " << elapsed_secs << " seconds to deliver a result." << endl;
}

vector<Node *> Bellman_Ford::get_negative_cycle()
{
    return _negative_cycle;
}

double Bellman_Ford::get_distance_to(int goal_node_)
{
    return _distance[goal_node_];
}

vector<Node *> Bellman_Ford::get_path_to(Node * goal_node_)
{
    vector<Node *> path;
    path.push_back(goal_node_);
    Node * prev_node = _prev_node[goal_node_->get_value()];
    do{
        path.push_back(prev_node);
        prev_node = _prev_node[prev_node->get_value()];
    }while(_prev_node[prev_node->get_value()] != prev_node);
    reverse(path.begin(),path.end());

    if(_debug){
        cout << "The path to " << goal_node_->get_value() << " is: ";
        for(auto i = 0; i < path.size()-1; i++){
            cout << path[i]->get_value() << " -> ";
        }
        cout << path[path.size()-1]->get_value() << endl;
    }

    return path;

}

void Bellman_Ford::get_edgelist(int start_node_)
{
    DFS dfs(_graph,_debug);
    dfs.perform_recursive_DFS(start_node_);

    vector<Node *> found_nodes = dfs.get_found_nodes();

    vector<Edge *> curr_edges;

    for(size_t i=0; i<found_nodes.size(); i++){

        curr_edges = found_nodes[i]->get_edges();
        for(size_t j=0; j<curr_edges.size() ;j++){
            auto it = _edges.find(curr_edges[j]);
            if( it == _edges.end() ){   //No edge found
                _edges.insert(pair<Edge*, double>(curr_edges[j], NAN));  // Save Edge*, second is placeholder
            }
        }
    }

    if (_debug){
        cout << "Found " << _edges.size() << " edges." << endl;
    }
}

void Bellman_Ford::calc_negative_cycle(Node *start_node_)
{
    vector<Node *> temp;
    vector<bool> in_cycle;
    in_cycle.resize(_graph->get_nodes().size(), false);

    temp.push_back(start_node_);
    in_cycle[start_node_->get_value()] = true;

    Node * prev_node = _prev_node[start_node_->get_value()];
    do{
        temp.push_back(prev_node);
        in_cycle[prev_node->get_value()] = true;
        prev_node = _prev_node[prev_node->get_value()];
    }
    while(in_cycle[prev_node->get_value()] == false);

    auto it = temp.end();
    it--;
    auto it_start = it;
    do{
        _negative_cycle.push_back(*it);
        it--;
    }
    while(prev_node != *it);
    _negative_cycle.push_back(*it);
    _negative_cycle.push_back(*it_start);

    if(_debug){
        print_negative_cycle();
    }
}

void Bellman_Ford::print_negative_cycle()
{
    cout << "The negative cycle is: ";
    for(auto i = 0; i < _negative_cycle.size()-1; i++){
        cout << _negative_cycle[i]->get_value() << " -> ";
    }
    cout << _negative_cycle[_negative_cycle.size()-1]->get_value() << endl;
}
