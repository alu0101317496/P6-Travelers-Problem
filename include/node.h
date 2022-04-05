#include "libraries.h"

#ifndef NODE_H
#define NODE_H

class Node {
    public:
    Node();
    ~Node();
    void set_name(std::string);
    std::string get_name();
    void InsertNeighbor(std::string, int);
    int find_neighbor(std::string);
    bool visited;
    std::vector<Edge> get_neighbors();
    std::string VisualizeNeighbors();
    private:
    std::string name_;
    std::vector<Edge> neighbors_;
    
};

Node::Node(): 
visited(false) {
    
}

Node::~Node() {
    
}

void Node::set_name(std::string new_name) {
    name_ = new_name;
}

std::string Node::get_name() {
    return name_;
}

void Node::InsertNeighbor(std::string name, int cost) {
    Edge new_edge;
    new_edge.city1 = name_;
    new_edge.city2 = name;
    new_edge.cost = cost;
    neighbors_.push_back(new_edge);
}

std::vector<Edge> Node::get_neighbors() {
    return neighbors_;
}

std::string Node::VisualizeNeighbors() {
    std::string aux = "";
    for(int i = 0; i < neighbors_.size(); ++i) {
        aux +=  "->" + neighbors_[i].city2 + " with cost: "+ std::to_string(neighbors_[i].cost) + "\n";
    }
    return aux;
}

int Node::find_neighbor(std::string name) {
    for(int i = 0; i < neighbors_.size(); ++i) {
        if(neighbors_[i].city2 == name) {
            return i;
        }
    }
    return -1;
}

#endif //NODE_H


