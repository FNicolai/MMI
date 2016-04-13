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
    enum GraphInputType {EDGELIST, ADJACENCY_MATRIX};
    Graph();
    Graph(bool weighted_, bool directed_);
    Graph(bool weighted_, bool directed_, GraphInputType graph_input_type, QString filename_);

    inline bool is_weighted() const;
    inline bool is_directed() const;
    inline bool is_adjacency_matrix() const;
    inline bool is_edgelist() const;

    Node* get_node(int value);
    void reset_visited();
//    unordered_map<double, Node*> get_nodes();
    vector<Node*> get_nodes();
    Node* insert_node_if_not_exist(int value);
    bool insert_edge_if_not_exist(Node* start_node, Node* end_node, double weight);

private:

    bool _is_weighted;             //Is the given graph weighted?
    bool _is_directed;             //Is the given graph directed?
    GraphInputType _input_type;    //In what kind of matrixtype has the given graph
    QString _filename;          //Where is the given graph located

//    std::unordered_map<double, Node*> nodes;
    vector<Node*> nodes;

//    std::unordered_map<Edge*, std::vector<Node*> > edges_to_nodes;
    std::unordered_map<Node*, std::vector<Edge*> > nodes_to_edges;

    void read_graph(QString _filename);             // Read graph from given file
    void read_quantity(ifstream& graph_file_, int &quantity);
    void read_unweighted_adjacency_matrix(ifstream &graph_file_, int quantity_);
    void read_weighted_adjacency_matrix(ifstream &graph_file_, int quantity_);
    void read_weighted_edgelist(ifstream &graph_file_);
    void read_unweighted_edgelist(ifstream &graph_file_);

    void insert_edge(int start_value, int end_value, double weight);
    void insert_n_nodes(int n);

    void print_nodes();

};

#endif // GRAPH_H
