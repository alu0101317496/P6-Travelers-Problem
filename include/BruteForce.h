#include "Method.h"

#ifndef _BRUTEFORCE_H_
#define _BRUTEFORCE_H_

class BruteForce : public Method {
  public:
  BruteForce(std::string);
  ~BruteForce();
  Pair SolveMethod();
  void VisualizeCandidates(std::vector<Pair>);
  void clear_nodes();
  int find_pair_with_lower_cost(std::vector<Pair>);

  private:
  int number_of_nodes_;
};

BruteForce::BruteForce(std::string file_name) : Method(file_name) {
  number_of_nodes_ = graph_->get_nodes().size();
}

BruteForce::~BruteForce() {}

Pair BruteForce::SolveMethod() {
  Pair result;
  std::vector<Pair> result_candidates;
  Pair aux_pair_candidate;
  clear_nodes();
  Node* actual_node;
  Node* next_node;
  std::vector<std::string> all_names = graph_->get_all_names();
  do {
    for(int i = 0; i < all_names.size(); ++i) {
      aux_pair_candidate.result += all_names[i] + ((i < all_names.size()) ? " -> " : "");
      actual_node = &graph_->get_nodes()[graph_->find_node(all_names[i])];
      actual_node->visited = true;
      if (i+1 < all_names.size()) {
        next_node = &graph_->get_nodes()[graph_->find_node(all_names[i + 1])];
        if(!next_node->visited) {
          aux_pair_candidate.cost += actual_node->get_neighbors()[actual_node->find_neighbor(next_node->get_name())].cost ;
        }
      }
    }
    result_candidates.push_back(aux_pair_candidate);
    aux_pair_candidate.cost = 0;
    aux_pair_candidate.result = "";
    clear_nodes();
  } while(std::next_permutation(all_names.begin(), all_names.end()));

  int final_index = find_pair_with_lower_cost(result_candidates);
  result = result_candidates[final_index];
  return result; 
}

void BruteForce::VisualizeCandidates(std::vector<Pair> candidates) {
  for(int i = 0; i < candidates.size(); ++i) {
    printf("%s | with cost %d\n", candidates[i].result.c_str(), candidates[i].cost);
  }
}

void BruteForce::clear_nodes() {
  for (int i = 0; i < graph_->get_nodes().size(); ++i) {
    graph_->get_nodes()[i].visited = false;
  }
}

int BruteForce::find_pair_with_lower_cost(std::vector<Pair> v_) {
  int min_cost = v_[0].cost;
  int min_index = 0;
  for(int i = 1; i < v_.size(); ++i) {
    if(v_[i].cost < min_cost) {
      min_cost = v_[i].cost;
      min_index = i;
    }
  }
  return min_index;
}
#endif // _BRUTEFORCE_H_