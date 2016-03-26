#include "edge.h"

edge::edge(double goal_node_,double weight_)
{
    _goal_node = goal_node_;
    _weight = weight_;
}

// ### GET and SET methods

double edge::get_goal_node() const
{
    return _goal_node;
}

void edge::set_goal_node(double goal_node_)
{
    _goal_node = goal_node_;
}

double edge::get_weight() const
{
    return _weight;
}

void edge::set_weight(double weight_)
{
    _weight = weight_;
}



// ### Other functions
