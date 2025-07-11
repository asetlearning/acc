//
// Created by Alex M on 7/7/25.
//

#ifndef ACC_WORD_H
#define ACC_WORD_H

#include <initializer_list>
#include <list>
#include <vector>

namespace acc {

class Word {
public:
  typedef std::list<int> WordContainerType;
  typedef WordContainerType::const_iterator word_const_iterator;
  typedef WordContainerType::iterator word_iterator;

  //! Default constructor (creates the empty word \f$w = \varepsilon\f$).
  Word() = default;

  explicit Word(const std::initializer_list<int>& gens);
  //! Constructs a word by its presentation (if the word defined in gens is not reduced then it reduces it).
  explicit Word(const std::vector<int>& gens);
  //! Constructs a word by its presentation (if the word defined in gens is not reduced then it reduces it).
  explicit Word(const std::list<int>& gens);
  //! Constructs a one letter word.
  explicit Word(int g);
  //! Copy construtor.
  Word(const Word& wr) = default;

  //! Empty the word.
  void clear();

  //! Comparison operator
  /*! The result of comparison of \f$u = u_1 \ldots u_k\f$ and \f$v = v_1 \ldots v_m\f$ is defined by
    \f$ u<v ~\Leftrightarrow~ k<m ~\vee~ ( k=m ~\wedge~ u_i<v_i \mbox{ where $i$ is the smallest index such that $u_i\ne
    v_i$}) \f$
  */
  bool operator<(const Word& wr) const;
  //! Comparison operator
  bool operator>(const Word& wr) const;
  //! Comparison operator
  bool operator==(const Word& wr) const;
  //! Comparison operator
  bool operator!=(const Word& wr) const;

  //! Multiply the word on the right by another word (the result is reduced)
  Word& operator*=(const Word& w);

  //! Multiply two words (the result is reduced)
  // TODO: move to cpp
  inline Word operator*(const Word& w) const {
    Word result(*this);
    result *= w;
    return result;
  }

  //! Conjugate a word by another word (the result is reduced)
  Word& operator^=(const Word& conjugator);

  // TODO: move to cpp
  Word operator^(const Word& conjugator) const {
    Word result(*this);
    result ^= conjugator;
    return result;
  }


  //! Conjugate a word by another word (the result is reduced)
  Word& operator^=(int power);
  // TODO: move to cpp
  Word operator^(int power) const {
    Word result(*this);
    result ^= power;
    return result;
  }


  //! Invert a word (works the same as inverse).
  inline Word operator-() const {
    auto result(*this);
    result.inverse();
    return result;
  }

  [[nodiscard]] word_const_iterator begin() const {
    return the_word_.begin();
  }
  [[nodiscard]] word_const_iterator end() const {
    return the_word_.end();
  }
  word_iterator begin() {
    return the_word_.begin();
  }
  word_iterator end() {
    return the_word_.end();
  }

  //! Freely reduce a word.
  Word freelyReduce() {
    freelyReduce(begin(), end());
    return *this;
  }

  [[nodiscard]] Word freelyReduce() const {
    auto result(*this);
    result.freelyReduce(result.begin(), result.end());
    return result;
  }

  //! Freely reduce a segment of a word defined by [B,E).
  void freelyReduce(word_iterator B, word_iterator E);
  // freely reduces a segment of a word specified by [beg,end].
  // Most of the operations produce freely reduced words,
  // except operations insert, remove. The function takes linear time to performs
  // which is not efficient. So, either try to avoid uses of functions insert and remove
  // or try to bound the changes in variables beg and end

  //! Generates a pseudo randomly reduced word of the length wLen over the alphabet \f$X = \{x_1,\ldots,x_n\}\f$.
  static Word randomWord(int n, int wLen);

  //! Generates a pseudo randomly reduced word of a length in [wLenMin,wLenMax] and  over the alphabet \f$X =
  //! \{x_1,\ldots,x_n\}\f$.
  static Word randomWord(int n, int wLenMin, int wLenMax);

  //! Get a constant representation the word.
  [[nodiscard]] inline const WordContainerType& getList() const {
    return the_word_;
  }

  //! Get a representation the word. This allows direct manipulation with the representation (which requires caution).
  inline WordContainerType& getList() {
    return the_word_;
  }

