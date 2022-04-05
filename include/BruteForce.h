#include "Method.h"

#ifndef _BRUTEFORCE_H_
#define _BRUTEFORCE_H_

class BruteForce : public Method {
  public:
  BruteForce(std::string);
  ~BruteForce();
  Pair SolveMethod();

  private:
  int number_of_nodes_;
};

BruteForce::BruteForce(std::string file_name) : Method(file_name) {
  number_of_nodes_ = graph_->get_nodes().size();
}

Pair BruteForce::SolveMethod() {
  Pair result;
  std::vector<Pair> result_candidates;
  Pair aux_pair_candidate;
  Node* actual_node;
  std::vector<std::string> all_names = graph_->get_all_names();
  do {
    for(int i = 0; i < all_names.size(); ++i) {
      aux_pair_candidate.result += all_names[i] + ((i < all_names.size()) ? " -> " : "");
      actual_node = &graph_->get_nodes()[graph_->find_node(all_names[i])];
      actual_node->visited = true;
      
    }
    result_candidates.push_back(aux_pair_candidate);
    aux_pair_candidate.cost = 0;
    aux_pair_candidate.result = "";
  } while(std::next_permutation(all_names.begin(), all_names.end()));




  return result; 
}

#endif // _BRUTEFORCE_H_