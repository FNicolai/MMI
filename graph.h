#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "edge.h"

#include <vector>
#include <iostream>

#include <QString>

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <unordered_map>

using namespace std;

class Graph
{
public:
    Graph(bool weighted_, bool directed, bool is_adjacency_matrix_, QString filename_);

    inline bool is_weighted() const;
    inline bool is_directed() const;
    inline bool is_adjacency_matrix() const;
    void add_node(Node new_node_);                                // Add nodes to the graph
    Node* get_node(double value);

private:
    vector<Node*> _nodes;

    bool _is_weighted;             //Is the given graph weighted?
    bool _is_directed;             //Is the given graph directed?
    bool _is_adjacency_matrix;  //In what kind of matrixtype has the given graph
    QString _filename;          //Where is the given graph located

    std::unordered_map<double, Node*> nodes;

//    std::unordered_map<Edge*, std::vector<Node*> > edges_to_nodes;
    std::unordered_map<Node*, std::vector<Edge*> > nodes_to_edges;

    void read_graph(QString _filename);             // Read graph from given file
    Node* insert_node_if_not_exist(double value);
    bool insert_edge_if_not_exist(Node* start_node, Node* end_node);
    void insert_edge(double start_value, double end_value);

};

#endif // GRAPH_H
