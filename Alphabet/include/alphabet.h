
// Contents: Definitions of Alphabet related  classes
//
// Principal Author:   Alex Myasnikov
// Copyright (C) 2005, 2025
//
// Status: in progress
//
// Revision History:
//

#ifndef ACC_ALPHABET_H
#define ACC_ALPHABET_H

#include <iostream>
#include <vector>
#include <string>
//#include "word.h"
//#include "Parser.h"
//#include <stdlib.h>
#include <sstream>

using namespace std;

namespace acc {
class Word;

//! Implements an abstract interface for all alphabet realizations
class Alphabet {
public:
  //! Interface for conversion from the letter name to an integer
  virtual size_t getNum(const string& letter) const = 0;

  //! Interface for conversion from an integer index into the corresponding  letter name
  virtual string getLetter(size_t index) const = 0;

  //! Output  a word in the alphabet letters
  void printWord(ostream& out, const Word& w) const;

  std::string toString(const Word& w) const;

  //! Read a word from a stream in the alphabet letters
  // TODO: implement
  //  Word readWord( istream& in )const;

  //! Output  a vector of words in the alphabet letters
  void printVector(ostream& out, const vector<Word>& v) const;

  //! Read a vector of words from a stream in the alphabet letters
  // TODO: implement
  //  vector<Word> readVector( istream& in )const;
};


//! Implements a finite size alphabet
/*!
  This is an implementation of a finite alphabet. Letter names are given
  as a parameter in the constructor
*/
class FiniteAlphabet : public Alphabet {
public:
  FiniteAlphabet() = default;

  //! Constructor
  /*!
    \param r - the number of letters in the alphabet.
    Default names of letters are \f$x_1, \ldots, x_r$\f
  */
  explicit FiniteAlphabet(int r);

  //! Constructor
  /*!
    \param letters - the list of the letter names. The size of the alphabet is
    defined by the number of letters. If cannot match the letter, 0 is returned.
  */
  explicit FiniteAlphabet(vector<string> letters)
    : letters_(std::move(letters)) {}

  //! Return the size of the alphabet
  inline size_t size() const {
    return letters_.size();
  }

  //! Implements the conversion from a letter name into its corresponding index
  /*!
    This is a temporary implemintation. Needs to be more efficient.
    \param letter - the name of a letter
    \return letters index in the alphabet
  */
  size_t getNum(const string& letter) const;

  //! Returns the name of the letter with a given index
  /*!
    \param index  - the index of a letter from the alphabet
    \return the name of the letter with index \c index
  */
  string getLetter(size_t index) const;

  //! Returns the names of letters of the alphabet
  /*!
    \return the names of letters of the alphabet
  */
  const vector<string>& getLetters() const;

  //! Output the alphabet into a stream
  friend ostream& operator<<(ostream& out, const FiniteAlphabet& a) {
    if (a.letters_.size() == 0)
      out << "{ }" << flush;
    else {
      out << "{ ";
      for (int i = 0; i < a.letters_.size() - 1; i++)
        out << a.letters_[i] << ", ";
      out << a.letters_[a.letters_.size() - 1] << " }" << flush;
    }
    return out;
  }

  //! Read an alphabet from a string
  // TODO: implement
  //  friend istream& operator >> ( istream& in,  FiniteAlphabet& a ){
  //    AParser ap( in );
  //    ap.parse();
  //
  //    a = ap.getAlphabet();
  //    return in;
  //  }

private:
  //  friend class AlphabetFlexLexer;

  void addGenerator(const string& g) {
    letters_.push_back(g);
  }

  //! List of letter names
  vector<string> letters_;
};


////! Implements an infinite size alphabet
// class InfiniteAlphabet : public Alphabet
//{
//  public:
//   //! Constructor
//   /*!
//     \param pref - prefix to be used for letter names. By defalut
//     the letter 'x' is used. In general letter names defined
//     by appending the corresponding index to the prefix, i.e. <prefix><index>.
//   */
//   InfiniteAlphabet(string pref  = string("x")): thePrefix( pref ) { }
//
//   //! Implements the conversion from a letter name into its corresponding index
//   /*!
//     \param letter - the name of a letter
//     \return letter index in the alphabet. If cannot match the letter, 0 is returned.
//   */
//   int getNum( const string& letter ) const;
//
//
//   //! Returns the name of the letter with a given index
//   /*!
//     \param index  - the index of a letter from the alphabet
//     \return the name of the letter with index \c index
//   */
//   string getLetter( int index ) const;
//
//   //! Static instance of the default alphabet x_1, x_2, ...
//   static InfiniteAlphabet defaultAlphabet;
//
//   //! Output the alphabet into a stream
//   friend ostream& operator << ( ostream& out, const InfiniteAlphabet& a ){
//     out << "{ ";
//     for ( int i=1;i<4;i++)
//       out << a.thePrefix << i <<  ", ";
//     out << "... }" << flush;
//
//     return out;
//   }
//
//  private:
//   string thePrefix; //! Prefix of letters
// };
//
//
// void readFPPresentation( istream& in );
}

#endif


