#include "dfs.h"

DFS::DFS() {

}

DFS::DFS(Graph* graph)
{
    _graph = graph;
}

void DFS::perform_recursive_DFS(double start_node_value) {
    visit(_graph->get_node(start_node_value));
}

void DFS::visit(Node* node) {
    cout << "visit: " << node->get_value() << endl;
    node->set_visited(true);
    vector<Edge*> cur_edges = node->get_edges();
    Node* next_node;

    for (uint iE = 0; iE < cur_edges.size(); iE++) {
        next_node = cur_edges[iE]->get_right_node();
        if (!next_node->get_visited()) {
            visit(next_node);
        } else {
            cout << "cycle!" << endl;
        }
    }
}

//void DFS::perform_iterative_BFS(double start_node_value) {
//    Node* cur_node = _graph->get_node(start_node_value);

//    nodes_queue.push(cur_node);
//    cur_node->set_visited(true);

//    cout << endl << "iterative BFS!" << endl;

//    while (!nodes_queue.empty()) {
//        cur_node = nodes_queue.front();
//        nodes_queue.pop();

//        cout << "cur_node: " << cur_node->get_value() << endl;

////        if (cur_node == goal_node) {
////            return;
////        }
//        vector<Edge*> cur_edges = cur_node->get_edges();
//        Node* next_node;

//        for (uint iE = 0; iE < cur_edges.size(); iE++) {
//            next_node = cur_edges[iE]->get_right_node();
//            if (!next_node->get_visited()) {
//                next_node->set_visited(true);
//                nodes_queue.push(next_node);
//            }
//        }
//    }
//}
