#include "graph.h"

Graph::Graph()
{

}

Graph::Graph(bool weighted_, bool directed_, GraphInputType input_type_)
{
    _is_weighted = weighted_;
    _is_directed = directed_;
    _input_type = input_type_;
}

Graph::Graph(bool weighted_, bool directed_, GraphInputType graph_input_type_, QString filename_)
{
    _is_weighted = weighted_;
    _is_directed = directed_;
    _filename = filename_;
    _input_type = graph_input_type_;

    cout << _is_weighted << " " << _is_directed << " " << _input_type << " " << _filename.toUtf8().constData() << endl;

    read_graph();
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

bool Graph::is_balance_given() const
{
    return _input_type == BALANCE;
}

// ### Other functions

void Graph::read_graph()
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
    }else if(is_balance_given()){
        read_balanced_edgelist(graph_file);
    }
}

void Graph::read_quantity(ifstream &graph_file_, int &quantity)
{
    if (graph_file_){
        graph_file_ >> quantity;

        cout << "There are " << quantity << " nodes in the file." << endl;

        //insert_n_nodes(quantity);
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

void Graph::read_balanced_edgelist(ifstream &graph_file_)
{
    double cost, weight, cur_node, goal_node, balance;
    if(graph_file_){
        for (auto i = 0; i < _nodes.size();i++){
            graph_file_ >> balance;
            _nodes.at(i)->set_balance(balance);
        }
        while (graph_file_ >> cur_node >> goal_node >> cost >> weight){
            //cout << a << " " << b << endl;
            insert_edge(cur_node, goal_node, weight, cost);
        }
        print_nodes();
    }else cout << "Error while reading file";
}

void Graph::insert_n_nodes(int n) {
    int offset = _nodes.size();
    for (int i = offset; i < offset + n; i++) {
        insert_node_if_not_exist(i);
    }
}

Graph *Graph::create_copy()
{
    Graph * copy = new Graph (this->is_weighted(),this->is_directed(),this->_input_type);
    copy->insert_n_nodes(this->get_nodes().size());

    for(auto x = 0; x < _nodes.size(); x++){
        copy->get_node(x)->set_balance(_nodes.at(x)->get_balance());
    }

    vector<Edge *> edgelist = this->get_edgelist();
    for(auto i = 0; i < edgelist.size(); i++){
        Edge * curr_edge = edgelist.at(i);
        Node * start_node = copy->get_node(curr_edge->get_left_node()->get_value());
        Node * end_node = copy->get_node(curr_edge->get_right_node()->get_value());
        double weight = curr_edge->get_weight();
        double flow = curr_edge->get_flow();
        double cost = curr_edge->get_cost();

        copy->insert_edge_if_not_exist(start_node, end_node, weight, flow, cost);
    }
    return copy;
}

Node* Graph::insert_node_if_not_exist(int value_, double balance_) {
    if (_nodes.size() <= value_) {
        Node * cur_node = new Node(value_, balance_);
        _nodes.push_back(cur_node);
    }
    return _nodes[value_];
}

void Graph::insert_edge(int start_value_, int end_value_, double weight_, double cost_) {

    Node* start_node = insert_node_if_not_exist(start_value_);
    Node* end_node = insert_node_if_not_exist(end_value_);

    insert_edge_if_not_exist(start_node, end_node, weight_, 0.0, cost_);
}

bool Graph::insert_edge_if_not_exist(Node* start_node_, Node* end_node_, double weight_, double flow_, double cost_) {
    Edge * rtnValue;
    rtnValue = start_node_->insert_edge_to(end_node_, is_directed(), weight_, flow_, cost_);
    if(rtnValue != NULL){
        _edgelist.push_back(rtnValue);
    }
}

void Graph::reset_edges()
{
    for(auto i=0; i < _nodes.size(); i++){
        _nodes[i]->reset_edges();
    }
}

vector<Edge *> Graph::get_edgelist()
{
    return _edgelist;
}

Node* Graph::get_node(int value_) {
    return _nodes[value_];
}

vector<Node *> Graph::get_nodes()
{
    return _nodes;
}

void Graph::print_nodes()
{
    if(is_balance_given()){
        cout << "DEBUG:\nNode(Balance)\t#Edges\tadjacent_nodes (flow,weight|cost)" << endl;
    }else{
        cout << "DEBUG:\nNode\t#Edges\tadjacent_nodes(weight)" << endl;
    }

    for (size_t i = 0; i < _nodes.size(); i++) {
        vector<Edge*> cur_edges = _nodes[i]->get_edges();

        if(is_balance_given()){
            cout << i << " ("<< _nodes[i]->get_balance() << ")" << "\t\t" << cur_edges.size() << "\t";
        }
        else{
            cout << i << "\t" << cur_edges.size() << "\t";
        }

        for (int j = 0; j < cur_edges.size(); j++) {
            if (cur_edges[j]->get_right_node()->get_value() == _nodes[i]->get_value()){
                cout << cur_edges[j]->get_left_node()->get_value();
            }else{
                cout << cur_edges[j]->get_right_node()->get_value();
            }

            if(is_balance_given()){
                cout << "(" << cur_edges[j]->get_flow()
                     << "," << cur_edges[j]->get_weight()
                     << "|" << cur_edges[j]->get_cost() << ")";
            }else if(is_weighted()){
                cout << " (" << cur_edges[j]->get_weight() << ")";
            }
            cout <<  "\t";
        }
        cout << endl;
    }
    cout << "There are " << _nodes.size() << " Nodes at the moment." << endl;
}
