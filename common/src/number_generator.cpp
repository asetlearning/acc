//
// Created by Alex M on 7/7/25.
//

#include "number_generator.h"

namespace generators {
NumberGenerator::NumberGenerator(unsigned int seed) {
  // If seed is 0, use a random seed
  if (seed == 0) {
    std::random_device rd;
    m_seed = rd();
  } else {
    m_seed = seed;
  }

  // Initialize this instance's generator
  m_generator.seed(m_seed);
}

void NumberGenerator::setSeed(unsigned int seed) {
  m_seed = seed;
  m_generator.seed(m_seed);
}

unsigned int NumberGenerator::getSeed() const {
  return m_seed;
}

int NumberGenerator::irand(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(m_generator);
}

std::vector<int> NumberGenerator::irand_vector(int min, int max, size_t n) {
  std::vector<int> result;
  result.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    result.push_back(irand(min, max));
  }
  return result;
}
} // namespace generators