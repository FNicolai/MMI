#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <QList>
#include <QMap>


class GraphModel
{
public:
    GraphModel();
    void set_weight(bool weight_);
    bool get_weight();

    void set_directed(bool directed_);
    bool get_directed();
private:
    //QList xy;
    //QMap xy;
    bool _weighted;
    bool _directed;

};

#endif // GRAPH_H
