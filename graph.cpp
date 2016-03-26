#include "graph.h"
#include "node.h"
#include "edge.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

Graph::Graph(bool weighted_, bool directed_, bool is_adjacency_matrix_, QString filename_)
{
    _weighted = weighted_;
    _directed = directed_;
    _filename = filename_;
    _is_adjacency_matrix = is_adjacency_matrix_;

    cout << _weighted << " " << _directed << " " << _is_adjacency_matrix << " " << _filename.toUtf8().constData() << endl;

    read_graph(_filename);
}



// ### GET and SET methods

bool Graph::get_weighted() const
{
    return _weighted;
}

bool Graph::get_directed() const
{
    return _directed;
}

bool Graph::get_is_adjacency_matrix() const{
    return _is_adjacency_matrix;
}

// ### Other functions

void Graph::read_graph(QString _filename)
{
    ifstream graph_file (_filename.toUtf8().constData());


    //Get first line with quantity of lines
    double quantity;
    if (graph_file){
        graph_file >> quantity;
        cout << "There are " << quantity << " lines in the file." << endl;
        //graph_file.close();
    }else cout << "Error while reading file";


    double cur_node,goal_node;
    double weight;

    if(!get_weighted()){
        weight = NULL; //No weight, because the graph is'nt weighted
    }

    if (get_is_adjacency_matrix()){

        //IS ADJACENCY MATRIX

    }else{

        //IS EDGELIST

        if(graph_file){
            while (graph_file >> cur_node >> goal_node){
                //cout << a << " " << b << endl;
                edge* new_edge = new edge(goal_node, weight);
                //if(_nodes.at(cur_node)){ //Test if node exists and add edge
                    //this->_nodes.at(cur_node) == new ;
                //}
                //this->_nodes.at(node).push_back(new_edge);
            }
        }else cout << "Error while reading file";
    }

//    string line;
//    if (graph_file){
//        while (getline( graph_file, line )){
//            if
//        }
//        graph_file.close();
//    }else cout << "Error while reading file";
}

void Graph::add_node(node new_node_)
{
    this->_nodes.push_back(new_node_);
}


