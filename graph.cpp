#include "graph.h"

Graph::Graph()
{

}

Graph::Graph(bool weighted_, bool directed_)
{
    _is_weighted = weighted_;
    _is_directed = directed_;
}

Graph::Graph(bool weighted_, bool directed_, GraphInputType graph_input_type, QString filename_)
{
    _is_weighted = weighted_;
    _is_directed = directed_;
    _filename = filename_;
    _input_type = graph_input_type;

    cout << _is_weighted << " " << _is_directed << " " << is_adjacency_matrix() << " " << _filename.toUtf8().constData() << endl;

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
    return _input_type == ADJACENCY_MATRIX;
}

bool Graph::is_edgelist() const {
    return _input_type == EDGELIST;
}

// ### Other functions

void Graph::read_graph(QString _filename)
{
    ifstream graph_file (_filename.toUtf8().constData());


    // Get first line with quantity of lines
    // AND generate a node for each n of quantity
    int quantity;
    read_quantity(graph_file, quantity);

    // Insert number of nodes no matter what kind of graph is given
    insert_n_nodes(quantity);


    if (is_adjacency_matrix()){

        //IS ADJACENCY MATRIX

        if(is_weighted()){
            read_weighted_adjacency_matrix(graph_file, quantity);
        }else{
            read_unweighted_adjacency_matrix(graph_file, quantity);
        }

    }else if (is_edgelist()){

        //IS EDGELIST
        if(is_weighted()){
            read_weighted_edgelist(graph_file);
        }else{
            read_unweighted_edgelist(graph_file);
        }
    }
}

void Graph::read_quantity(ifstream &graph_file_, int &quantity)
{
    if (graph_file_){
        graph_file_ >> quantity;

        cout << "There are " << quantity << " nodes in the file." << endl;

        for (double i = 0; i < quantity; i++) {
            insert_node_if_not_exist(i);
        }

        _nodes_visited.resize(quantity,false);

        //graph_file.close();
    }else cout << "Error while reading file";
}

void Graph::read_unweighted_adjacency_matrix(ifstream &graph_file_, int quantity_)
{
    double edge_exists;

    if (graph_file_){
        for(int cur_node = 0; cur_node < quantity_; cur_node++){
            for(int goal_node = 0; goal_node < quantity_; goal_node++){
                graph_file_ >> edge_exists;
                //cout << edge_exists << " ";
                if(edge_exists == 1){
                    //cout << "Edge from " << cur_node << " to " << goal_node << " exists." << endl;
                    insert_edge(cur_node,goal_node,NAN);
                }
            }
            //cout << endl;
        }
        print_nodes();
    }else cout << "Error while reading file";

}

void Graph::read_weighted_adjacency_matrix(ifstream &graph_file_, int quantity_)
{
    double weight;
    if (graph_file_){
        for(int cur_node = 0; cur_node < quantity_; cur_node++){
            for(int goal_node = 0; goal_node < quantity_; goal_node++){
                graph_file_ >> weight;
                cout << weight << " ";
                insert_edge(cur_node,goal_node,weight);
            }
            cout << endl;
        }
        print_nodes();
    }else cout << "Error while reading file";
}

void Graph::read_weighted_edgelist(ifstream &graph_file_)
{
    double cur_node, goal_node, weight;

    if(graph_file_){        
        while (graph_file_ >> cur_node >> goal_node >> weight){
            //cout << a << " " << b << endl;
            insert_edge(cur_node, goal_node, weight);
        }
        print_nodes();
    }else cout << "Error while reading file";
}

void Graph::read_unweighted_edgelist(ifstream &graph_file_)
{
    double cur_node, goal_node;

    if(graph_file_){
        while (graph_file_ >> cur_node >> goal_node){
            //cout << a << " " << b << endl;
            insert_edge(cur_node, goal_node, NAN);
        }
        print_nodes();
    }else cout << "Error while reading file";
}

void Graph::insert_n_nodes(int n) {
    for (int i = 0; i < n; i++) {
        insert_node_if_not_exist(i);
    }
}

Node* Graph::insert_node_if_not_exist(int value) {
    if (nodes.size() <= value) {
        Node * cur_node = new Node(value);
        nodes.push_back(cur_node);
    }
    return nodes[value];
}

void Graph::insert_edge(int start_value, int end_value, double weight) {

    Node* start_node = insert_node_if_not_exist(start_value);
    Node* end_node = insert_node_if_not_exist(end_value);

    insert_edge_if_not_exist(start_node, end_node, weight);
}

bool Graph::insert_edge_if_not_exist(Node* start_node, Node* end_node, double weight) {
    start_node->insert_edge_to(end_node, is_directed(), weight);
}

Node* Graph::get_node(int value_) {
    return nodes[value_];
}

bool Graph::get_node_visited(Node *node_)
{

    return _nodes_visited[node_->get_value()];
}

void Graph::set_node_visited(Node *node_, bool status_)
{
    _nodes_visited[node_->get_value()] = status_;
}

void Graph::reset_visited() {
    fill(_nodes_visited.begin(), _nodes_visited.end(), false);
//    for (size_t i; i < nodes.size(); i++)
//    {
//        nodes[i]->set_visited(false);
//    }
}

vector<Node *> Graph::get_nodes()
{
    return nodes;
}

void Graph::print_nodes()
{
    cout << "DEBUG:\nNode\t#Edges\tadjacent_nodes" << endl;

    for (size_t i = 0; i < nodes.size(); i++) {
        vector<Edge*> cur_edges = nodes[i]->get_edges();
        cout << i << "\t" << cur_edges.size() << "\t";

        for (int j = 0; j < cur_edges.size(); j++) {
            if (cur_edges[j]->get_right_node()->get_value() == nodes[i]->get_value()){
                cout << cur_edges[j]->get_left_node()->get_value();
            }else{
                cout << cur_edges[j]->get_right_node()->get_value();
            }
            if(is_weighted()){
                cout << " (" << cur_edges[j]->get_weight() << ")";
            }
            cout <<  "\t";
        }
        cout << endl;
    }
    cout << "There are " << nodes.size() << " Nodes at the moment." << endl;
}
