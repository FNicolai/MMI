#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "edge.h"

#include <vector>
#include <iostream>

#include <QString>

using namespace std;

class Graph
{
public:
    Graph(bool weighted_, bool directed, bool is_adjacency_matrix_, QString filename_);

    bool get_weighted() const;
    bool get_directed() const;
    void add_node(node new_node_);                                // Add nodes to the graph
    bool get_is_adjacency_matrix() const;

private:
    vector<node> _nodes;


    bool _weighted;             //Is the given graph weighted?
    bool _directed;             //Is the given graph directed?
    bool _is_adjacency_matrix;  //In what kind of matrixtype has the given graph
    QString _filename;          //Where is the given graph located

    void read_graph(QString _filename);             // Read graph from given file

};

#endif // GRAPH_H
