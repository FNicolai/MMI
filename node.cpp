#include "node.h"

Node::Node()
{

}

Node::Node(double value)
{
    _value = value;
}

// ### GET and SET methods

double Node::get_value()
{
    return _value;
}

bool Node::get_visited() const
{
    return _visited;
}

void Node::set_visited(bool visited_)
{
    _visited = visited_;
}

vector<Edge *> Node::get_edges() const
{
    return _edges;
}

Edge* Node::get_edge_to(Node *target_node) {
    Edge* retVal = NULL;

    for (int i = 0; i < _edges.size(); i++) {
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

Edge* Node::insert_edge_to(Node *target_node, bool directed) {
    Edge* retVal = get_edge_to(target_node);

    if (retVal == NULL) {
        retVal = new Edge(this, target_node, 0);
        _edges.push_back(retVal);
    }

    if (!directed) {
        target_node->insert_edge_to(this, false);
    }
    return retVal;
}


// ### Other functions

void Node::add_edge(double value_)
{

}
