//
// Created by Alex M on 7/7/25.
//

#ifndef ACC_NUMBER_GENERATOR_H
#define ACC_NUMBER_GENERATOR_H

#include <random>
#include <vector>

namespace generators {

class NumberGenerator {
private:
  std::mt19937 m_generator;
  unsigned int m_seed;

public:
  // Constructor with optional seed (uses global seed by default)
  NumberGenerator(unsigned int seed = 0);

  // Set seed for this instance
  void setSeed(unsigned int seed);

  // Get current seed for this instance
  unsigned int getSeed() const;

  // Generate random integer in range [min, max]
  int irand(int min, int max);

  static NumberGenerator defaultGenerator() {
    static NumberGenerator default_generator;
    return default_generator;
  }

  // Generate vector of n random integers in range [min, max]
  std::vector<int> irand_vector(int min, int max, size_t n);
};
} // namespace generators
#endif // ACC_NUMBER_GENERATOR_H
