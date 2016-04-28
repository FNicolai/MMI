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

    multimap<Edge *, double> _edges;            // Edges sorted by pointer-value. Double is placeholder
    multimap<double,Edge *> _sorted_edges;      // Edges sorted by their weight.

    vector<vector<Node *> > _groups;            // "Group"/"Color"/"ID" and Node with his group membership

    vector<bool> _nodes_visited;
    bool get_node_visited(Node * node_);
    void set_node_visited(Node *node_, bool status_);

    //Graph* _MST_graph;
    multimap<Edge *, double> _MST_edges;        // To return all found edges that build the MST
};

#endif // KRUSKAL_H
