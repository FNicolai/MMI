#include "kruskal.h"

Kruskal::Kruskal()
{

}

Kruskal::Kruskal(Graph *graph_)
{
    _graph = graph_;
}

void Kruskal::perform_kruskal()
{
    BFS bfs(_graph);
    bfs.perform_iterative_BFS(0);
    _graph->reset_visited();

    vector<Node *> found_nodes = bfs.get_found_nodes();

    vector<Edge *> curr_edges;

    for(size_t i=0; i<found_nodes.size(); i++){
        curr_edges = found_nodes[i]->get_edges();
        for(size_t j=0; j<curr_edges.size() ;j++){
            map<Edge*,double>::iterator it;
            it = _edges.find(curr_edges[j]);
            if( it == _edges.end() ){   //No edge found
                _edges.insert(pair<Edge*,double>(curr_edges[j],curr_edges[j]->get_weight()));
            }
        }
    }

    cout << "Found " << _edges.size() << " edges." << endl;


}
