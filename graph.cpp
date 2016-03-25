#include "graph.h"
#include "nodes.h"

GraphModel::GraphModel()
{

}

void GraphModel::set_weight(bool weight_){
    _weighted = weight_;
}

bool GraphModel::get_weight(){
    return _weighted;
}

void GraphModel::set_directed(bool directed_){
    _directed = directed_;
}

bool GraphModel::get_directed(){
    return _directed;
}
