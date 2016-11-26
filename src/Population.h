#ifndef _gluesless_RCPP_POPULATION_H
#define _gluesless_RCPP_POPULATION_H

#include <Rcpp.h>
using namespace Rcpp;

class Population {
public:
  //constructor
  Population(double size_, double birthrate_, double deathrate_);

  // getter
  double size_get();

  // develop function
  void develop(Function popdevel);

private:
  // attributes
  double birthrate;
  double deathrate;
  double size;
};

#endif