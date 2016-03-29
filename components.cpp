#include "components.h"

Components::Components()
{

}

Components::Components(Graph *graph_)
{
    _graph = graph_;
}

double Components::perform_connected_compontents(SearchInputType search_input_type_)
{
    double components;

    DFS * dfs;
    BFS * bfs;

    switch(search_input_type_){
        case enum_DFS  :
           dfs = new DFS (_graph);
           break;
        case enum_BFS  :
           bfs = new BFS (_graph);
           break;
    }

    std::unordered_map<double, Node*>::iterator nodes_iterator;
    for (nodes_iterator = _graph->get_nodes().begin(); nodes_iterator != _graph->get_nodes().end(); nodes_iterator++) {
        if(!nodes_iterator->second->get_visited()){
            components++;
            switch(search_input_type_){
                case enum_DFS  :
                   dfs->perform_recursive_DFS(nodes_iterator->first);
                   break;
                case enum_BFS  :
                   bfs->perform_iterative_BFS(nodes_iterator->first);;
                   break;
            }

        }
    }

    cout << "The graph has " << components << " components." << endl;
}
