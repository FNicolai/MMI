#ifndef EDGE_H
#define EDGE_H

// Forward declaration
class Node;

#include "node.h"

class Edge
{
public:
    Edge(Node* left_node, Node* right_node, double weight_, double flow_ = 0.0, double cost_ = 0.0);

    Node* get_right_node() const;
    Node* get_left_node() const;

//    double get_goal_node() const;
    void set_goal_node(double goal_node_);

    void set_weight(double weight_);
    double get_weight() const;

    double get_flow() const;
    void set_flow(double flow_);

    double get_cost();

    inline bool operator< (const Edge& rhs){ return _weight < rhs._weight; }
    inline bool operator> (const Edge& rhs){ return rhs._weight < _weight; }
    inline bool operator<=(const Edge& rhs){ return !(_weight > rhs._weight); }
    inline bool operator>=(const Edge& rhs){ return !(_weight < rhs._weight); }
    inline bool operator==(const Edge& rhs){ return _weight == rhs._weight; }
    inline bool operator!=(const Edge& rhs){ return !(_weight == rhs._weight); }

private:
//    double _goal_node;       //Goal of edge
    Node * left_node;
    Node * right_node;

    double _weight;     //Weight of edge

    double _flow;       // Flow for edmonds_karp

    double _cost;
};

#endif // EDGE_H
