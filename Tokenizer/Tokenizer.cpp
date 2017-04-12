/////////////////////////////////////////////////////////////////////
// Tokenizer.cpp - read words from a std::stream                   //
// ver 1.0                                                         //
// Language:    C++, Visual Studio 2015                            //
// Application: Parser component, CSE687 - Object Oriented Design  //
//  Platform:      HP Pavilion dv6/ Window 7 Service Pack 1        //
//Author:       Shishir Bijalwan, Syracuse University              //
//              sbijalwa@syr.edu,9795876340                        //
// Source:      Jim Fawcett, Syracuse University, CST 4-187        //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////

#include "Tokenizer.h"
#include <iostream>
#include <cctype>
#include <string>
#include <vector>

namespace Scanner
{
	class ConsumeState
	{
	public:
		ConsumeState();
		virtual ~ConsumeState();
		void attach(std::istream* pIn) { _pIn = pIn;}
		virtual void eatChars() = 0;
		void consumeChars() {
			_pState->eatChars();
			_pState = nextState();
		}
		bool canRead() { return _pIn->good(); }
		std::string getTok() { return token; }
		bool hasTok() { return token.size() > 0; }
		ConsumeState* nextState();
		void setSpecialCharPairs(std::string ssp);
		void setSpecialSingleChars(std::string ssc);
		void setdisplayCommentOn(bool display);
		

	protected:
		static std::string token;
		static std::istream* _pIn;
		static int prevChar;
		static int currChar;
		static ConsumeState* _pState;
		static ConsumeState* _pEatCppComment;
		static ConsumeState* _pEatCComment;
		static ConsumeState* _pEatWhitespace;
		static ConsumeState* _pEatPunctuator;
		static ConsumeState* _pEatAlphanum;
		static ConsumeState* _pEatNewline;
		static ConsumeState* _pEatString;
		static std::vector<std::string> doublesplchrv;
		static std::vector<std::string> singlesplchrv;
		static bool displayComment;

		
	};
}

using namespace Scanner;
std::vector<std::string> ConsumeState::doublesplchrv{ "<<",">>","::","++","--","==","+=","-=","*=","/=" };
std::vector<std::string> ConsumeState::singlesplchrv{ "<",">",":" ,"]","[","{","}","(",")","+","-","*","\"","'",";" };
std::string ConsumeState::token;
std::istream* ConsumeState::_pIn;
int ConsumeState::prevChar;
int ConsumeState::currChar;
bool ConsumeState::displayComment = false;
ConsumeState* ConsumeState::_pState = nullptr;
ConsumeState* ConsumeState::_pEatCppComment = nullptr;
ConsumeState* ConsumeState::_pEatCComment = nullptr;
ConsumeState* ConsumeState::_pEatWhitespace = nullptr;
ConsumeState* ConsumeState::_pEatPunctuator = nullptr;
ConsumeState* ConsumeState::_pEatAlphanum = nullptr;
ConsumeState* ConsumeState::_pEatString = nullptr;
ConsumeState* ConsumeState::_pEatNewline;

void testLog(const std::string& msg);
// Setter for doublesplchrv vector
void ConsumeState::setSpecialCharPairs(std::string ssp)
{
	doublesplchrv.push_back(ssp);
}
// Setter for singlesplchrv vector
void ConsumeState::setSpecialSingleChars(std::string ssc)
{
	singlesplchrv.push_back(ssc);
}
// Setter for displayComment bool variable
void ConsumeState::setdisplayCommentOn(bool display)
{
	displayComment = display;
}
//To get the nextState based on character read
ConsumeState* ConsumeState::nextState()
{
	if (!(_pIn->good()))
		return _pEatWhitespace;

	int chNext = _pIn->peek();
	if (chNext == EOF)
	{
		_pIn->clear();
	}
	if (std::isspace(currChar) && currChar != '\n')
	{
		testLog("state: eatWhitespace");
		return _pEatWhitespace;
	}
	
	if (currChar == '/' && chNext == '/')
	{
		testLog("state: eatCppComment");
		return _pEatCppComment;
	}
	if (currChar == '/' && chNext == '*')
	{
		testLog("state: eatCComment");
		return _pEatCComment;
	}
	if (currChar == '\n')
	{
		testLog("state: eatNewLine");
		return _pEatNewline;
	}
	if (std::isalnum(currChar) && prevChar != '"')
	{
		testLog("state: eatAlphanum");
		return _pEatAlphanum;
	}
	if (ispunct(currChar) && currChar != '"' && currChar != '\'')
	{

		testLog("state: eatPunctuator");
		return _pEatPunctuator;
	}
	else if ((currChar == '"' || currChar == '\'') && ispunct(currChar)) {
		testLog("state: eatString");
		return _pEatString;
	}
	if (!_pIn->good())
		return _pEatWhitespace;
	throw(std::logic_error("invalid type"));
}
 //Class to eat White spaces
