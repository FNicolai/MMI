#ifndef EDGE_H
#define EDGE_H


class edge
{
public:
    edge(double goal_node_, double weight_);

    double get_goal_node() const;
    void set_goal_node(double goal_node_);

    void set_weight(double weight_);
    double get_weight() const;

private:
    double _goal_node;       //Goal of edge
    double _weight;     //Weight of edge
};

#endif // EDGE_H
