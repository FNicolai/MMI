#include "dijkstra.h"

Dijkstra::Dijkstra(Graph* graph_, bool debug_)
{
    _graph = graph_;
    _nodes_count = _graph->get_nodes().size();
    _debug = debug_;
}

// TODO: Endnode = NULL or -1
void Dijkstra::perform_dijkstra(int start_node_, int end_node_ = INFINITY)
{
    // Initializations
    clock_t time_begin = clock();

    distances.resize(_nodes_count);
    prev_nodes.resize(_nodes_count);
    nodes_processed.resize(_nodes_count);

    for(auto i = 0; i < _nodes_count; i++)
    {
        distances[i] = INFINITY;
        prev_nodes[i] = NULL;
        nodes_processed[i] = false;
    }

    distances[start_node_] = 0;
    prev_nodes[start_node_] = start_node_;

    Node* cur_node;

    // TODO: FOR N NODES
    while(!every_node_processed())
    {
        int cur_node_value = get_unvisited_node_with_least_dist();
        if(cur_node_value == -1)
            break; // Occurs when a node is not reachable

        // Shortest path to end_node_ found
        if(cur_node_value == end_node_)
        {
            cout << "Shortest path from node " << start_node_ << " to node " << end_node_ << " has length " << distances[cur_node_value] << "." << endl;

            clock_t time_end = clock();
            double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;
            cout << "The Dijkstra algorithm obtained the result in " << elapsed_secs << " seconds." << endl;

            auto i = end_node_;
            do{
                _path.push_back(_graph->get_node(i));
                i = prev_nodes[i];
            }while(i != start_node_);

            _path.push_back(_graph->get_node(start_node_));

            reverse(_path.begin(),_path.end());

            if(_debug){
                cout << "Path: ";
                for(auto x: _path){
                    cout << x->get_value() << " ";
                }
                cout << endl;
            }

            return;
        }

        cur_node = _graph->get_node(cur_node_value);
        nodes_processed[cur_node_value] = true;

        vector<Edge*> edges = cur_node->get_edges();
        for(auto i = 0; i < edges.size(); i++)
        {
            Node* cur_left_node = edges[i]->get_left_node();
            Node* cur_right_node = edges[i]->get_right_node();
            Node* crp_node; // Corresponding node

            // Get corresponding node to cur_node
            //TODO: METHOD GIVE OTHER NODE OF EDGE
            if(edges[i]->get_left_node() != cur_node)
                crp_node = cur_left_node;
            else
                crp_node = cur_right_node;

            // Update distance (and prev_node) if distance is lower distance is possible when using edges[i] to reach crp_node
            if(distances[cur_node->get_value()] + edges[i]->get_weight() < distances[crp_node->get_value()])
            {
                distances[crp_node->get_value()] = distances[cur_node->get_value()] + edges[i]->get_weight();
                prev_nodes[crp_node->get_value()] = cur_node->get_value();
            }
        }

        if(_debug)
            print_table();
    }

    clock_t time_end = clock();

    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;

    if(_debug){
        cout << "Shortest path from node " << start_node_ << " to all other nodes has the following connections:" << endl;
        for(int i = 0; i < _nodes_count; i++){
            cout << "Node " << i << " is reachable over node " << prev_nodes[i] << " with distance " << distances[i] << endl;
        }
    }

    cout << "The Dijkstra algorithm obtained the result in " << elapsed_secs << " seconds." << endl;
}

vector<Node *> Dijkstra::get_path()
{
    return _path;
}

bool Dijkstra::every_node_processed()
{
    for(auto i = 0; i < _nodes_count; i++)
        if(!nodes_processed[i])
            return false;

    return true;
}

int Dijkstra::get_unvisited_node_with_least_dist()
{
    double least_dist = INFINITY;
    int unvisited_node_with_least_dist = -1;
    for(auto i = 0; i < _nodes_count; i++)
        if(!nodes_processed[i] && distances[i] < least_dist)
        {
            least_dist = distances[i];
            unvisited_node_with_least_dist = i;
        }

    return unvisited_node_with_least_dist;
}

void Dijkstra::print_table()
{
    cout << "distance: ";
    for(auto i = 0; i < _nodes_count; i++)
        cout << distances[i] << "\t";
    cout << endl;

    cout << "previous: ";
    for(auto i = 0; i < _nodes_count; i++)
        cout << prev_nodes[i] << "\t";
    cout << endl;

    cout << "visited:  ";
    for(auto i = 0; i < _nodes_count; i++)
        cout << nodes_processed[i] << "\t";
    cout << endl << endl;
}
