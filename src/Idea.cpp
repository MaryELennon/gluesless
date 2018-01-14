#include "Idea.h"

#include <algorithm>

#include "global.h"

Idea::Idea(
  std::string identity,
  Networkland* realworld,
  std::vector<double> power_distribution
) {
  this->identity = identity;
  this->realworld = realworld;
  // fill expansion map
  set_expansion(power_distribution);
}

std::string Idea::get_identity() { return this->identity; }
void Idea::set_identity(std::string identity) { this->identity = identity; }
std::map<vertex_desc, IdeaState*> Idea::get_expansion() { return this->expansion;}
void Idea::set_expansion(std::vector<double> power_distribution) {
  std::pair<vertex_iter, vertex_iter> vp;
  size_t it = 0;
  for (vp = this->realworld->get_all_vertices(); vp.first != vp.second; ++vp.first) {
    IdeaState* state_for_one_region = new IdeaState(power_distribution[it]);
    expansion.insert(std::pair<vertex_desc, IdeaState*>(*vp.first, state_for_one_region));
    it++;
  }
}
void Idea::add_competing_idea(Idea* competing_idea) {
  this->competing_ideas.push_back(competing_idea);
}

void Idea::live() {
  this->produce_poison();
}

void Idea::produce_poison() {
  for(auto it = this->expansion.begin(); it != this->expansion.end(); ++it) {
    it->second->produce_poison_local();
    //Rcpp::Rcout << it->second->get_local_poison_amount() << " ";
  }
}