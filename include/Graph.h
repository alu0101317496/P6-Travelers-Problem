#include "libraries.h"
#include "node.h"

#ifndef _GRAPH_H
#define _GRAPH_H




class Graph {
    public:
    Graph(std::string);
    ~Graph();
    void GraphVisualizer();
    inline std::vector<Node>& get_nodes() { return node_v_; }
    inline std::vector<Edge> get_edges() { return edge_v_; }
    int find_node(std::string);
    int find_start_node();
    std::vector<std::string> get_all_names();
    
    protected:
    std::vector<Node> node_v_;
    std::vector<Edge> edge_v_;
    int number_of_nodes_;
};

Graph::Graph(std::string input_file) {
    std::fstream file(input_file);
    std::string aux;
    std::getline(file, aux);
    number_of_nodes_ = std::stoi(aux);
    for (int i = 0; i < number_of_nodes_; ++i) {
        Node new_node;
        std::string name;
        if(number_of_nodes_ < 27) {
            name = char(65+i);
        } else {
            name = "n" + std::to_string(i);
        }
        new_node.set_name(name);
        node_v_.push_back(new_node);
    }
    int nodeNumber = 0;
    while(std::getline(file, aux)) {
        std::stringstream ss(aux);
        std::string city1, city2;
        int cost;
        ss >> city1 >> city2 >> cost;
        Edge new_edge;
        new_edge.city1 = city1;
        new_edge.city2 = city2;
        new_edge.cost = cost;
        edge_v_.push_back(new_edge);
        for (int i = 0; i < node_v_.size(); ++i) {
            if (city1 == node_v_[i].get_name()) {
                node_v_[i].InsertNeighbor(city2, cost);
            } else if(city2 == node_v_[i].get_name()) {
                node_v_[i].InsertNeighbor(city1, cost);
            }
        }
    }
}

Graph::~Graph() {
    
}

void Graph::GraphVisualizer() {
    std::string aux = "";
    for(int i = 0; i < edge_v_.size(); ++i) {
        aux += edge_v_[i].city1 + " <--> "+ edge_v_[i].city2 + " || with cost: "+ std::to_string(edge_v_[i].cost) + "\n";
    }

    aux += "\n";
    aux += "Nodes neighbors: \n";
    for(int i = 0; i < node_v_.size(); ++i) {
        aux += node_v_[i].get_name() +"\n" + node_v_[i].VisualizeNeighbors() + "\n";
    }
    std::cout << aux;
}

int Graph::find_node(std::string name) {
    for (int i = 0; i < node_v_.size(); ++i) {
        if (node_v_[i].get_name() == name) {
            return i;
        }
    }
    return -1;
}

int Graph::find_start_node() {
    int total_cost = 999999999;
    int candidate_cost = 0;
    int candidate_node = 0;
    for (int i = 0; i < number_of_nodes_; ++i) {
        for(int j = 0; j < node_v_[i].get_neighbors().size(); ++j)
        {
            candidate_cost += node_v_[i].get_neighbors()[j].cost;
        }
        if (candidate_cost < total_cost) {
            total_cost = candidate_cost;
            candidate_node = i;
        }
        candidate_cost = 0;
    }
    return candidate_node;
}

std::vector<std::string> Graph::get_all_names() {
    std::vector<std::string> all_names;
    for (int i = 0; i < node_v_.size(); ++i) {
        all_names.push_back(node_v_[i].get_name());
    }
    return all_names;
}

#endif //_GRAPH_H
