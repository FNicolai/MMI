#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graph.h"
#include "bfs.h"
#include "dfs.h"
#include <map>
#include <queue>
#include <functional>

class Kruskal
{
public:
    Kruskal();
    Kruskal(Graph* graph_);

    multimap<Edge *, double> perform_kruskal(double start_node_);

private:
    Graph* _graph;

    //Graph* _MST_graph;
    multimap<Edge *, double> _MST_edges;        // To return all found edges that build the MST
    multimap<Edge *, double> _edges_by_edge;    // Edge
    multimap<double,Edge *> _edges_by_weight;   // Weight and Edge

    vector<vector<Node *> > _nodes_by_group;    // "Group"/"Color"/"ID" and Node with his group membership

    vector<bool> _nodes_visited;
    bool get_node_visited(Node * node_);
    void set_node_visited(Node *node_, bool status_);
};

#endif // KRUSKAL_H
