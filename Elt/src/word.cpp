//
// Created by Alex M on 7/7/25.
//

#include "word.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <tuple>
#include <vector>


#include "logger.h"
#include "number_generator.h"

namespace acc {

void Word::push_back(int g) {
  if (the_word_.empty())
    the_word_.push_back(g);
  else {
    int e = *(--the_word_.end());
    if (e + g == 0)
      the_word_.pop_back();
    else
      the_word_.push_back(g);
  }
}

void Word::push_front(int g) {
  if (the_word_.empty())
    the_word_.push_front(g);
  else {
    int e = *(the_word_.begin());
    if (e + g == 0)
      the_word_.pop_front();
    else
      the_word_.push_front(g);
  }
}

Word::Word(const std::initializer_list<int>& gens)
  : the_word_(gens) {}

Word::Word(const std::list<int>& gens) {
  the_word_.resize(gens.size());
  std::copy(gens.begin(), gens.end(), the_word_.begin());
  freelyReduce();
}

Word::Word(const std::vector<int>& gens) {
  the_word_.resize(gens.size());
  std::copy(gens.begin(), gens.end(), the_word_.begin());
  freelyReduce();
}

Word::Word(int g) {
  push_back(g);
}

void Word::clear() {
  the_word_.clear();
}

Word& Word::operator^=(int power) {
  Word base = (power > 0 ? *this : this->inverse());
  this->clear();
  int ap = abs(power);
  for (int i = 0; i < ap; ++i)
    *this *= base;
  return *this;
}

Word& Word::operator^=(const Word& w) {
  *this *= w;
  for (int m_it : w.the_word_)
    push_front(-m_it);
  return *this;
}

Word& Word::operator*=(const Word& w) {
  for (int m_it : w.the_word_)
    push_back(m_it);
  return *this;
}

bool Word::doesContain(int gen) const {
  for (int g_it : the_word_)
    if (g_it == gen || g_it == -gen)
      return true;

  return false;
}


void Word::cyclicLeftShift() {
  if (the_word_.size() < 2)
    return;
  push_back(*the_word_.begin());
  the_word_.pop_front();
}

void Word::cyclicRightShift() {
  if (the_word_.size() < 2)
    return;
  push_front(*--the_word_.end());
  the_word_.pop_back();
}

int Word::isIn(int gen) const {
  int result = 0;
  auto g_it = the_word_.begin();
  for (; g_it != the_word_.end(); ++g_it)
    if (*g_it == gen || *g_it == -gen)
      result += 1;
  return result;
}

int Word::exponentSum(int gen) const {
  int result = 0;
  auto g_it = the_word_.begin();
  for (; g_it != the_word_.end(); ++g_it)
    if (*g_it == gen || *g_it == -gen)
      result += 1;
  return result;
}


Word Word::inverse() const {
  Word result;
  auto g_it = the_word_.begin();
  for (; g_it != the_word_.end(); ++g_it)
    result.push_front(-*g_it);
  return result;
}

bool Word::operator==(const Word& wr) const {
  if (the_word_.size() != wr.the_word_.size())
    return false;

  auto g_it1 = the_word_.begin();
  auto g_it2 = wr.the_word_.begin();
  while (g_it1 != the_word_.end())
    if (*(g_it1++) != *(g_it2++))
      return false;

  return true;
}

bool Word::operator!=(const Word& wr) const {
  return !(*this == wr);
}

bool Word::operator<(const Word& wr) const {
  int len1 = the_word_.size();
  int len2 = wr.the_word_.size();
  if (len1 < len2)
    return true;
  if (len1 > len2)
    return false;

  auto g_it1 = the_word_.begin();
  auto g_it2 = wr.the_word_.begin();
  for (int t = 0; t < len1; ++t) {
    if (*g_it1 < *g_it2)
      return true;
    if (*(g_it1++) > *(g_it2++))
      return false;
  }

  return false;
}

bool Word::operator>(const Word& wr) const {
  int len1 = the_word_.size();
  int len2 = wr.the_word_.size();
  if (len1 < len2)
    return true;
  if (len1 > len2)
    return false;

  auto g_it1 = the_word_.begin();
  auto g_it2 = wr.the_word_.begin();
  for (int t = 0; t < len1; ++t) {
    if (*g_it1 > *g_it2)
      return true;
    if (*(g_it1++) < *(g_it2++))
      return false;
  }

  return false;
}


// void Word::insert(WordIterator it, int g) {
//   the_word_.insert(it.theIterator, g);
// }
//
// template <class ConstIntIterator>
// void Word::insert(WordIterator it, ConstIntIterator B, ConstIntIterator E) {
//   the_word_.insert(it.theIterator, B, E);
// }
//
// void Word::insert(int pos, int g) {
//   if (pos < 0 || the_word_.size() < pos)
//     return;
//   std::list<int>::iterator l_it = the_word_.begin();
//   for (; pos > 0; --pos, ++l_it)
//     ;
//   the_word_.insert(l_it, g);
// }
//
// template <class ConstIntIterator>
// void Word::insert(int pos, ConstIntIterator B, ConstIntIterator E) {
//   if (pos < 0 || the_word_.size() < pos)
//     return;
//   std::list<int>::iterator l_it = the_word_.begin();
//   for (; pos > 0; --pos, ++l_it)
//     ;
//   the_word_.insert(l_it, B, E);
// }
//
//
////=========================================================
//
// void Word::replace(WordIterator it, const Generator& g) {
//  *(it.theIterator) = g;
//}
//
// void Word::replace(int pos, const Generator& g) {
//  if (pos < 0 || the_word_.size() < pos)
//    return;
//  std::list<int>::iterator l_it = the_word_.begin();
//  for (; pos > 0; --pos, ++l_it)
//    ;
//  *l_it = g;
//}
//
////=========================================================
//
// template <class ConstIntIterator>
// void Word::replace(WordIterator it, ConstIntIterator B, ConstIntIterator E) {
//  // std::list< int >::iterator l_it =
//  std::list<int>::iterator c_it = it.theIterator;
//  for (; c_it != the_word_.end() && B != E; ++c_it, ++B)
//    *c_it = *B;
//}
//
////=========================================================


void Word::cyclicallyPermute(int n) {
  int len = the_word_.size();
  if (n == 0 || len == 0)
    return;

  // make it positive
  n %= len;
  n = n < 0 ? n + len : n;

  Word segm1 = *this;
  segm1.initialSegment(n);
  Word segm2 = *this;
  segm2.terminalSegment(n);
  *this = segm2 * segm1;
}

Word Word::cyclicallyPermute(int n) const {
  Word result(*this);
  result.cyclicallyPermute(n);
  return result;
}

void Word::segment(int from, int to) {
  initialSegment(to);
  terminalSegment(from);
}

Word Word::segment(int from, int to) const {
  Word result(*this);
  result.segment(from, to);
  return result;
}

void Word::initialSegment(int len) {
  if (len <= 0) {
    the_word_.clear();
    return;
  }

  for (int left = the_word_.size() - len; left > 0; --left)
    the_word_.pop_back();
}

Word Word::initialSegment(int len) const {
  Word result(*this);
  result.initialSegment(len);
  return result;
}

void Word::terminalSegment(int len) {
  int l = len < the_word_.size() ? len : the_word_.size();
  for (int t = 0; t < l; ++t)
    the_word_.pop_front();
}

Word Word::terminalSegment(int len) const {
  Word result(*this);
  result.terminalSegment(len);
  return result;
}


void Word::cyclicallyReduce() {
  while (the_word_.size() > 1) {
    int b = *the_word_.begin();
    int e = *--the_word_.end();
    if (e + b)
      break;
    the_word_.pop_back();
    the_word_.pop_front();
  }
}

void Word::cyclicallyReduce(Word& conjugator) {
  conjugator.the_word_.clear();
  while (the_word_.size() > 1) {
    int b = *the_word_.begin();
    int e = *--the_word_.end();
    if (e + b)
      break;
    the_word_.pop_back();
    the_word_.pop_front();
    conjugator.the_word_.push_front(e);
  }
}

Word Word::cyclicallyReduce(Word& conjugator) const {
  Word result(*this);
  result.cyclicallyReduce(conjugator);
  return result;
}

int Word::getPower(Word& base) const {
  int len = the_word_.size();
  if (len <= 1)
    return 1;

  int up = sqrt((double) len) + 1;

  // Decompose len into a product of primes
  std::list<std::pair<int, int>> primes;
  std::list<std::pair<int, int>> primes_to_use;

  for (int i = 2; i < up; ++i) {
    bool prime = true;
    auto p_it = primes.begin();
    for (; p_it != primes.end(); ++p_it) {
      int a = (*p_it).first;
      int b = (*p_it).second;
      (*p_it).second = b + 1 == a ? (prime = false) : b + 1;
    }
    if (prime) {
      primes.push_back(std::pair<int, int>(i, 0));
      int count = 0;
      while (len % i == 0) {
        ++count;
        len /= i;
      }
      if (count) {
        primes_to_use.push_back(std::pair<int, int>(i, count));
        up = sqrt((double) len) + 1;
      }
    }
  }
  if (len > 1)
    primes_to_use.push_back(std::pair<int, int>(len, 1));

  len = the_word_.size();

  // Construct a std::vector of generators (to have indexed access)
  std::vector<int> wrd_vct(len);
  auto g_it = the_word_.begin();
  for (int j = 0; g_it != the_word_.end(); ++j, ++g_it)
    wrd_vct[j] = *g_it;

  // Find the power
  std::list<std::pair<int, int>>::iterator p_it = primes_to_use.begin();
  for (; p_it != primes_to_use.end(); ++p_it) {
    int parts = (*p_it).first;
    int count = (*p_it).second;
    int shrt_len = len / parts;

    bool progress = true;
    for (int t = 0; t < count && progress; ++t) {
      for (int offset = 0; offset < shrt_len && progress; ++offset) {
        int e = wrd_vct[offset];
        for (int j = offset; j < len && progress; j += shrt_len)
          if (wrd_vct[j] != e)
            progress = false;
      }
      if (progress)
        shrt_len = (len = shrt_len) / parts;
    }
  }

  base = *this;
  base.initialSegment(len);
  return the_word_.size() / len;
}

void Word::freelyReduce(word_iterator beg, word_iterator end) {
  // TODO: fix it
  word_iterator& b = beg; //.theIterator;
  word_iterator& e = end; //.theIterator;

  for (auto cur_it = b; cur_it != e && cur_it != the_word_.end();) {
    auto cur_it2 = cur_it;
    if (++cur_it2 == the_word_.end())
      break;
    if (*cur_it + *cur_it2) {
      ++cur_it;
      continue;
    }

    if (cur_it2 == e)
      ++e;
    the_word_.erase(cur_it);
    cur_it = the_word_.erase(cur_it2);
    if (cur_it != the_word_.begin())
      --cur_it;
  }
}

Word Word::randomWord(int gens, int wLen) {
  if (wLen == 0)
    return Word();

  int old = 0;
  WordContainerType result;
  for (int i = 0; i < wLen; ++i) {
    int div = i == 0 ? 2 * gens : 2 * gens - 1;
    // int g = ::rand()%div-gens;
    int g = generators::NumberGenerator::defaultGenerator().irand(0, div - 1) - gens;
    g = g >= 0 ? g + 1 : g;
    if (g + old == 0)
      g = gens;
    result.push_back(old = g);
  }

  return Word(result);
}

Word Word::randomWord(int gens, int wLenMin, int wLenMax) {
  int wLen = generators::NumberGenerator::defaultGenerator().irand(wLenMin, wLenMax);
  return randomWord(gens, wLen);
}

void Word::push_back(const Word& w) {
  for (const auto& g : w.the_word_) {
    push_back(g);
  }
}

void Word::push_front(const Word& w) {
  for (auto w_it = w.end(); w_it != w.begin();)
    push_front(*--w_it);
}

Word Word::power(int t) const {
  if (t == 0)
    return Word();

  Word result = (t < 0 ? inverse() : *this);
  for (int i = 1; i < abs(t); ++i)
    result *= (t < 0 ? inverse() : *this);
  return result;
}

Word Word::replaceGenerators(const std::vector<Word>& images) const {
  Word result;

  for (const auto& g : the_word_) {
    if (abs(g) - 1 >= images.size()) {
      logger::fatal("Word::replaceGenerators() : image vector index overflow.");
    }
    result *= (g > 0 ? images[abs(g) - 1] : images[abs(g) - 1].inverse());
  }
  return result;
}
} // namespace acc