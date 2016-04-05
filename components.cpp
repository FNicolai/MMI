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

    double components = 0.;

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

    vector<Node*> nodes = _graph->get_nodes();
    for (size_t i = 0; i < nodes.size(); i++) {
        if(!nodes[i]->get_visited()){
            components++;
            switch(search_input_type_){
                case enum_DFS  :
                   dfs->perform_recursive_DFS(i);
                   break;
                case enum_BFS  :
                   bfs->perform_iterative_BFS(i);
                   break;
            }

        }
    }

    cout << endl << "The graph has " << components << " connected components." << endl;
}
