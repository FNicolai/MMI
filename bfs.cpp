#include "bfs.h"

BFS::BFS() {

}

BFS::BFS(Graph* graph)
{
    _graph = graph;
}

void BFS::perform_iterative_BFS(int start_node_value) {

    Node * cur_node = _graph->get_node(start_node_value);
    _nodes_queue.push(cur_node);
    _graph->set_node_visited(cur_node,true);
    //cur_node->set_visited(true);

    cout << endl << "iterative BFS:" << endl;

    while (!_nodes_queue.empty()) {
        cur_node = _nodes_queue.front();
        _nodes_queue.pop();

        cout << cur_node->get_value();
        _found_nodes.push_back(cur_node);

//        if (cur_node == goal_node) {
//            return;
//        }
        vector<Edge*> cur_edges = cur_node->get_edges();
        Node* next_node;

        for (uint iE = 0; iE < cur_edges.size(); iE++) {
            next_node = cur_edges[iE]->get_right_node();
            //if (!next_node->get_visited()) {
            if (!_graph->get_node_visited(next_node)) {
                _graph->set_node_visited(next_node,true);
                //next_node->set_visited(true);
                _nodes_queue.push(next_node);
            }
            if(!_graph->is_directed()){
                next_node = cur_edges[iE]->get_left_node();
                //if (!next_node->get_visited()) {
                if (!_graph->get_node_visited(next_node)) {
                    //next_node->set_visited(true);
                    _graph->set_node_visited(next_node,true);
                    _nodes_queue.push(next_node);
                }
            }
        }
        if(!_nodes_queue.empty()){
            cout << " -> ";
        }
    }
    cout << endl;

    _graph->reset_visited();
}

vector<Node *> BFS::get_found_nodes()
{
    return _found_nodes;
}
