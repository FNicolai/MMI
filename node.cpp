#include "node.h"
#include "edge.h"

node::node()
{

}

// ### GET and SET methods

bool node::get_visited() const
{
    return _visited;
}

void node::set_visited(bool visited_)
{
    _visited = visited_;
}

vector<edge> node::get_edges() const
{
    return _edges;
}


// ### Other functions

void node::add_edge(double value_)
{

}
