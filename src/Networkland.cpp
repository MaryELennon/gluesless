#include <Rcpp.h>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graph_mutability_traits.hpp>
#include <boost/range/iterator_range.hpp>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector

#include "Networkland.h"
#include "Idea.h"
#include "global.h"

using namespace boost;
using namespace Rcpp;
using namespace std;

// constructor
Networkland::Networkland(std::string graphstring) {

  graph_t graph(0);

  dynamic_properties dp(ignore_other_properties);
  dp.property("name",       get(&Vertex::name,   graph));
  dp.property("distance",   get(&Edge::distance, graph));

  boost::ref_property_map<graph_t *, std::string> gname(get_property(graph, graph_name));
  dp.property("graph_name", gname);

  std::istringstream is(graphstring);

  read_graphml(is, graph, dp);
  Rcout << "I created a new graph: '" << get_property(graph, graph_name) << "'\n";

  this->env = graph;
}

// getter
graph_t Networkland::get_graph() {
  return env;
}

// R-exporter
// std::string Networkland::export_graph() {
//
//   graph_t graph = this->get_graph();
//
//   dynamic_properties dp(ignore_other_properties);
//   dp.property("name", get(&Vertex::name,  graph));
//   dp.property("age",   get(&Vertex::age, graph));
//   dp.property("gender",   get(&Vertex::gender, graph));
//   dp.property("friendship",   get(&Edge::friendship,   graph));
//   dp.property("advice",   get(&Edge::advice,   graph));
//
//   ostringstream fout;
//   write_graphml(fout,
//                 this->get_graph(),
//                 dp,
//                 false);
//   string test = fout.str();
//
//   return test;
// }

// developer
Networkland Networkland::develop() {

  // copy Networkland object to prepare a successor in the timeline
  Networkland newland = *this;

  // extract graph from Networkland
  graph_t g = newland.get_graph();

  // define vertex iterator object
  typedef graph_traits<graph_t>::vertex_iterator vertex_iter;

  // create a pair to store the vertex iterators
  std::pair<vertex_iter, vertex_iter> vp;

  // keep vp.first at the start
  vp = vertices(g);

  // create offset vector
  std::vector<int> myvector;
  for (int i=0; i<num_vertices(g); ++i) {
    myvector.push_back(i);
  }

  // using randWrapper to shuffle offset vector
  std::random_shuffle(myvector.begin(), myvector.end(), randWrapper);

  // iterate over the vertices effectively shuffled by the offset
  vertex_iter dummy_iter;
  for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it) {
    dummy_iter = vp.first + *it;
    //Rcout << g[*dummy_iter].name << std::endl;

    // idea act and interact here:

    // birth of ideas
    double prop_birth = 0.5; //probabilities here are just dummies

    if (randunifrange(1, 2) == 1) {
      Idea* newidea = new Idea();
      g[*dummy_iter].mind.push_back(newidea);
    }

    std::vector<Idea*> v = g[*dummy_iter].mind;

    for(std::vector<Idea*>::size_type i = 0; i != v.size(); i++) {
      Rcout << v[i]->get_identity() << std::endl;
    }

    // mutate
    double prop_mutate = 0.1;



    // conjugate
    double prop_conjugate = 0.1;

    // infect
    double prop_infect = 0.1;

  }
  Rcout << std::endl;

  return newland;
}