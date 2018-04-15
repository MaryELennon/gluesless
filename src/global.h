#include <string>
#include <random>
#include <algorithm>
#include <math.h>

inline int randunifrange(int start, int stop) {
  std::random_device rd;     // only used once to initialise (seed) engine
  std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
  std::uniform_int_distribution<int> uni(start, stop); // guaranteed unbiased
  return uni(rng);
}

inline int get_number_of_digits (int i) {
  return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

// https://stackoverflow.com/questions/1577475/c-sorting-and-keeping-track-of-indexes
template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v) {

  // initialize original index locations
  std::vector<size_t> idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  sort(idx.begin(), idx.end(),
       [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

  return idx;
}

// http://www.stats.ox.ac.uk/~marchini/teaching/L6/L6.slides.pdf
inline double normal_distribution_pdf(double x) {
  return (1.0/sqrt(2.0 * M_PI)) * exp(-pow((x - 1), 2.0) / (2.0 * pow(0.5, 2.0)));
}
