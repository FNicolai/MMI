#ifndef BRANCH_AND_BOUND_H
#define BRANCH_AND_BOUND_H

#include "graph.h"
#include "bfs.h"
#include "dfs.h"
#include <queue>
#include <limits.h>


class Branch_and_Bound
{
public:
    Branch_and_Bound();
    Branch_and_Bound(Graph *graph_);

    double perform_brand_and_bound();
private:
    struct compare
    {
        bool operator()(pair<Edge*,double> n1,pair<Edge*,double> n2) {
            return n1.second > n2.second;
        }
    };

    void insert_edges(vector<Edge *> edges_);

    Graph* _graph;
    Graph* _MST_graph;

    multimap<Edge *, double> _edges; // Edge

    priority_queue<pair<Edge*,double>,vector<pair<Edge*,double>>,compare> _sorted_edges;

    vector<bool> _nodes_visited;
    bool get_node_visited(Node * node_);
    void set_node_visited(Node *node_, bool status_);

};

#endif // BRANCH_AND_BOUND_H
