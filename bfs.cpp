#include "bfs.h"

BFS::BFS() {

}

BFS::BFS(Graph* graph)
{
    _graph = graph;
}

void BFS::perform_iterative_BFS(double start_node_value) {
    Node* cur_node = _graph->get_node(start_node_value);
    nodes_queue.push(cur_node);
    cur_node->set_visited(true);

    cout << endl << "iterative BFS:" << endl;

    while (!nodes_queue.empty()) {
        cur_node = nodes_queue.front();
        nodes_queue.pop();

        cout << cur_node->get_value() << " -> ";

//        if (cur_node == goal_node) {
//            return;
//        }
        vector<Edge*> cur_edges = cur_node->get_edges();
        Node* next_node;

        for (uint iE = 0; iE < cur_edges.size(); iE++) {
            next_node = cur_edges[iE]->get_right_node();
            if (!next_node->get_visited()) {
                next_node->set_visited(true);
                nodes_queue.push(next_node);
            }
        }
    }
    cout << endl;
}
