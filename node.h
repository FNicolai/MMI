#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>
#include "edge.h"

using namespace std;

class node
{
public:
    node();

    bool get_visited() const;
    void set_visited(bool visited_);

    vector<edge> get_edges() const;

    void add_edge(double value_);
    void remove_edge(double value_);

private:
    double _value;
    bool _visited = false;   //Alread visited?
    vector<edge> _edges;
};

#endif // NODE_H
