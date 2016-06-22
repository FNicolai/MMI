#include "maximum_matching.h"

Maximum_Matching::Maximum_Matching()
{

}

Maximum_Matching::Maximum_Matching(Graph *graph_, bool debug_)
{
    _graph = graph_;
    _debug = debug_;
}

void Maximum_Matching::perform_maximum_matching()
{
    clock_t time_begin = clock();

    Edmonds_Karp edmonds_karp(_graph,_debug);

    //Perform edmonds karp from super source to super sink
    Node * super_source = _graph->get_nodes().at(_graph->get_nodes().size()-2);
    Node * super_sink   = _graph->get_nodes().at(_graph->get_nodes().size()-1);
    edmonds_karp.perform_edmonds_karp(super_source->get_value(), super_sink->get_value());

    double max_flow = edmonds_karp.get_max_flow();

    clock_t time_end = clock();
    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;

    cout << "Maximum matching of the graph is: " << max_flow << endl;

    cout << "The maximum matching algorithm obtained the result in " << elapsed_secs << " seconds." << endl;
}
