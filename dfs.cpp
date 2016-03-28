#include "dfs.h"
//#define SHOWCYCLES

DFS::DFS() {

}

DFS::DFS(Graph* graph)
{
    _graph = graph;
}

void DFS::perform_recursive_DFS(double start_node_value) {
    cout << endl << "recursive DFS:" << endl;
    visit(_graph->get_node(start_node_value));
    cout << endl;
}

void DFS::visit(Node* node) {
    cout << node->get_value();
    node->set_visited(true);
    vector<Edge*> cur_edges = node->get_edges();
    Node* next_node;

    for (uint iE = 0; iE < cur_edges.size(); iE++) {
        next_node = cur_edges[iE]->get_right_node();
        if (!next_node->get_visited()) {
            cout << " -> ";
            visit(next_node);
        } else {
#ifdef SHOWCYCLES
            cout << "cycle: " << next_node->get_value() << " -> ";
#endif
        }
    }
}
