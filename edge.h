#ifndef EDGE_H
#define EDGE_H

// Forward declaration
class Node;

#include "node.h"

class Edge
{
public:
    Edge(Node* left_node, Node* right_node, double weight_);

    Node* get_right_node() const;
    Node* get_left_node() const;

//    double get_goal_node() const;
    void set_goal_node(double goal_node_);

    void set_weight(double weight_);
    double get_weight() const;

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
};

#endif // EDGE_H
