//
// Created by Alex M on 7/7/25.
//

#include <gtest/gtest.h>
#include "number_generator.h"

namespace {

auto def_generator = generators::NumberGenerator::defaultGenerator();

TEST(NumberGenerator, Test1) {
  {
    EXPECT_EQ(generators::NumberGenerator::defaultGenerator().getSeed(), def_generator.getSeed());
  }
  {
    auto new_gen = generators::NumberGenerator(123455);
    EXPECT_NE(new_gen.getSeed(), def_generator.getSeed());
  }
}
TEST(NumberGenerator, Test2) {
  auto new_gen = generators::NumberGenerator(123455);
  {
    EXPECT_EQ(new_gen.irand_vector(0, 10, 5), std::vector({ 3, 4, 8, 0, 8 }));
  }
  {
    EXPECT_EQ(
        generators::NumberGenerator::defaultGenerator().irand_vector(0, 10, 5), def_generator.irand_vector(0, 10, 5));
  }
  def_generator.setSeed(123455);
  {
    EXPECT_EQ(def_generator.irand_vector(0, 10, 5), std::vector({ 3, 4, 8, 0, 8 }));
  }
}
} // namespace