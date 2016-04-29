#include "double_tree.h"

DoubleTree::DoubleTree(Graph* graph)
{
    _graph = graph;
}

void DoubleTree::perform_doubleTree(int start_node_value) {

    my_kruskal = Kruskal(_graph);
    multimap<Edge *, double> kruskal_edges = my_kruskal.perform_kruskal(start_node_value);

    double total_weight = 0.;

    // Two graphs required in order to perform traversation and another one to fill the double-tree
    Graph graph_for_search(true, false);
    Graph double_tree_graph(true, false);

    bool my_nodes_visited[_graph->get_nodes().size()];// = { 0 };
    for(auto i = 0; i < _graph->get_nodes().size(); i++)
        my_nodes_visited[i] = false;

    for(auto i = 0; i < _graph->get_nodes().size(); i++){
        graph_for_search.insert_node_if_not_exist(i);
        double_tree_graph.insert_node_if_not_exist(i);
    }

    for(multimap<Edge *, double>::iterator ii=kruskal_edges.begin(); ii!=kruskal_edges.end(); ++ii) {
//        std::cout << "From: " << ii->first->get_left_node()->get_value() << " To: " << ii->first->get_right_node()->get_value() << " Weight: " << ii->first->get_weight() << std::endl;

        // We have to make sure that we are using the pointers of the graph_for_search
        graph_for_search.insert_edge_if_not_exist(
                    graph_for_search.get_node(ii->first->get_left_node()->get_value()),
                    graph_for_search.get_node(ii->first->get_right_node()->get_value()),
                    ii->first->get_weight());
    }

    Node* cur_node = NULL;
    Node* previous_node = NULL;
    Node* cur_node_in_traversing_edge;

    _nodes_queue.push(graph_for_search.get_node(start_node_value));

    while (!_nodes_queue.empty()) {
        cur_node = _nodes_queue.front();
        int num_edges = cur_node->get_edges().size();
        my_nodes_visited[cur_node->get_value()] = true;

        for (int i = 0; i < num_edges; i++) {
            cur_node_in_traversing_edge = cur_node->get_edges()[i]->get_right_node();
            if (!my_nodes_visited[cur_node_in_traversing_edge->get_value()]) {
                _nodes_queue.push(cur_node_in_traversing_edge);
//                cout << "right ";
            }

            cur_node_in_traversing_edge = cur_node->get_edges()[i]->get_left_node();
            if (!my_nodes_visited[cur_node_in_traversing_edge->get_value()]) {
                _nodes_queue.push(cur_node_in_traversing_edge);
//                cout << "left ";
            }
        }

        if (previous_node != NULL) {
            Edge* edge_of_orig_graph = locate_edge_in_orig_graph(previous_node->get_value(), cur_node->get_value());

//            Node* previous_node_in_orig_graph = _graph->get_node(previous_node->get_value());

//            // locate edge pointing to "cur_node" in _graph (original graph
//            // we need this to determine the weight of this edge
//            Edge* edge_in_orig_graph_from_prev_to_cur;
//            for (int i = 0; i < previous_node_in_orig_graph->get_edges().size(); i++) {
//                edge_in_orig_graph_from_prev_to_cur = previous_node_in_orig_graph->get_edges()[i];

//                // This can either be the right or the left node of the edge
//                if (
//                        edge_in_orig_graph_from_prev_to_cur->get_right_node()->get_value() == cur_node->get_value() ||
//                        edge_in_orig_graph_from_prev_to_cur->get_left_node()->get_value() == cur_node->get_value()
//                        )
//                {
//                    break;
//                }
//            }

            double_tree_graph.insert_edge_if_not_exist(
                        double_tree_graph.get_node(previous_node->get_value()),
                        double_tree_graph.get_node(cur_node->get_value()),
                        edge_of_orig_graph->get_weight());
            total_weight += edge_of_orig_graph->get_weight();
        }
        previous_node = cur_node;
        _nodes_queue.pop();
    }


    // Insert last edge from last node to start_node
    Edge* edge_of_orig_graph = locate_edge_in_orig_graph(cur_node->get_value(), start_node_value);

    double_tree_graph.insert_edge_if_not_exist(
                double_tree_graph.get_node(cur_node->get_value()),
                double_tree_graph.get_node(start_node_value),
                edge_of_orig_graph->get_weight());

    total_weight += edge_of_orig_graph->get_weight();

    cout << endl << total_weight << endl;
}

Edge* DoubleTree::locate_edge_in_orig_graph(int start_node, int end_node) {
    Node* previous_node_in_orig_graph = _graph->get_node(start_node);

    // locate edge pointing to "end_node" in _graph (original graph
    // we need this to determine the weight of this edge
    Edge* edge_in_orig_graph_from_prev_to_cur;
    for (int i = 0; i < previous_node_in_orig_graph->get_edges().size(); i++) {
        edge_in_orig_graph_from_prev_to_cur = previous_node_in_orig_graph->get_edges()[i];

        // This can either be the right or the left node of the edge
        if (
                edge_in_orig_graph_from_prev_to_cur->get_right_node()->get_value() == end_node ||
                edge_in_orig_graph_from_prev_to_cur->get_left_node()->get_value() == end_node
                )
        {
            return edge_in_orig_graph_from_prev_to_cur;
        }
    }

    return NULL;
}

void DoubleTree::print_tree() {
//    cout << "Double tree with " << double_tree_edges.size() << " edges" << endl;

}
