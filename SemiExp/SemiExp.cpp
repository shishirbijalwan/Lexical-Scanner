///////////////////////////////////////////////////////////////////////
// SemiExpression.cpp - collect tokens for analysis                  //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CSE687 - Object Oriented Design    //
//  Platform:      HP Pavilion dv6/ Window 7 Service Pack 1          //
//Author:       Shishir Bijalwan, Syracuse University                //
//              sbijalwa@syr.edu, 9795876340                         //
// Source:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>
#include <algorithm>
#include "SemiExp.h"
#include "../Tokenizer/Tokenizer.h"
#include "itokcollection.h"
using namespace Scanner;

SemiExp::SemiExp(Toker* pToker) : _pToker(pToker) {}
// This function is to get the tokens from tokenizer
bool SemiExp::get(bool clear)
{
  if (_pToker == nullptr)
    throw(std::logic_error("no Toker reference"));
  if (clear) {
	  _tokens.clear();
  }
  std::string prevToken;
  while (true)
  {
    std::string token = _pToker->getTok();
    if (token == "")
      break;
    _tokens.push_back(token);
    
	if (token == "{") {
		return true;
	}
	if (token == "}") {
		return true;
	}
	if (token == ";") {
		return true;
	}
	
	if (token==":" && (prevToken == "public" || prevToken == "protected" || prevToken == "private")) {
		return true;
	}
	if (token == "for") { // in case of for we call the helper function
		helperFor();
		return true;
	}
	if (token == "#") { // in case of # we call helper function
		helperhash();
		return true;
	}
	prevToken = token;
  }
  return false;
}

// Function for collecting tookens for "For" condition
void SemiExp::helperFor() {
	int counter1 = 0;
	int counter2 = 0;
	std::string token;
	do {
		token = _pToker->getTok();
		if (token == ";") { // to keep the count of semicolon.It should be 2 for a statement
			counter1++;
		}
		if (token == ":") { // to keep the count of colon.
			counter2++;
		}
		_tokens.push_back(token);
	} while (!(token == "{" && counter1 == 2) && !(token == "{" && counter2 == 1) && !(token == ";" && counter1 == 3) && !(token == ";" && counter2 == 1));
	// based on different combination of semicolon,curly bracket and colon we have set above conditions for "For"
}
// Helper to collect tokens for SemiExp starting with #
void SemiExp::helperhash() {

	std::string token;
	token = _pToker->getTok();
		_tokens.push_back(token);
		token = _pToker->getTok();
		
			_tokens.push_back(token);
			do {
				token = _pToker->getTok();
				_tokens.push_back(token);
				
				if (!_pToker->canRead()) { // in case of end of the file we won't get newline
					break;
				}
				
			} while (token != "\n" );
		


}
//Gives the value of the token in SemiExp
Token SemiExp::operator[](size_t n)
{
  if (n < 0 || n >= _tokens.size())
    throw(std::invalid_argument("index out of range"));
  return _tokens[n];
}
//Gives the refernce of the token in SemiExp
std::string& SemiExp::operator[](int n) {

	int toke_size = _tokens.size();
	if (n < 0 || n >= toke_size)
		throw(std::invalid_argument("index out of range"));
	return _tokens[n];
}
// Gives Length
size_t SemiExp::length()
{
  return _tokens.size();
}
// Dislaying the SemiExp depending on bool argument
std::string SemiExp::show(bool showNewLines)
{
	std::string semiExpString;
	for (auto token : _tokens)
		if (showNewLines) {
			semiExpString += token;
			semiExpString += " ";

		}else{
		if (token != "\n"   ) {
			semiExpString += token;
			semiExpString += " ";
		}
}
	return semiExpString;
}

 // Inserting value in the Vector SemiExp
void SemiExp::push_back(const std::string& tok) {

	_tokens.push_back(tok);
}
// Finds the value in vector SemiExp and returns its poistion
size_t SemiExp::find(const std::string& tok) {
	
	size_t maxvalue = SIZE_MAX; // In case we dont find the string in vector we return max value of size_t. 

		for (unsigned int i = 0; i < _tokens.size(); i++)
	{
		if (_tokens[i] == tok) {
			maxvalue = i;
			break;
		}

	}
		
		return maxvalue;
}
// As instructed by Prof. returned true for it
bool SemiExp::merge(const std::string& firstTok, const std::string& secondTok) {

	return true;
}
// Removes based on value
bool SemiExp::remove(const std::string& tok) {

	size_t i = find(tok); //** Reusing the find function defined above
	if (i != SIZE_MAX) {
		_tokens.erase(_tokens.begin() + i);
		return true;
	}else{
		return false;
	}
	
}
//Removes based on index
bool SemiExp::remove(size_t i) {
	if (i < _tokens.size()) { // Haven't done <0 check as size_t can't be negative
		_tokens.erase(_tokens.begin() + i);
		return true;
	}
	else {

		return false;
}
}
// Makes SemiExp to lower case
void SemiExp::toLower() {
	for (unsigned int i = 0; i < _tokens.size(); i++)
	{
		std::string temp= _tokens[i];
		std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // #include <algorithm>
		_tokens[i] = temp;
		
	}
}
// Trims the new line and spaces from front
void SemiExp::trimFront() {
	unsigned int counter=0;
	for (unsigned int i = 0; i < _tokens.size(); i++)
	{    
			if (_tokens[i] == "\n" || _tokens[i] == " ") {
			counter++;
			}
			else { break; }

	}
	if (counter != 0) {
		if (counter == 1) {
			_tokens.erase(_tokens.begin());
		}else{

		_tokens.erase(_tokens.begin(), _tokens.begin() + counter);
		}
	}
}

void SemiExp::clear() {
	_tokens.clear();
}





#ifdef TEST_SemiExp
int main()
{
  Toker toker;
 // std::string fileSpec = "../Tokenizer/Tokenizer.cpp";
 // std::string fileSpec = "../../Updated_project1/Tokenizer/Sunday/Toker/1.2_Toker_withstring_with_invertedcomma.txt";
 std::string fileSpec = "../../Updated_project1/Tokenizer/check_file1.txt";
  std::fstream in(fileSpec);
  if (!in.good())
  {
    std::cout << "\n  can't open file " << fileSpec << "\n\n";
    return 1;
  }
  toker.attach(&in);

  SemiExp semi(&toker);

  bool showSemiExpr = true;

  while(semi.get())
  {
	  std::cout << "\n  -- semiExpression --" << "\n" << semi.show()  << "\n";
	
  }
  /*
     May have collected tokens, but reached end of stream
     before finding SemiExp terminator.
   */
  if (semi.length() > 0)
  {
	  std::cout << "\n  -- semiExpression --" << "\n" << semi.show() << "\n";
  }

 


 
  return 0;
}
#endif