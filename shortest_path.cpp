#include "shortest_path.h"

Shortest_Path::Shortest_Path(Graph* graph_)
{
    _graph = graph_;
    _nodes_count = _graph->get_nodes().size();
}

void Shortest_Path::perform_dijkstra(int start_node_, int end_node_ = INFINITY)
{
    // Initializations
    distances.resize(_nodes_count);
    prev_nodes.resize(_nodes_count);
    nodes_visited.resize(_nodes_count);

    for(auto i = 0; i < _nodes_count; i++)
    {
        distances[i] = INFINITY;
        prev_nodes[i] = NULL;
        nodes_visited[i] = false;
    }

    distances[start_node_] = 0;
    prev_nodes[start_node_] = start_node_;

    Node* cur_node;
    while(!every_node_visited())
    {
        int cur_node_value = get_unvisited_node_with_least_dist();
        if(cur_node_value == -1)
            // Occurs when a node is not reachable
            break;

        cur_node = _graph->get_node(cur_node_value);
        nodes_visited[cur_node_value] = true;

        vector<Edge*> edges = cur_node->get_edges();
        for(auto i = 0; i < edges.size(); i++)
        {
            Node* cur_left_node = edges[i]->get_left_node();
            Node* cur_right_node = edges[i]->get_right_node();
            Node* crp_node;

            // Get corresponding node to cur_node
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

            // Shortest path to end_node_ found
            if(crp_node->get_value() == end_node_)
            {
                cout << "Shortest path from node " << start_node_ << " to node " << end_node_ << " has length " << distances[crp_node->get_value()] << "." << endl;
                return;
            }
        }

        print_table();
    }

    cout << "Shortest path from node " << start_node_ << " to all other nodes has the following connections:" << endl;
    for(int i = 0; i < _nodes_count; i++)
        cout << "Node " << i << " is reachable over node " << prev_nodes[i] << " with distance " << distances[i] << endl;
}

bool Shortest_Path::every_node_visited()
{
    for(auto i = 0; i < _nodes_count; i++)
        if(!nodes_visited[i])
            return false;

    return true;
}

int Shortest_Path::get_unvisited_node_with_least_dist()
{
    double least_dist = INFINITY;
    int unvisited_node_with_least_dist = -1;
    for(auto i = 0; i < _nodes_count; i++)
        if(!nodes_visited[i] && distances[i] < least_dist)
        {
            least_dist = distances[i];
            unvisited_node_with_least_dist = i;
        }

    return unvisited_node_with_least_dist;
}

void Shortest_Path::print_table()
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
        cout << nodes_visited[i] << "\t";
    cout << endl << endl;
}
