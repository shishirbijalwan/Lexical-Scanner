#ifndef TOKENIZER_H
#define TOKENIZER_H
///////////////////////////////////////////////////////////////////////
// Tokenizer.h - read words from a std::stream                       //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CSE687 - Object Oriented Design    //
//  Platform:      HP Pavilion dv6/ Window 7 Service Pack 1          //
//Author:       Shishir Bijalwan, Syracuse University                //
//              sbijalwa@syr.edu, 9795876340                         //
// Source:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package provides a public Toker class and private ConsumeState class.
 * Toker reads words from a std::stream, throws away whitespace and comments
 * and returns words from the stream in the order encountered.  Quoted
 * strings and certain punctuators and newlines are returned as single tokens.
 *
 *
 * Build Process:
 * --------------
 * Required Files: Tokenizer.h, Tokenizer.cpp
 * Build Command: devenv Project1.sln /rebuild debug
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 08 Feb 16
 * - first release
 *
 */
#include <iosfwd>
#include <string>

namespace Scanner
{
  class ConsumeState;

  class Toker
  {
  public:
    Toker();
    Toker(const Toker&) = delete;
    ~Toker();
    Toker& operator=(const Toker&) = delete;
    bool attach(std::istream* pIn);
    std::string getTok();
    bool canRead();
	void setSpecialCharPairsToker(std::string ssp);
	void setSpecialSingleCharsToker(std::string ssc);
	void setShowCommentOnToker(bool show);
  private:
    ConsumeState* pConsumer;

  };
}
#endif
