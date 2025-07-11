//
// Created by Alex M on 7/7/25.
//

#include <gtest/gtest.h>
#include "alphabet.h"
#include "word.h"

namespace {

using namespace acc;
TEST(Alphabet, Test1) {
  {
    FiniteAlphabet a({"a", "b"});
    Word w(std::list<int>{-1,-2,-2,1});
    EXPECT_EQ(a.toString(w), "a^-1 b^-2 a");
  }
}
} // namespace