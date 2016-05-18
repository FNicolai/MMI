#include "bellman_ford.h"

Bellman_Ford::Bellman_Ford()
{

}

Bellman_Ford::Bellman_Ford(Graph *graph_)
{
    _graph = graph_;
}

double Bellman_Ford::perform_bellman_ford(int start_node_)
{
    // Initializations
    clock_t time_begin = clock();

    double distance[_graph->get_nodes().size()];    // Distance to Node [i]
    Node * prev_node[_graph->get_nodes().size()];   // Previus node from Node [i]

    //Init node_description
    for(auto i = 0; i < _graph->get_nodes().size(); i++) {
        // INFINITY = Distance to Node i is INFINITE
        // NULL = Node i has no prev node at start
        distance[i] = INFINITY;
        prev_node[i] = NULL;
    }

    // Init startnode
    distance[start_node_] = 0;
    prev_node[start_node_] = _graph->get_node(start_node_);

    // Get edgelist "E" and write it to _edges
    get_edgelist(start_node_);

    // Do it n-1 times
    for(auto i = 0; i < _graph->get_nodes().size()-1; i++) {
        // For each (u,v) from E
        for(auto it = _edges.begin(); it != _edges.end(); ++it){

            Edge * curr_edge = it->first;
            Node * u = curr_edge->get_left_node();  // Start node
            Node * v = curr_edge->get_right_node(); // Goal node

            // IF (Distance(u) + Weight(u,v)) < Distance(v)
            if ( (distance[u->get_value()] + u->get_edge_to(v)->get_weight() ) < distance[v->get_value()] ){
                // Distance(v) := Distance(u) + Weight(u,v)
                distance[v->get_value()] = distance[u->get_value()] + u->get_edge_to(v)->get_weight();
                // Prev(v) := u
                prev_node[v->get_value()] = u;
            }

            // If graph is undirected, look at E the other way round too
            if(!_graph->is_directed()){

                Node * v = curr_edge->get_left_node();  // Start node
                Node * u = curr_edge->get_right_node(); // Goal node

                // IF (Distance(u) + Weight(u,v)) < Distance(v)
                if ( (distance[u->get_value()] + u->get_edge_to(v)->get_weight() ) < distance[v->get_value()] ){
                    // Distance(v) := Distance(u) + Weight(u,v)
                    distance[v->get_value()] = distance[u->get_value()] + u->get_edge_to(v)->get_weight();
                    // Prev(v) := u
                    prev_node[v->get_value()] = u;
                }
            }
        }
    }

    // For each (u,v) from E
    for(auto it = _edges.begin(); it != _edges.end(); ++it){

        Edge * curr_edge = it->first;
        Node * u = curr_edge->get_left_node();  // Start node
        Node * v = curr_edge->get_right_node(); // Goal node

        // IF (Distance(u) + Weight(u,v)) < Distance(v)
        if ( (distance[u->get_value()] + u->get_edge_to(v)->get_weight() ) < distance[v->get_value()] ){
            // STOPP and print out that e cycle with negative weight exists
            cout << "Negative cycle found at: (" << u->get_value() << "," << v->get_value() << ")"
                 << " where distance[" << u->get_value() << "] = " << distance[u->get_value()] << " + "
                 << u->get_edge_to(v)->get_weight() << " < " << "distance[" << v->get_value() << "] = "
                 << distance[v->get_value()] <<  endl;
            break;
        }

        // If graph is undirected, look at E the other way round too
        if(!_graph->is_directed()){

            Node * v = curr_edge->get_left_node();  // Start node
            Node * u = curr_edge->get_right_node(); // Goal node

            // IF (Distance(u) + Weight(u,v)) < Distance(v)
            if ( (distance[u->get_value()] + u->get_edge_to(v)->get_weight() ) < distance[v->get_value()] ){
                // STOPP and print out that e cycle with negative weight exists
                cout << "Negative cycle found at: (" << u->get_value() << "," << v->get_value() << ")"
                     << " where distance[" << u->get_value() << "] = " << distance[u->get_value()] << " + "
                     << u->get_edge_to(v)->get_weight() << " < " << "distance[" << v->get_value() << "] = "
                     << distance[v->get_value()] <<  endl;
                break;
            }
        }
    }

    clock_t time_end = clock();

    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;

    if(_debug){
        cout << "Node\tDistance\tPrevious Node" << endl;
        for(int i = 0; i < _graph->get_nodes().size(); i++){
            cout << i << "\t" << distance[i];

            if(prev_node[i] != NULL){
                cout << "\t" << prev_node[i]->get_value() << endl;
            }else{
                cout << "\t" << "-" << endl;
            }
        }
    }

    cout << "The Moore-Bellman-Ford algorithm needed " << elapsed_secs << " seconds to deliver a result." << endl;
}

void Bellman_Ford::get_edgelist(int start_node_)
{
    DFS dfs(_graph);
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
