#include "edge.h"

Edge::Edge(Node* left_node, Node* right_node, double weight_, double flow_, double cost_)
{
    this->left_node = left_node;
    this->right_node = right_node;

//    _goal_node = goal_node_;
    _weight = weight_;
    _flow = flow_;
    _cost = cost_;
}

// ### GET and SET methods

Node* Edge::get_right_node() const
{
    return right_node;
}

Node* Edge::get_left_node() const
{
    return left_node;
}

void Edge::set_goal_node(double goal_node_)
{
//    _goal_node = goal_node_;
}

double Edge::get_weight() const
{
    return _weight;
}

double Edge::get_flow() const
{
    return _flow;
}

void Edge::set_flow(double flow_)
{
    _flow = flow_;
}

double Edge::get_cost()
{
    return _cost;
}

void Edge::set_weight(double weight_)
{
    _weight = weight_;
}



// ### Other functions
