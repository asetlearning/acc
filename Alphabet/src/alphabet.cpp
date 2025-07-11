
// Contents: Implementation of Alphabet related  classes
//
// Principal Author:   Alex Myasnikov
// Copyright (C) 2005, 2025
//
// Status: in progress
//
// Revision History:
//

#include "alphabet.h"

#include <iostream>
#include <string>
#include <vector>
// #include "Parser.h"
#include <stdlib.h>
#include <sstream>

#include "logger.h"
#include "word.h"
// #include "errormsgs.h"
#include <iterator>

namespace acc {

void Alphabet::printWord(ostream& out, const Word& w) const {
  int p_base = 0;
  int deg = 0;

  if (w.length() == 0) {
    out << "1";
    return;
  }

  int pb;
  for (auto e_it = w.begin(); e_it != w.end(); ++e_it) {
    if (*e_it == p_base) {
      ++deg;
    } else {
      pb = p_base;
      if (pb != 0) {
        out << getLetter(abs(p_base));
        if (deg != 1 || pb < 0)
          out << "^" << (pb < 0 ? -deg : deg);
        out << " ";
      }
      pb = p_base = *e_it;
      deg = 1;
    }
  }

  out << getLetter(abs(p_base));
  if (deg != 1 || pb < 0)
    out << "^" << (pb < 0 ? -deg : deg);
}

// Word Alphabet::readWord( istream& in )const {
//   Parser p( cin,(const Alphabet*)this );
//   p.parse();
//
//   return Word( p.getWord() );
// }

std::string Alphabet::toString(const Word& w) const {
  stringstream ss;
  printWord(ss, w);
  return ss.str();
}

void Alphabet::printVector(ostream& out, const vector<Word>& v) const {
  out << "{ ";
  for (const auto& w : v) {
    printWord(out, w);
    out << ", ";
  }
  out << " }" << flush;
}


// vector<Word> Alphabet::readVector( istream& in )const
//{
//   list<Word> l;
//
//   // read the first symbol which supposed to be '}'
//   char ch = ' ';
//   while ( ch == ' ' || ch=='\t' || ch == '\n' || ch == '\r' ){
//     in >> ch;
//   }
//
//   if (ch!='{') {
//     msgs::error("Alphabet::readVector(): syntax error.");
//   }
//   while (1){
//     Parser p(in,this);
//     p.parse();
//     Word w(p.getWord());
//     l.push_back(w);
//     if (p.getWordTerminalSymbol() == '}') break;
//     if (p.getWordTerminalSymbol() != ',' && p.getWordTerminalSymbol() != ';'){
//       msgs::error("Alphabet::readVector(): syntax error.");
//     }
//   }
//
//   vector<Word> v(l.size());
//   copy(l.begin(),l.end(),v.begin());
//   return v;
// }

FiniteAlphabet::FiniteAlphabet(int r)
  : letters_(r) {
  for (int i = 0; i < r; i++) {
    stringstream ss;
    ss << "x" << i + 1 << flush;
    letters_[i] = ss.str();
  }
}

size_t FiniteAlphabet::getNum(const string& letter) const {
  for (size_t i = 0; i < letters_.size(); i++)
    if (letters_[i] == letter)
      return i + 1;

  return 0;
}

string FiniteAlphabet::getLetter(size_t index) const {
  if (index <= 0 || index > letters_.size()) {
    logger::fatal(std::format("Index {} is out of bounds", index));
  }
  return letters_[index - 1];
}

const vector<string>& FiniteAlphabet::getLetters() const {
  return letters_;
}


// int InfiniteAlphabet::getNum( const string& letter ) const {
//   // match the letter prefix first
//   if ( thePrefix.size() >= letter.size() ) return 0;
//   for (int i=0;i<thePrefix.size();i++)
//     if ( thePrefix[i] != letter[i] ) return 0;
//
//   // extract the index
//   int index = atoi((letter.substr(thePrefix.size(),letter.size()-thePrefix.size())).c_str());
//
//   return index;
// }
//
//
// string InfiniteAlphabet::getLetter( int index ) const {
//   if (abs(index) == 0 ){
//     cout << "Index " << index << " is out of bounds" << endl;
//     exit(0);
//   }
//   stringstream ss;
//   ss << thePrefix << index  << flush;
//   return ss.str();
// }
//
// InfiniteAlphabet InfiniteAlphabet::defaultAlphabet = InfiniteAlphabet();
//
//
} // namespace acc