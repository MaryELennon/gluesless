#include "Timeline.h"

#include "Aether.h"

Timeline::Timeline(Aether* start) {
  this->ideanumber.push_back(start->get_ideanumber());
}

void Timeline::develop(Aether* current) {
  this->ideanumber.push_back(current->get_ideanumber());
  this->ideas.push_back(current->get_ideas());
  this->idea_vertices.push_back(
      current->get_idea_vertices()
    );

  current->develop();

  Rcpp::Rcout << "Zeitschritt vorwärts! " << std::endl;
}

SEXP Timeline::export_as_R_list() {

  using namespace Rcpp;

  List res;

  NumericVector ideanumber_nv(
      ideanumber.begin(),
      ideanumber.end()
    );

  NumericVector timestep;
  NumericVector id;
  NumericVector vert;

  int count = 0;
  std::vector< std::vector<int> >::iterator it_id_1=ideas.begin();

  for (auto& it_vert_1 : idea_vertices) {

    std::vector<int>::iterator it_id_2=(*it_id_1).begin();

    for (auto& it_vert_2 : it_vert_1) {

      for (auto& it_vert_3 : it_vert_2) {

        timestep.push_back(count);
        id.push_back(*it_id_2);
        vert.push_back(it_vert_3);

      }

    it_id_2++;

    }

  it_id_1++;
  count++;

  }

  res["number_of_ideas"] = ideanumber_nv;
  res["idea_exp"] = Rcpp::DataFrame::create(
    _["timestep"] = timestep,
    _["ideas"] = id,
    _["vertices"] = vert
    );

  return res;
}