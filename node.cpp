#include "node.h"

Node::Node()
{
    _value = 0;
}

Node::Node(int value, double balance_)
{
    _value = value;
    _balance = balance_;
}

// ### GET and SET methods

int Node::get_value()
{
    return _value;
}

double Node::get_group()
{
    return _group;
}

void Node::set_group(double group_)
{
    _group = group_;
}

double Node::get_balance()
{
    return _balance;
}

void Node::set_balance(double balance_)
{
    _balance = balance_;
}

void Node::reset_edges()
{
    _edges.clear();
}

//bool Node::get_visited() const
//{
//    return _visited;
//}

//void Node::set_visited(bool visited_)
//{
//    _visited = visited_;
//}

vector<Edge *> Node::get_edges() const
{
    return _edges;
}

Edge* Node::get_edge_to(Node *target_node) {
    Edge* retVal = NULL;

    for (size_t i = 0; i < _edges.size(); i++) {
        if (
                _edges[i]->get_right_node() == target_node ||
                _edges[i]->get_left_node() == target_node
                ) {
            retVal = _edges[i];
            break;
        }
    }
    return retVal;
}

bool Node::has_edge_to(Node *target_node) {
    return get_edge_to(target_node) != NULL;
}

Edge* Node::insert_edge_to(Node *target_node, bool directed, double weight, double flow, double cost) {
    Edge* retVal = get_edge_to(target_node);

    if (retVal == NULL) {
        retVal = new Edge(this, target_node, weight, flow, cost);
        _edges.push_back(retVal);

        if (!directed) {
            target_node->_edges.push_back(retVal);
            //target_node->insert_edge_to(this, true, weight);
        }
    }

    return retVal;
}

// ### Other functions

void Node::add_edge(double value_)
{

}
