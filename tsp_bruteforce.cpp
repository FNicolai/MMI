#include "tsp_bruteforce.h"

TSP_Bruteforce::TSP_Bruteforce()
{

}

TSP_Bruteforce::TSP_Bruteforce(Graph *graph_)
{
    _graph = graph_;
}

double TSP_Bruteforce::perform_tsp_bruteforce()
{
    // Initializations
    clock_t time_begin = clock();

    vector<int> nodes(_graph->get_nodes().size());

    //Save 0 to nodes.size in vector<double> nodes
    iota (nodes.begin(), nodes.end(), 0);

    double total_weight = 0.0;
    double best_weight = numeric_limits<double>::max();

    bool debug = false;

    do{
        total_weight = 0.0;
        for (auto i = 0; i < nodes.size()-1; i++){
            int curr_node = nodes.at(i);
            int next_node = nodes.at(i+1);

            total_weight += _graph->get_node(curr_node)->get_edge_to(_graph->get_node(next_node))->get_weight();

            if(debug){
                cout << _graph->get_node(curr_node)->get_value() << " -" << total_weight << "-> ";
            }
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
    cout << "The TSP Bruteforce algorithm obtained a hamiltonian circle with a total weight of " << best_weight << " in " << elapsed_secs << " seconds." << endl;

    return best_weight;
}
