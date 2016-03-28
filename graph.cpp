#include "graph.h"

Graph::Graph(bool weighted_, bool directed_, bool is_adjacency_matrix_, QString filename_)
{
    _is_weighted = weighted_;
    _is_directed = directed_;
    _filename = filename_;
    _is_adjacency_matrix = is_adjacency_matrix_;

    cout << _is_weighted << " " << _is_directed << " " << _is_adjacency_matrix << " " << _filename.toUtf8().constData() << endl;

    read_graph(_filename);
}



// ### GET and SET methods

bool Graph::is_weighted() const
{
    return _is_weighted;
}

bool Graph::is_directed() const
{
    return _is_directed;
}

bool Graph::is_adjacency_matrix() const {
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


    double cur_node, goal_node;
    double weight;

    if(!is_weighted()){
        weight = NULL; //No weight, because the graph is'nt weighted
    }

    if (is_adjacency_matrix()){

        //IS ADJACENCY MATRIX

    }else{

        //IS EDGELIST

        if(graph_file){
            while (graph_file >> cur_node >> goal_node){
                //cout << a << " " << b << endl;
//                Node* left_node = new Node(cur_node);
//                Node* right_node = new Node(goal_node);

//                Edge* new_edge = new Edge(left_node, right_node, weight);
                //if(_nodes.at(cur_node)){ //Test if node exists and add edge
                    //this->_nodes.at(cur_node) == new ;
                //}
                //this->_nodes.at(node).push_back(new_edge);

                insert_edge(cur_node, goal_node);
            }

            cout << "DEBUG:\nNode\tnum_ed\tadjacent_nodes" << endl;
            for (int i = 0; i < nodes.size(); i++) {
                vector<Edge*> cur_edges = nodes.at(i)->get_edges();
                cout << i << "\t" << cur_edges.size() << "\t";

                for (int j = 0; j < cur_edges.size(); j++) {
                    cout << cur_edges[j]->get_right_node()->get_value() << "\t";
                }
                cout << endl;

            }
            cout << nodes.size() << endl;
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

Node* Graph::insert_node_if_not_exist(double value) {
    if (nodes[value] == NULL) {
        nodes[value] = new Node(value);
    }
    return nodes[value];
}

void Graph::insert_edge(double start_value, double end_value) {

    Node* start_node = insert_node_if_not_exist(start_value);
    Node* end_node = insert_node_if_not_exist(end_value);

//    // Insert nodes if they don't exist
//    if (nodes[start_value] == NULL) {
//        nodes[start_value] = new Node();
//    }
//    if (nodes[end_value] == NULL) {
//        nodes[end_value] = new Node();
//    }

    insert_edge_if_not_exist(start_node, end_node);

//    vector<Edge*> start_edges = nodes_to_edges[nodes[start_value]];
//    vector<Edge*> end_edges = nodes_to_edges[nodes[end_value]];

//    if (start_edges.size() == 0) {
//        Edge* cur_edge = new Edge(nodes[start_value], nodes[end_value], 0);
//        start_edges.push_back(cur_edge);

//    } else {
//        bool found = false;

//        for (int iS = 0; iS < start_edges.size(); iS++) {
//            Edge* cur_edge = start_edges.get(iS);
//            if (
//                    cur_edge->left_node == nodes[start_value] ||
//                    cur_edge->left_node == nodes[end_value]) {

//            }
//        }
//    }

//    // Check if start node has edges
//    if (nodes_to_edges[nodes[start_value]].size() == 0) {
//        nodes_to_edges[nodes[start_value]] = vector<Node*>();
//    }

//    // Check if end node has edges
//    if (nodes_to_edges[nodes[end_value]].size() == 0) {

//    }
}

bool Graph::insert_edge_if_not_exist(Node* start_node, Node* end_node) {
    start_node->insert_edge_to(end_node, is_directed());
}

void Graph::add_node(Node new_node_)
{
//    this->_nodes.push_back(new_node_);
}

Node* Graph::get_node(double value) {
    return nodes[value];
}