  //! Get the length of the word.
  [[nodiscard]] inline unsigned length() const {
    return size();
  }
  [[nodiscard]] inline unsigned size() const {
    return the_word_.size();
  }

  //! Multiply the word by a one-letter word defined by gen on the right. The result is being reduced.
  void push_back(int gen);

  //! Multiply the word by a one-letter word defined by gen on the left. The result is being reduced.
  void push_front(int gen);

  //! Multiply the word by a word on the right. The result is being reduced.
  void push_back(const Word& w);

  //! Multiply the word by a word on the left. The result is being reduced.
  void push_front(const Word& w);

  //! Remove the last symbol
  void pop_back() {
    the_word_.pop_back();
  }

  //! Remove the first symbol
  void pop_front() {
    the_word_.pop_front();
  }

  //! Determines the power of the word (as an element of a free monoid, not as an element of a free group).
  int getPower(Word& base) const;

  //! Checks if the word contains a generator given by gen.
  [[nodiscard]] bool doesContain(int gen) const;

  //! Shifts the word one position to the left, i.e., \f$cyclicLeftShift( x_1 x_2 \ldots x_{k-1} x_k ) = x_2 \ldots
  //! x_{k-1} x_k x_1 \f$.
  inline void cyclicLeftShift();

  //! Shifts the word one position to the right, i.e., \f$cyclicRightShift( x_1 x_2 \ldots x_{k-1} x_k ) = x_k x_1 x_2
  //! \ldots x_{k-1} \f$.
  inline void cyclicRightShift();

  //! Cyclically reduces the Word
  void cyclicallyReduce();

  //! Returns the cyclically reduced word.
  [[nodiscard]] inline Word cyclicallyReduce() const {
    Word result(*this);
    result.cyclicallyReduce();
    return result;
  }

  //! Returns the cyclically reduced word and the corresponding conjugator.
  inline Word cyclicallyReduce(Word& conjugator) const;

  //! Cyclically reduces the Word and returns the corresponding conjugator.
  inline void cyclicallyReduce(Word& conjugator);

  //! Invert the word.
  Word inverse() const;

  //! Cyclically permute the word and return the result.
  /*! n>0 => left-shift, n<0 => rigth-shift permute. */
  void cyclicallyPermute(int n);
  Word cyclicallyPermute(int n) const;

  //! Get an initial segment of the word of length len.
  void initialSegment(int len);
  Word initialSegment(int len) const;

  //! Get a terminal segment of the word of length len.
  void terminalSegment(int len);
  Word terminalSegment(int len) const;

  // Get a segment of the word defined by ???
  void segment(int from, int to);
  Word segment(int from, int to) const;

  inline int exponentSum(int gen) const;

  int isIn(int gen) const;

  Word power(int t) const;

  //! Insert a sequence of generators [B,E) into a word at a position pos
  // TODO: implement below
  //  template <class ConstIntIterator>
  //  void insert(int pos, ConstIntIterator B, ConstIntIterator E);

  //! Insert a generator g into a word at a position pos
  //  void insert(int pos, int g);

  //  //! Insert a sequence of generators [B,E) into a word before a position it
  //  template <class ConstIntIterator>
  //  void insert(WordIterator it, ConstIntIterator B, ConstIntIterator E);
  //  //! Insert a generator g into a word before a position it
  //  void insert(WordIterator it, int g);
  //
  //  //! Replace a generator at a position it by g
  //  void replace(WordIterator it, const Generator& g);

  //! Replace a generator at a position pos by g
  //  void replace(int pos, const Generator& g);

  //  //! Replace a subword of a word starting at a position it by a word [B,E). The length of the word does not
  //  increase if
  //  //! [B,E) is longer than the terminal segment of the word [it,end()). In that case terminal symbols of [B,E) are
  //  //! ignored.
  //  template <class ConstIntIterator>
  //  void replace(WordIterator it, ConstIntIterator B, ConstIntIterator E);

  //! Returns a word in which generators are replaced by words
  /*! Replace generators with the words (images) contained
    in the std::vector \param images
    */
  Word replaceGenerators(const std::vector<Word>& images) const;


  //! Compute the minimal equivalent word.
  /*! permutableGenerators must be positive.
   */
  //  Word minimalEquivalentForm(const set<int>& permutableGenerators, bool inverses, bool cyclicPermutations) const;


private:
  WordContainerType the_word_;
};
} // namespace acc
#endif // ACC_WORD_H
