#include "dfs.h"
//#define SHOWCYCLES

DFS::DFS() {

}

DFS::DFS(Graph* graph, bool debug_)
{
    _graph = graph;
    _debug = debug_;
}

void DFS::perform_recursive_DFS(double start_node_value) {

    _nodes_visited.resize(_graph->get_nodes().size(),false);

    cout << endl << "recursive DFS:" << endl;
    visit(_graph->get_node(start_node_value));
    cout << endl;
}

vector<Node *> DFS::get_found_nodes()
{
    return _found_nodes;
}

void DFS::visit(Node* node) { 

    cout << node->get_value();
    _found_nodes.push_back(node);

    set_node_visited(node,true);
    //node->set_visited(true);
    vector<Edge*> cur_edges = node->get_edges();
    Node* next_node;

    for (uint iE = 0; iE < cur_edges.size(); iE++) {
        next_node = cur_edges[iE]->get_right_node();
        //if (!next_node->get_visited()) {
        if (!get_node_visited(next_node)) {
            cout << " -> ";
            visit(next_node);
        } else {
#ifdef SHOWCYCLES
            cout << "cycle: " << next_node->get_value() << " -> ";
#endif
        }
        if(!_graph->is_directed()){
            next_node = cur_edges[iE]->get_left_node();
            //if (!next_node->get_visited()) {
            if (!get_node_visited(next_node)) {
                cout << " -> ";
                visit(next_node);
            }
        }
    }
}

bool DFS::get_node_visited(Node *node_)
{
    return _nodes_visited[node_->get_value()];
}

void DFS::set_node_visited(Node *node_, bool status_)
{
    _nodes_visited[node_->get_value()] = status_;
}
