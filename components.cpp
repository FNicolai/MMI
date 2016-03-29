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
    cout << endl << "Count connected components of graph ";

    double components;

    DFS * dfs;
    BFS * bfs;

    switch(search_input_type_){
        case enum_DFS  :
           dfs = new DFS (_graph);
           cout << "with DFS." << endl;
           break;
        case enum_BFS  :
           bfs = new BFS (_graph);
           cout << "with BFS." << endl;
           break;
    }

    unordered_map<double, Node*> nodes = _graph->get_nodes();
    std::unordered_map<double, Node*>::iterator nodes_iterator;
    for (nodes_iterator = nodes.begin(); nodes_iterator != nodes.end(); nodes_iterator++) {
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

    cout << endl << "The graph has " << components << " connected components." << endl;
}
