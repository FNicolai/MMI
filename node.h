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
    Node(int value, double balance_ = 0.0);

    //bool get_visited() const;
    //void set_visited(bool visited_);

    bool has_edge_to(Node* target_node);
    Edge* get_edge_to(Node* target_node);
    Edge* insert_edge_to(Node* target_node, bool directed, double weight, double flow = 0.0, double cost = 0.0);

    vector<Edge *> get_edges() const;

    void add_edge(double value_);

    int get_value();

    double get_group();
    void set_group(double group_);

    double get_balance();
    void set_balance(double balance_);

    void reset_edges();

    double get_pseudo_balance() const;
    void set_pseudo_balance(double pseudo_balance_);

private:
    int _value;
    //bool _visited = false;    //Already visited?
    double _group = 0.0;        // Group ID for Kruskal

    double _balance;
    double _pseudo_balance = 0.0;

    vector<Edge*> _edges;
};

#endif // NODE_H
