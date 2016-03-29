#include "components.h"

Components::Components()
{

}

Components::Components(Graph *graph_)
{
    _graph = graph_;
}

double Components::perform_connected_compontents()
{
    double components;
    BFS bfs(_graph);

    std::unordered_map<double, Node*>::iterator nodes_iterator;
    for (nodes_iterator = _graph->get_nodes().begin(); nodes_iterator != _graph->get_nodes().end(); nodes_iterator++) {
        if(!nodes_iterator->second->get_visited()){
            components++;
            bfs.perform_iterative_BFS(nodes_iterator->first);
        }
    }

    cout << "The graph has " << components << " components." << endl;
}
