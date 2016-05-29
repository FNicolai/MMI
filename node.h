#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>

// Forward declaration
class Edge;

#include "edge.h"

using namespace std;

class Node
{
public:
    Node();
    Node(int value);

    //bool get_visited() const;
    //void set_visited(bool visited_);

    bool has_edge_to(Node* target_node);
    Edge* get_edge_to(Node* target_node);
    Edge* insert_edge_to(Node* target_node, bool directed, double weight, double flow);

    vector<Edge *> get_edges() const;

    void add_edge(double value_);
    void remove_edge(double value_);

    int get_value();

    double get_group();
    void set_group(double group_);

    void reset_edges();

private:
    int _value;
    //bool _visited = false;   //Already visited?
    double _group; // Group ID for Kruskal

    vector<Edge*> _edges;
};

#endif // NODE_H
