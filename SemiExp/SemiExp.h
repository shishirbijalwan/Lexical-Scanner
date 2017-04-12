#ifndef SEMIEXPRESSION_H
#define SEMIEXPRESSION_H
///////////////////////////////////////////////////////////////////////
// SemiExpression.h - collect tokens for analysis                    //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CSE687 - Object Oriented Design    //
//  Platform:      HP Pavilion dv6/ Window 7 Service Pack 1          //
//Author:       Shishir Bijalwan, Syracuse University                //
//              sbijalwa@syr.edu,9795876340                          //
// Source:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides a public SemiExp class that collects and makes
* available sequences of tokens.  SemiExp uses the services of a Toker
* class to acquire tokens.  Each call to SemiExp::get() returns a 
* sequence of tokens that ends in {.  This will be extended to use the
* full set of terminators: {, }, ;, and '\n' if the line begins with #.
*
*
* Build Process:
* --------------
* Required Files: 
*   SemiExpression.h, SemiExpression.cpp, Tokenizer.h, Tokenizer.cpp, ITokCollection.h
* 
* Build Command: devenv Project1.sln /rebuild debug
*
* Maintenance History:
 * --------------------
 * ver 1.0 : 08 Feb 16
 * - first release
 *
 */

#include <vector>
#include "../Tokenizer/Tokenizer.h"
#include "itokcollection.h"

namespace Scanner
{
  using Token = std::string;

  class SemiExp :public ITokCollection
  {
  public:
    SemiExp(Toker* pToker = nullptr);
    SemiExp(const SemiExp&) = delete;
    SemiExp& operator=(const SemiExp&) = delete;
    bool get(bool clear = true);
    Token operator[](size_t n);
    size_t length();
    std::string show(bool showNewLines = false);
	void push_back(const std::string& tok);
	size_t find(const std::string& tok);
	bool merge(const std::string& firstTok, const std::string& secondTok);
	bool remove(const std::string& tok);
	bool remove(size_t i);
	void toLower();
	void trimFront();
	void clear();
	std::string& operator[](int n);

  protected:
	  void helperFor();
	  void helperhash();

  private:
    std::vector<Token> _tokens;
    Toker* _pToker;
	
  };
}
#endif

