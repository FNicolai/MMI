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
    // Initializations
    clock_t time_begin = clock();

    vector<double> nodes(_graph->get_nodes().size());

    //Save 0 to nodes.size in vector<double> nodes
    iota (nodes.begin(), nodes.end(), 0);

    double total_weight = 0.0;
    double best_weight = numeric_limits<double>::max();
    bool break_it = false;

    bool debug = false;

    do{
        total_weight = 0.0;
        break_it = false;
        for (auto i = 0; i < nodes.size()-1; i++){
            int curr_node = nodes.at(i);
            int next_node = nodes.at(i+1);

            total_weight += _graph->get_node(curr_node)->get_edge_to(_graph->get_node(next_node))->get_weight();

            if(debug){
                cout << _graph->get_node(curr_node)->get_value() << " -" << total_weight << "-> ";
            }

            if(total_weight > best_weight){
                if(debug){
                    cout << "\nBREAK: At this point the costs (" << total_weight
                         << ") of the current path are higher than the current best weight ("
                         << best_weight << ")." << endl;
                }
                break_it = true;
                break;
            }
        }
        if (break_it){
            continue;
        }
        total_weight += _graph->get_node(nodes.at(nodes.size()-1))->get_edge_to(_graph->get_node(nodes.at(0)))->get_weight();
        if(debug){
            cout << _graph->get_node(nodes.at(nodes.size()-1))->get_value() << " -" << total_weight << "-> " << _graph->get_node(nodes.at(0))->get_value() << endl;
        }

        if(total_weight < best_weight){
            best_weight = total_weight;
        }
    }while (next_permutation(nodes.begin(), nodes.end()));

    clock_t time_end = clock();

    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;
    cout << "The Brand and Bound algorithm obtained a hamiltonian circle with a total weight of " << best_weight << " in " << elapsed_secs << " seconds." << endl;

    return best_weight;
}

