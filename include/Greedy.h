#include "Method.h"
#ifndef _GREEDY_H
#define _GREEDY_H

class Greedy : public Method {
    public: 
    Greedy(std::string);
    ~Greedy();
    Pair SolveMethod();
    private:
    int number_of_nodes_;
    
};

Greedy::Greedy(std::string name) : Method(name) {
    number_of_nodes_ = graph_->get_nodes().size();
}

Greedy::~Greedy() {
    
}
Pair Greedy::SolveMethod() {
    int controller = number_of_nodes_;
    int candidate_cost = 999999999;
    Pair result;
    result.result = "";
    result.cost = 0;
    std::string candidate;
    int start_node = graph_->find_start_node();
    result.result += graph_->get_nodes()[start_node].get_name() + " -> ";
    std::vector<Edge> neighbors = graph_->get_nodes()[start_node].get_neighbors();
    graph_->get_nodes()[start_node].visited = true;
    while(controller > 0) {
        for(int i = 0; i < neighbors.size(); ++i) {
            int candidate_index = graph_->find_node(neighbors[i].city2);
            if(!graph_->get_nodes()[candidate_index].visited) {
                if(neighbors[i].cost < candidate_cost) {
                    candidate_cost = neighbors[i].cost;
                    candidate = neighbors[i].city2;
                }
           }
        }
        int index = graph_->find_node(candidate);
        --controller;
        neighbors = graph_->get_nodes()[index].get_neighbors();
        graph_->get_nodes()[index].visited = true;
        result.result += candidate + ((controller > 0) ? " -> " : "");
        if(controller > 0) {
            result.cost += candidate_cost;
        }
        candidate_cost = 999999999;
    }
    int the_last_travel = graph_->find_node(candidate);
    neighbors = graph_->get_nodes()[the_last_travel].get_neighbors();
    int the_start = graph_->get_nodes()[the_last_travel].find_neighbor(graph_->get_nodes()[start_node].get_name());
    result.cost += neighbors[the_start].cost;


    return result;
}

#endif //_GREEDY_H
