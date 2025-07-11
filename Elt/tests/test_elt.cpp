//
// Created by Alex M on 7/7/25.
//

#include <gtest/gtest.h>
#include "word.h"

namespace {
TEST(Elt, WordReduction) {
  {
    acc::Word w(std::list{-1, -2, 2, 1});
    EXPECT_EQ(w.freelyReduce(), acc::Word());
  }
  {
    const acc::Word w(std::list{2, -1, -2 });
    EXPECT_EQ(w.cyclicallyReduce(), acc::Word(-1));
  }
}
TEST(Elt, Inverse) {
  {
    acc::Word w(std::list{1, -2, -1, 2, 1});
    acc::Word winv(std::list{-1, -2, 1, 2, -1});
    EXPECT_EQ(w.inverse(), winv);
    EXPECT_EQ(winv.inverse(), w);
  }
}
TEST(Elt, Power) {
  {
    acc::Word w(std::list{1});
    acc::Word wp(std::list{1, 1, 1, 1, 1});
    EXPECT_EQ(w.power(5), wp);
  }
  {
    acc::Word w(std::list{1, -2, -1});
    acc::Word wp(std::list{1, -2, -2, -2, -1});
    EXPECT_EQ(w.power(3), wp);
  }
}
} // namespace