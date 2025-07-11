//
// Principal Author: Alex Myasnikov (2002, 2025)
//

#include "ac_transformations.h"

#include <sstream>

#include "logger.h"

namespace acc {

AC2TransformationsSet::AC2TransformationsSet()
  : n_generators_(2)
  , n_relators_(2)
  , n_tranformations_(0)
  , transforms_alphabet_({"r0", "r1", "a", "b"})
  , group_alhpabet_({"a", "b"}) {
  // fill out the transformations
  n_tranformations_ = n_relators_ + 2 * n_relators_ * (n_relators_ - 1) + 2 * n_relators_ * n_generators_;
  transformations_.reserve(n_tranformations_);

  // This is (r1, r2)
  AC2Tuple origin(Word(1), Word(2));

  int t_count = 0;
  for (size_t i = 0; i < n_relators_; ++i) {
    // add r->r^-1
    auto image = origin;
    image[i] = Word(i + 1).inverse();
    transformations_.emplace_back(origin, image, std::format("t{} (AC1)", ++t_count));

    // add r_i -> r_i*r_j, i!=j
    for (int j = 0; j < n_relators_; j++) {
      if (j != i) {
        image[i] = Word(i + 1) * Word(j + 1);
        transformations_.emplace_back(origin, image, std::format("t{} (AC2)", ++t_count));
      }
    }

    // add r_i -> r_j*r_i, i!=j  ????????????????
    for (int j = 0; j < n_relators_; j++) {
      if (j != i) {
        image[i] = Word(j + 1) * Word(i + 1);
        transformations_.emplace_back(origin, image, std::format("t{} (AC2)", ++t_count));
      }
    }

    // add r_i -> x_j^-1 r_i x_j
    for (int j = 0; j < n_generators_; j++) {
      image[i] = Word(j + 1 + n_relators_).inverse() * Word(i + 1) * Word(j + 1 + n_relators_);
      transformations_.emplace_back(origin, image, std::format("t{} (AC3)", ++t_count));
    }

    // add r_i -> x_j r_i x_j^-1
    for (int j = 0; j < n_generators_; j++) {
      image[i] = Word(j + 1 + n_relators_) * Word(i + 1) * Word(j + 1 + n_relators_).inverse();
      transformations_.emplace_back(origin, image, std::format("t{} (AC3)", ++t_count));
    }
  }

  // Sanity checks
  if (n_tranformations_ != t_count) {
    logger::fatal("Number of transformations is not equal to the number of added transformations.");
  }
}

AC2Tuple AC2TransformationsSet::apply(int ti, const AC2Tuple& p) const {
  return transformations_[ti].apply(p);
}

void AC2TransformationsSet::print(std::ostream& out, int i) const {
  transformations_[i].print(out, transforms_alphabet_);
  out << flush;
}

void AC2TransformationsSet::print(std::ostream& out) const {
  out << n_tranformations_ << ": " << std::endl;
  for (size_t i = 0; i < n_tranformations_; i++) {
    transformations_[i].print(out, transforms_alphabet_);
    out << std::endl;
  }
}

AC2Tuple AC2Transformation::apply(const AC2Tuple& w) const {
  // To apply a transformation, we replace relation gens (r1,r2) with
  // the corresponding words in the tuple (w0, w1).
  // For example, if the transformation is {r0->r0, r1->r1*r0} then the result tuple is (w0,w1*w0)


  // this is hardcoded for case 2
  // need to create image which will be substituted into
  // transformations
  std::vector<Word> replace_image(4);
  replace_image[0] = w.first();
  replace_image[1] = w.second();
  replace_image[2] = Word(1);
  replace_image[3] = Word(2);

  AC2Tuple result;
  result[0] = image_.first().replaceGenerators(replace_image).freelyReduce();
  result[1] = image_.second().replaceGenerators(replace_image).freelyReduce();

  return result;
}

void AC2Transformation::print(std::ostream& out, const FiniteAlphabet& alphabet) const {
  out << label_ << ": " << alphabet.toString(origin_.first()) << "->" << alphabet.toString(image_.first()) << ", "
      << alphabet.toString(origin_.second()) << "->" << alphabet.toString(image_.second()) << std::endl;
}
} // namespace acc