class EatWhitespace : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		do {
			if (!_pIn->good())  // end of stream
				return;
			currChar = _pIn->get();
		} while (std::isspace(currChar) && currChar != '\n');
	}
};

// Adding the comment to token if bool displayComment is true

class EatCppComment : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		do {
			if (displayComment) {
				token += currChar;
			}
			if (!_pIn->good())  // end of stream
				return;
			currChar = _pIn->get();
			if (currChar == '\n') {
			}
		} while (currChar != '\n');
		_pState = nextState();
	}
};
// Adding the comment to token if bool displayComment is true
class EatCComment : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		do {
			if (displayComment) {
				token += currChar;
			}
			if (!_pIn->good())  // end of stream
				return;
			currChar = _pIn->get();
		} while (currChar != '*' || _pIn->peek() != '/');
		if (displayComment) { //based on bool displayComment value comments are added to token
			token += currChar;
		}
		currChar = _pIn->get();
		if (displayComment) {
			token += currChar;
		}
		currChar = _pIn->get();
		_pState = nextState();

	}
};

// Created 3 functions for collecting 3 different types of punctuators Double ,Single special and other.
class EatPunctuator : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		if (!_pIn->good())  // end of stream
			return;
		do {
						
			if (getSplCharPair()) {// If it gets double special char it breaks out
				break;
			}
			else {				
				if (getSplChr())// If it gets single special char it breaks out
				{
					break;
				}
				else {
					
					if (getOtherPunc()) { // call function to collect punctuators other than special chars
						break;
					}
				}
			}

		} while (ispunct(currChar));
		_pState = nextState();
	}

	bool getOtherPunc()
	{
		bool counter3;
		if (currChar == '\\' && _pIn->peek() == 'n') {
			if (token.size() == 0) {  // checks if it is a new token otherwise break to form new token
				token += currChar;
				currChar = _pIn->get();
				token += currChar;
				currChar = _pIn->get();
				counter3= true;
			}
			else {
				counter3= true;
			}

		}
		else {
			token += currChar;

			currChar = _pIn->get();
			counter3= false;
		}
		return counter3;
	}


	int getSplCharPair() {
		bool counter=false;
		for (std::vector<std::string>::size_type i = 0; i != doublesplchrv.size(); i++) {
			char firstChar = doublesplchrv[i][0];
			char secondChar = doublesplchrv[i][1];
			if (currChar == firstChar && _pIn->peek() == secondChar) { //compares current and next char for special character
				if (token.size() == 0) { // checks if it is a new token otherwise break to form new token
					token += currChar;
					currChar = _pIn->get();
					token += currChar;
					currChar = _pIn->get();
					counter = true;
					break;
				}
				else {
					counter = true;
					break;
				}
			}
		}
		return counter;


	}


	int getSplChr()
	{
		bool counter2 = false;
		for (std::vector<std::string>::size_type i = 0; i != singlesplchrv.size(); i++) {
			char firstChar = singlesplchrv[i][0];
			if (currChar == firstChar) { // checks fro spl single char
				if (token.size() == 0) {  // checks if it is a new token otherwise break to form new token
					token += currChar;
					counter2=true;
					currChar = _pIn->get();
					break;
				}
				else {
					counter2 = true;;
					break;
				}
			}
		}
		return counter2;
	}
};
// Class to eat Alphanumeric character
class EatAlphanum : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		do {
			int temp = _pIn->peek();


			token += currChar;

