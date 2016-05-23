#include "components.h"

Components::Components()
{

}

Components::Components(Graph *graph_, bool debug_)
{
    _graph = graph_;
    _debug = debug_;
}

double Components::perform_connected_compontents(SearchInputType search_input_type_)
{
    cout << endl << "Count connected components of graph ";

    double components = 0.;

    DFS * dfs;
    BFS * bfs;

    switch(search_input_type_){
    case enum_DFS  :
        dfs = new DFS (_graph, _debug);
        cout << "with DFS." << endl;
        break;
    case enum_BFS  :
        bfs = new BFS (_graph, _debug);
        cout << "with BFS." << endl;
        break;
    }

    vector<Node *> nodes = _graph->get_nodes();
    vector<Node *> visited_nodes;
    vector<Node *> found_nodes;

    for (size_t i = 0; i < nodes.size(); i++) {
        vector<Node *>::iterator it;
        it = find (visited_nodes.begin(), visited_nodes.end(), nodes[i]);
        if(it == visited_nodes.end()){ //No node found => not visited yet
            components++;
            switch(search_input_type_){
            case enum_DFS  :
                dfs->perform_recursive_DFS(i);
                found_nodes = dfs->get_found_nodes();
                break;
            case enum_BFS  :
                bfs->perform_iterative_BFS(i);
                found_nodes = bfs->get_found_nodes();
                break;
            }
            visited_nodes.insert(visited_nodes.end(),found_nodes.begin(),found_nodes.end());

        }
    }

    cout << endl << "The graph has " << components << " connected components." << endl;
}
