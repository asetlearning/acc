//
// Created by Alex M on 7/7/25.
//

#include <gtest/gtest.h>
#include "ac_transformations.h"

#include "word.h"

namespace {
using namespace acc;

#define PRINT_WORD(w) ac_transformations.groupAlphabet().toString(w)

#define PRINT_TUPLE(t)                                                                                                 \
  ac_transformations.groupAlphabet().toString(t.first()) + "," + ac_transformations.groupAlphabet().toString(t.second())

#define APPLY_SEQUENCE(sequence, the_tuple)                                                                            \
  {                                                                                                                    \
    size_t counter = 0;                                                                                                \
    for (const auto& ti : sequence) {                                                                                  \
      iter_tuple = ac_transformations.apply(ti, iter_tuple);                                                           \
      std::cout << ++counter << " : " << ac_transformations.groupAlphabet().toString(iter_tuple.first()) << ", "       \
                << ac_transformations.groupAlphabet().toString(iter_tuple.second()) << " : "                           \
                << iter_tuple.first().length() + iter_tuple.second().length() << std::endl;                            \
    }                                                                                                                  \
  }

TEST(ACC, Test1) {
  AC2TransformationsSet ac_transformations;
  ac_transformations.print(std::cout);
}
TEST(ACC, AK12) {
  const auto a = 1;
  const auto b = 2;

  AC2TransformationsSet ac_transformations;
  AC2Tuple ak12(Word({a, a, -b, -b, -b}), Word({a, b, a, -b, -a, -b}));

  // Solution from the ACC99 paper
  //  1 : r0 → r0^−1        : t1 (AC1): r0->r0^-1, r1->r1
  //  2 : r1 → r1 r0        : t9 (AC2): r0->r0, r1->r1 r0
  //  3 : r1 → a^−1 r1 a    : t11 (AC3): r0->r0, r1->a^-1 r1 a
  //  4 : r1 → b^−1 r1 b    : t12 (AC3): r0->r0, r1->b^-1 r1 b
  //  5 : r0 → a^−1 r0 a.   : t4 (AC3): r0->a^-1 r0 a, r1->r1
  //  6 : r0 → r0 r1.       : t2 (AC2): r0->r0 r1, r1->r1
  //  7 : r1 → b^−1 r1 b    : t12 (AC3): r0->r0, r1->b^-1 r1 b
  //  8 : r1 → r1 r0        : t9 (AC2): r0->r0, r1->r1 r0
  //
  //  9 : r1 → ba^−1 b r1 b^−1 a b^−1 : composition of three
  //
  //  91: r1 → b r1  b^−1   : t14 (AC3): r0->r0, r1->b r1 b^-1
  //  92: r1 → a^−1 r1 a    : t11 (AC3): r0->r0, r1->a^-1 r1 a
  //  93: r1 →  b r1 b^−1   : t14 (AC3): r0->r0, r1->b r1 b^-1
  //
  //  10 : r0 → r0^−1       : t1 (AC1): r0->r0^-1, r1->r1
  //  11 : r1 → r1 r0       : t9 (AC2): r0->r0, r1->r1 r0
  //  12 : r0 → r0 r1       : t2 (AC2): r0->r0 r1, r1->r1
  //  13 : r0 → r0 r1       : t2 (AC2): r0->r0 r1, r1->r1
  //  14 : r0 → r0 r1       : t2 (AC2): r0->r0 r1, r1->r1
  //  15 : r0 → r0^−1       : t1 (AC1): r0->r0^-1, r1->r1
  //  16 : r1 → r1 r0       : t9 (AC2): r0->r0, r1->r1 r0
  //  17 : r1 → r1 r0       : t9 (AC2): r0->r0, r1->r1 r0
  //  18 : r1 → r1^−1       : t8 (AC1): r0->r0, r1->r1^-1
  //  19 : r0 → r0^−1       : t1 (AC1): r0->r0^-1, r1->r1

  const std::vector<size_t> solution_sequence = {0, 8, 10, 11, 3, 1, 11, 8, 13, 10, 13, 0, 8, 1, 1, 1, 0, 8, 8, 7, 0};
  auto iter_tuple = ak12;
  APPLY_SEQUENCE(solution_sequence, iter_tuple)
  EXPECT_EQ(iter_tuple, AC2Tuple(Word(2), Word(1)));
}
TEST(ACC, ACCGenetic_G2) {
  const auto x = 1;
  const auto y = 2;

  AC2TransformationsSet ac_transformations;
  // Presentation G2 from ACC99 paper
  AC2Tuple acc_g2(Word({y, x, -y, -x, -x}), Word({-x, y, y, x, -y, -y, -y}));

  // Solution for presentation G2 from the ACC99 paper
  // 1: r1 -> x r1 x^−1. :  t13 (AC3): r0->r0, r1->a r1 a^-1
  // 2 : r1 -> r1^−1 : t8 (AC1): r0->r0, r1->r1^-1
  // 3 : r1 -> y^−1 r1 y : t12 (AC3): r0->r0, r1->b^-1 r1 b
  // 4 : r1 -> r1 r0 : t9 (AC2): r0->r0, r1->r1 r0
  // 5 : x  -> x^−1 ???????
  // 6 : r1 -> y r1 y^−1 : t14 (AC3): r0->r0, r1->b r1 b^-1
  // 7 : r1 -> r1 r0 : t9 (AC2): r0->r0, r1->r1 r0
  // 8 : r1 -> x2 r1 x^−2 ???
  // 81: t14 (AC3): r0->r0, r1->b r1 b^-1
  // 82: t14 (AC3): r0->r0, r1->b r1 b^-1

  // 9 : r1 -> r1 r0 : t9 (AC2): r0->r0, r1->r1 r0
  // 10 : r1 -> r1^−1 : t8 (AC1): r0->r0, r1->r1^-1
  // 11 : y -> yx^−2 ??????
  // 12 : r1 -> r1^−1 : t8 (AC1): r0->r0, r1->r1^-1
  // 13 : r0 -> r0^−1 : t1 (AC1): r0->r0^-1, r1->r1

  // 14 : r1 -> y r1^−1 y^−1 ????
  // 141 : t14 (AC3): r0->r0, r1->b r1 b^-1
  // 142 : t8 (AC1): r0->r0, r1->r1^-1

  // 15 : r0 -> r0 r1 : t2 (AC2): r0->r0 r1, r1->r1
  // 16 : r0 -> x^2 r0 x^−2 ????

  // 161: t6 (AC3): r0->a r0 a^-1, r1->r1
  // 162: t6 (AC3): r0->a r0 a^-1, r1->r1

  // 17 : r1 -> r1^−1 : t8 (AC1): r0->r0, r1->r1^-1
  // 18 : r1 ->  r1 r0 :  t9 (AC2): r0->r0, r1->r1 r0
  // 19 : r1 -> r1^−1 : t8 (AC1): r0->r0, r1->r1^-1

  auto iter_tuple = acc_g2;
  const std::vector<size_t> solution_sequence_1 = {12, 7, 11, 8};
  APPLY_SEQUENCE(solution_sequence_1, iter_tuple)

  iter_tuple = iter_tuple.replaceGenerators({Word({-x}), Word({y})});

  const std::vector<size_t> solution_sequence_2 = {13, 8, 13, 13, 8, 7};
  APPLY_SEQUENCE(solution_sequence_2, iter_tuple)

  iter_tuple = iter_tuple.replaceGenerators({Word({x}), Word({y, -x, -x})});

  const std::vector<size_t> solution_sequence_3 = {7, 0, 13, 7, 1, 5, 5, 7, 6, 7};
  APPLY_SEQUENCE(solution_sequence_3, iter_tuple)

  std::cout << " ----> " << PRINT_TUPLE(iter_tuple) << std::endl;
}
TEST(ACC, ACCGenetic_G3) {
  const auto x = 1;
  const auto y = 2;

  AC2TransformationsSet ac_transformations;
  // Presentation G3 from ACC99 paper
  AC2Tuple acc_g3(Word({-x, y, y, x, -y, -y, -y}), Word({x, x, -y, -x, -y}));

  //  1 : r0 -> x r0 x^−1 : t6 (AC3): r0->a r0 a^-1, r1->r1
  //  2 : r0 -> r0 r1 : t2 (AC2): r0->r0 r1, r1->r1

  //  3 : r1 -> x y x^−2 r1 x^2 y^−1 x^−1 ???????
  // 31: r1 -> x^−1 r1 x : t11 (AC3): r0->r0, r1->a^-1 r1 a
  // 32: r1 -> x^−1 r1 x. : t11 (AC3): r0->r0, r1->a^-1 r1 a
  // 33: r1 -> y r1 y^−1 : t14 (AC3): r0->r0, r1->b r1 b^-1
  // 34: r1 -> x r1  x^−1. t13 (AC3): r0->r0, r1->a r1 a^-1

  //  4 : r0 -> y^−2 r0 y^2 :
  // 41: r0 -> y^−1 r0 y: t5 (AC3): r0->b^-1 r0 b, r1->r1
  // 42: r0 -> y^−1 r0 y : t5 (AC3): r0->b^-1 r0 b, r1->r1

  //  5 : r0 -> r0 r1 : : t2 (AC2): r0->r0 r1, r1->r1

  //  6 : r1 -> x y^−1 x^−1 r1 x y x^−1 ???
  // 61: r1 →  x^−1 r1 x : t11 (AC3): r0->r0, r1->a^-1 r1 a
  // 62: r1 → y^−1  r1  y : t12 (AC3): r0->r0, r1->b^-1 r1 b
  // 62: r1 -> x  r1 x^−1 : t13 (AC3): r0->r0, r1->a r1 a^-1


  const std::vector<size_t> solution_sequence = {5, 1, 10, 10, 13, 12, 4, 4, 1, 10, 11, 12};
  auto iter_tuple = acc_g3;
  APPLY_SEQUENCE(solution_sequence, iter_tuple)
  // apply auto
  const std::vector<Word> image = {Word({-y, -x}), Word({x, -y, -x})};
  const auto& image_tuple = iter_tuple.replaceGenerators(image);
  std::cout << PRINT_TUPLE(image_tuple) << std::endl;
  EXPECT_EQ(image_tuple, AC2Tuple(Word({y, y, -x, -x, y}), Word({y, x, y, -x, -y, -x})));
}
TEST(ACC, ACCGenetic_G4) {
  const auto a = 1;
  const auto b = 2;

  AC2TransformationsSet ac_transformations;
  // Presentation G from section 6 of the ACC99 paper
  AC2Tuple acc_g4(Word({-b, a, b, -a, -a}), Word({-a, b, a, -b, -b}));

  // 1 : r1 -> a r1 a^−1  : t13 (AC3): r0->r0, r1->a r1 a^-1
  // 2 : r1 -> b^−1 r1 b  : t12 (AC3): r0->r0, r1->b^-1 r1 b
  // 3 : r1 -> r1 r0 : t9 (AC2): r0->r0, r1->r1 r0
  // 4 : r0 -> a^−1 r0 a : t4 (AC3): r0->a^-1 r0 a, r1->r1
  // 5 : r0 -> r0 r1 : t2 (AC2): r0->r0 r1, r1->r1
  // 6 : r0 -> a r0 a^−1 : t6 (AC3): r0->a r0 a^-1, r1->r1
  // 7 : r1 -> a^−1 r1 a : t11 (AC3): r0->r0, r1->a^-1 r1 a
  // 8 : r1 -> r1^−1 : t8 (AC1): r0->r0, r1->r1^-1
  // 9 : r1 -> r1 r0 : t9 (AC2): r0->r0, r1->r1 r0
  // 10 : r1 -> r1^−1 : t8 (AC1): r0->r0, r1->r1^-1
  // 11 : r0 -> r0 r1 : t2 (AC2): r0->r0 r1, r1->r1
  // 12 : r0 -> r0 r1 : t2 (AC2): r0->r0 r1, r1->r1
  // 13 : r0 ->r0^−1 : t1 (AC1): r0->r0^-1, r1->r1

  const std::vector<size_t> solution_sequence = {12, 11, 8, 3, 1, 5, 10, 7, 8, 7, 1, 1, 0};
  auto iter_tuple = acc_g4;
  APPLY_SEQUENCE(solution_sequence, iter_tuple)
  EXPECT_EQ(iter_tuple, AC2Tuple(Word({2}), Word({1})));
}
} // namespace