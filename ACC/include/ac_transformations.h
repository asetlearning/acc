//
// Principal Author: Alex Myasnikov (2002, 2025)
//

#ifndef ACC_TRANSFORMATIONS_H
#define ACC_TRANSFORMATIONS_H

#include <iostream>
#include <list>
#include <vector>

#include "alphabet.h"
#include "logger.h"
#include "word.h"

namespace acc {

class AC2Tuple {
public:
  AC2Tuple() = default;
  AC2Tuple(const std::vector<Word>& w) {
    if (w.size() != 2) {
      logger::fatal("Must contain 2 words.");
    }
    w1_ = w[0];
    w2_ = w[1];
  }

  AC2Tuple(Word w1, Word w2)
    : w1_(std::move(w1))
    , w2_(std::move(w2)) {}

  bool operator==(const AC2Tuple& other) const {
    return w1_ == other.w1_ && w2_ == other.w2_;
  }

  inline const Word& first() const {
    return w1_;
  }

  inline const Word& second() const {
    return w2_;
  }

  inline Word& first() {
    return w1_;
  }

  inline Word& second() {
    return w2_;
  }

  Word& operator[](size_t i) {
    if (i < 0 || i >= 2) {
      logger::fatal(std::format("AC2Tuple index {} out of bounds.", i));
    }
    if (i == 0) {
      return w1_;
    } else {
      return w2_;
    }
  }

  AC2Tuple replaceGenerators(const std::vector<Word>& replacements) const {
    return {
        w1_.replaceGenerators(replacements).freelyReduce(), w2_.replaceGenerators(replacements).freelyReduce()
    };
  }

private:
  Word w1_;
  Word w2_;
};

class AC2Transformation {
public:
  //! Defines transformation of words in origin_ into words in image_
  //  with label_
  AC2Transformation(AC2Tuple o, AC2Tuple i, std::string l)
    : origin_(std::move(o))
    , image_(std::move(i))
    , label_(std::move(l)) {}

  AC2Tuple apply(const AC2Tuple& w) const;

  void print(std::ostream& out, const FiniteAlphabet& alphabet) const;

private:
  AC2Tuple origin_;
  AC2Tuple image_;
  std::string label_;
};

class AC2TransformationsSet {
public:
  AC2TransformationsSet();

  AC2Tuple apply(int i, const AC2Tuple& w) const;

  void print(std::ostream& out) const;

  void print(std::ostream& out, int i) const;

  inline size_t numOfTransformations() const {
    return transformations_.size();
  }

  inline const FiniteAlphabet& groupAlphabet() const {
    return group_alhpabet_;
  }

  inline const FiniteAlphabet& transformsAlphabet() const {
    return transforms_alphabet_;
  }

private:
  size_t n_generators_;
  size_t n_relators_;
  size_t n_tranformations_;
  std::vector<AC2Transformation> transformations_;
  FiniteAlphabet transforms_alphabet_;
  FiniteAlphabet group_alhpabet_;
};
} // namespace acc
#endif // ACC_TRANSFORMATIONS_H
