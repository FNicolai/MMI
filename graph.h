#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "edge.h"

#include <vector>
#include <map>
#include <iostream>

#include <QString>

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <unordered_map>

#include <ctime>

using namespace std;

class Graph
{
public:
    enum GraphInputType {EDGELIST, ADJACENCY_MATRIX, BALANCE};
    Graph();
    Graph(bool weighted_, bool directed_, GraphInputType input_type_ = EDGELIST);
    Graph(bool weighted_, bool directed_, GraphInputType graph_input_type_, QString filename_);

    inline bool is_weighted() const;
    inline bool is_directed() const;
    inline bool is_adjacency_matrix() const;
    inline bool is_edgelist() const;
    inline bool is_balance_given() const;
    GraphInputType get_input_type() const;

    Node* get_node(int value_);
//    unordered_map<double, Node*> get_nodes();
    vector<Node*> get_nodes();
    Node* insert_node_if_not_exist(int value_, double balance_ = 0.0);
    bool insert_edge_if_not_exist(Node* start_node_, Node* end_node_, double weight_, double flow_ = 0.0, double cost_ = 0.0);
    void reset_edges();

    vector <Edge *> get_edgelist();

    void insert_n_nodes(int n);

    //void remove_node(Node * node_);

    Graph * create_copy();
    void *transfer_balance(Graph *graph_);

    void print_nodes();

private:

    bool _is_weighted;              // Is the given graph weighted?
    bool _is_directed;              // Is the given graph directed?
    GraphInputType _input_type;     // In what kind of matrixtype has the given graph
    QString _filename;              // Where is the given graph located
    bool _balance_given;            // Is the balance given?

    //std::unordered_map<double, Node*> nodes;
    vector<Node*> _nodes;

    vector<Edge *> _edgelist;

    //std::unordered_map<Edge*, std::vector<Node*> > edges_to_nodes;
    //std::unordered_map<Node*, std::vector<Edge*> > nodes_to_edges;

    void read_graph();             // Read graph from given file
    void read_quantity(ifstream& graph_file_, int &quantity);
    void read_unweighted_adjacency_matrix(ifstream &graph_file_, int quantity_);
    void read_weighted_adjacency_matrix(ifstream &graph_file_, int quantity_);
    void read_weighted_edgelist(ifstream &graph_file_);
    void read_unweighted_edgelist(ifstream &graph_file_);
    void read_balanced_edgelist(ifstream &graph_file_);

    void insert_edge(int start_value_, int end_value_, double weight_ = NAN, double cost_ = 0.0);

};

#endif // GRAPH_H