			if (!_pIn->good())  // end of stream
				return;
			currChar = _pIn->get();
			temp = _pIn->peek();

		} while (isalnum(currChar));
		_pState = nextState();
	}
};
// Class to eat new line
class EatNewline : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		token += currChar;
		if (!_pIn->good())  // end of stream
			return;
		currChar = _pIn->get();
	}
};
// Function to extract quoted strings
class EatString : public ConsumeState
{
public:
	virtual void eatChars()
	{
		if (!_pIn->good())  // end of stream
			return;

		int temp = _pIn->peek();
		int temp2 = currChar;
		int enterChar = currChar;
		token.clear();
		currChar = _pIn->get();
		if ((temp == '"' && temp2 == '"') || (temp == '\'' && temp2 == '\'')) {
			currChar = _pIn->get();
			token += temp;
			token += temp;
			_pState = nextState();
		}
		else {
			//added here
			token += temp2;
			do {
				

				if (currChar == '\\' && _pIn->peek() == '\\') { // checking for double escape char
					currChar = _pIn->get();
				}else{
				if (currChar == '\\' && (_pIn->peek() == '"' || _pIn->peek() == '\'')) // checking for escape char and a closing inverted comma
				{
					token += currChar;
					currChar = _pIn->get();
				}
				}

				token += currChar;
				currChar = _pIn->get();

				} while (currChar != enterChar);
				token += currChar;
			currChar = _pIn->get();
			_pState = nextState();
		}
	}
};

ConsumeState::ConsumeState()
{
	static bool first = true;
	if (first)
	{
		first = false;
		_pEatAlphanum = new EatAlphanum();
		_pEatCComment = new EatCComment();
		_pEatCppComment = new EatCppComment();
		_pEatPunctuator = new EatPunctuator();
		_pEatWhitespace = new EatWhitespace();
		_pEatNewline = new EatNewline();
		_pEatString = new EatString();
		_pState = _pEatWhitespace;
	}
}

ConsumeState::~ConsumeState()
{
	static bool first = true;
	if (first)
	{
		first = false;
		delete _pEatAlphanum;
		delete _pEatCComment;
		delete _pEatCppComment;
		delete _pEatPunctuator;
		delete _pEatWhitespace;
		delete _pEatNewline;
	}
}

Toker::Toker() : pConsumer(new EatWhitespace()) {}

Toker::~Toker() { delete pConsumer; }

bool Toker::attach(std::istream* pIn)
{
	if (pIn != nullptr && pIn->good())
	{
		pConsumer->attach(pIn);
		return true;
	}
	
	return false;
}
// Wrapper for setting special double char values
void Toker::setSpecialCharPairsToker(std::string ssp) {
	pConsumer->setSpecialCharPairs(ssp);

}
// Wrapper for setting special single char values
void Toker::setSpecialSingleCharsToker(std::string ssc) {

	pConsumer->setSpecialSingleChars(ssc);
}
// Wrapper for setting comment variable
void Toker::setShowCommentOnToker(bool show) {
	pConsumer->setdisplayCommentOn(show);
}

std::string Toker::getTok()
{

	while (true)
	{
		if (!pConsumer->canRead())
			return "";
		pConsumer->consumeChars();
		if (pConsumer->hasTok())
			break;
	}
	return pConsumer->getTok();
}

bool Toker::canRead() { return pConsumer->canRead(); }

void testLog(const std::string& msg)
{
#ifdef TEST_LOG
	std::cout << "\n  " << msg;
#endif
}

//----< test stub >--------------------------------------------------

#ifdef TEST_TOKENIZER

#include <fstream>

int main()
{


	std::string fileSpec = "../Tokenizer/Tokenizer.cpp";
	//std::string fileSpec = "../Tokenizer/Tokenizer.h";
	//std::string fileSpec = "../Tokenizer/Test.txt";
	//std::string fileSpec = "../Tokenizer/check_file.txt";

	
	std::ifstream in(fileSpec);
	if (!in.good())
	{
		std::cout << "\n  can't open " << fileSpec << "\n\n";
		return 1;
	}

	Toker toker;
	
	toker.attach(&in);
	
	while (in.good())
	{
		std::string tok = toker.getTok();
		if (tok == "\n")
			tok = "newline";
		std::cout << "\n -- " << tok;
	}
	std::cout << "\n\n";
	
	return 0;
}
#endif