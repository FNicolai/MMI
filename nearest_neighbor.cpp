#include "nearest_neighbor.h"

Nearest_Neighbor::Nearest_Neighbor()
{

}

Nearest_Neighbor::Nearest_Neighbor(Graph *graph_, bool debug_)
{
    _graph = graph_;
    _debug = debug_;
}

double Nearest_Neighbor::perform_nearest_neighbor(double start_node_)
{
    // Initializations
    clock_t time_begin = clock();
    _nodes_visited.resize(_graph->get_nodes().size(),false);
    double total_weight = 0;
    int nodes_counter = _graph->get_nodes().size();

    // Insert start edges
    Node * start_node = _graph->get_node(start_node_);
    insert_edges(start_node->get_edges());
    set_node_visited(start_node,true);
    nodes_counter--;

    for( ; nodes_counter > 0; nodes_counter--){
        // Get edge with minimal weight that has not been used yet
        Edge * curr_edge;
        do{
            curr_edge = _sorted_edges.top().first;
            _sorted_edges.pop();
        }while(get_node_visited(curr_edge->get_left_node()) && get_node_visited(curr_edge->get_right_node()));

        Node * curr_left_node = curr_edge->get_left_node();
        Node * curr_right_node = curr_edge->get_right_node();

        // Proceed with corresponding unused node
        Node * curr_node;
        if(!get_node_visited(curr_left_node)){
            curr_node = curr_left_node;
        }
        else if(!get_node_visited(curr_right_node)){
            curr_node = curr_right_node;
        }

        insert_edges(curr_node->get_edges());
        set_node_visited(curr_node,true);
        total_weight += curr_edge->get_weight();
    }

    // Finish Circle by connecting current node with start node
    while(!_sorted_edges.empty())
    {
        Edge * edge = _sorted_edges.top().first;
        _sorted_edges.pop();

        if(edge->get_left_node() == start_node || edge->get_right_node() == start_node)
        {
            total_weight += edge->get_weight();
            break;
        }
    }

    clock_t time_end = clock();

    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;
    cout << "The nearest neighbor algorithm with start node " << start_node_ << " obtained a hamiltonian circle with a total weight of " << total_weight << " in " << elapsed_secs << " seconds." << endl;

    return total_weight;
}

void Nearest_Neighbor::insert_edges(vector<Edge *> edges_)
{
    _sorted_edges = priority_queue<pair<Edge*,double>,vector<pair<Edge*,double>>,compare>(); // Clear priority queue

    for(auto i=0; i < edges_.size(); i++){
        // TODO: INSERT ONLY THOSE WHO ARE NOT VISITED
        // PRIO queue unneeded here, because of O(n log n) - just check linearly O(n)
        _sorted_edges.push(pair<Edge *,double>(edges_[i],edges_[i]->get_weight()));
    }
}

bool Nearest_Neighbor::get_node_visited(Node *node_)
{
    return _nodes_visited[node_->get_value()];
}

void Nearest_Neighbor::set_node_visited(Node *node_, bool status_)
{
    _nodes_visited[node_->get_value()] = status_;
}
