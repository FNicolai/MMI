#include "branch_and_bound.h"

Branch_and_Bound::Branch_and_Bound()
{

}

Branch_and_Bound::Branch_and_Bound(Graph *graph_)
{
    _graph = graph_;
}

double Branch_and_Bound::perform_brand_and_bound()
{
    cout << "\nStart Branch and Bound:" << endl;
    // Initializations
    clock_t time_begin = clock();

    double best_weight = numeric_limits<double>::max();
    double total_weight = 0.0;
    double prev_total_weight = 0.0;

    _nodes_visited.resize(_graph->get_nodes().size(),false);

    for(int i = 0; i < _graph->get_nodes().size(); i++ ){

        //Initialize the current run
        bool break_it =  false;
        fill(_nodes_visited.begin(), _nodes_visited.end(), false);
        total_weight = 0.0;
        int nodes_counter = _graph->get_nodes().size();

        // Insert start edges
        Node * start_node = _graph->get_node(i);
        insert_edges(start_node->get_edges());
        set_node_visited(start_node,true);
        nodes_counter--;

        cout << start_node->get_value();

        for( ; nodes_counter > 0; nodes_counter--){

            //bool break_it = false;
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
            //Insert edge into new hamilton graph here (if you want)
            total_weight += curr_edge->get_weight();
            cout << " -" << total_weight << "-> " << curr_node->get_value();

            // After the first found hamilton circle compare the
            // new total_weight with the old/best weight
            // If the new one is worse the old, cancel
            if(i >= 1){
                if( total_weight > prev_total_weight){
                    cout << "\nBREAK! The current costs of " << total_weight
                         << " are higher than the current best found hamiltion path with cost of "
                         << best_weight << "." << endl << endl;
                    break_it = true;
                    break;
                }
            }
        }

        if(break_it){
            continue;
        }

        // Finish Circle by connecting current node with start node
        while(!_sorted_edges.empty())
        {
            Edge * edge = _sorted_edges.top().first;
            _sorted_edges.pop();

            if(edge->get_left_node() == start_node || edge->get_right_node() == start_node)
            {
                total_weight += edge->get_weight();
                cout << " -" << total_weight << "-> " << start_node->get_value() << endl << endl;
                break;
            }
        }

        prev_total_weight = total_weight;

        if(total_weight < best_weight){
            best_weight = total_weight;
        }
    }



    clock_t time_end = clock();

    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;
    cout << "The branch and bound algorithm obtained a hamiltonian circle as best with a total weight of " << best_weight << " in " << elapsed_secs << " seconds." << endl;

    return best_weight;
}

void Branch_and_Bound::insert_edges(vector<Edge *> edges_)
{
    _sorted_edges = priority_queue<pair<Edge*,double>,vector<pair<Edge*,double>>,compare>(); // Clear priority queue

    for(auto i=0; i < edges_.size(); i++){
        _sorted_edges.push(pair<Edge *,double>(edges_[i],edges_[i]->get_weight()));
    }
}

bool Branch_and_Bound::get_node_visited(Node *node_)
{
    return _nodes_visited[node_->get_value()];
}

void Branch_and_Bound::set_node_visited(Node *node_, bool status_)
{
    _nodes_visited[node_->get_value()] = status_;
}
