#include "bfs.h"

BFS::BFS() {

}

BFS::BFS(Graph* graph, bool debug_)
{
    _graph = graph;
    _debug = debug_;
}

void BFS::perform_iterative_BFS(int start_node_value) {

    _nodes_visited.resize(_graph->get_nodes().size(),false);

    Node * cur_node = _graph->get_node(start_node_value);
    _nodes_queue.push(cur_node);
    set_node_visited(cur_node,true);
    //cur_node->set_visited(true);

    if(_debug){
        cout << endl << "iterative BFS:" << endl;
    }

    while (!_nodes_queue.empty()) {
        cur_node = _nodes_queue.front();
        _nodes_queue.pop();
        if(_debug){
            cout << cur_node->get_value();
        }
        _found_nodes.push_back(cur_node);

//        if (cur_node == goal_node) {
//            return;
//        }
        vector<Edge*> cur_edges = cur_node->get_edges();
        Node* next_node;

        for (uint iE = 0; iE < cur_edges.size(); iE++) {
            next_node = cur_edges[iE]->get_right_node();
            //if (!next_node->get_visited()) {
            if (!get_node_visited(next_node)) {
                set_node_visited(next_node,true);
                //next_node->set_visited(true);
                _nodes_queue.push(next_node);
            }
            if(!_graph->is_directed()){
                next_node = cur_edges[iE]->get_left_node();
                //if (!next_node->get_visited()) {
                if (!get_node_visited(next_node)) {
                    //next_node->set_visited(true);
                    set_node_visited(next_node,true);
                    _nodes_queue.push(next_node);
                }
            }
        }
        if(_debug){
            if(!_nodes_queue.empty()){
                cout << " -> ";
            }
        }
    }
    if(_debug){
        cout << endl;
    }
}

vector<Node *> BFS::get_found_nodes()
{
    return _found_nodes;
}

bool BFS::get_node_visited(Node *node_)
{
    return _nodes_visited[node_->get_value()];
}

void BFS::set_node_visited(Node *node_, bool status_)
{
    _nodes_visited[node_->get_value()] = status_;
}
