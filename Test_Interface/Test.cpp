///////////////////////////////////////////////////////////////////////
// Test.cpp - Testing Tokenizer & SemiExp                            //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2015                              //
//  Platform:      HP Pavilion dv6/ Window 7 Service Pack 1          //
// Application: Parser component, CSE687 - Object Oriented Design    //
//Author:       Shishir Bijalwan, Syracuse University                //
//              sbijalwa@syr.edu ,9795876340                         //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is for the testing and provide the automated test cases for the Tokenizer
* and the SemiExp packages. In this we have taken each requirement at a time and given the
* output. In last we have given taken a sample class and given it as input to 
* generate semiexpressions
*
* Build Process:
* --------------
* Required Files: SemiExpression.h, SemiExpression.cpp, Tokenizer.h, Tokenizer.cpp, ITokCollection.h, Test.cpp
*
* Build Command: devenv Project1.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 08 Feb 16
* - first release
*/

#include <iostream>
#include <fstream>
#include "../Tokenizer/Tokenizer.h"
#include "../SemiExp/SemiExp.h"
using namespace Scanner;
class Test {
public:
	void alphanumericTest();
	void punctuatorTest();
	void commentTest();
	void stringTest();
	void semiTokenTerminationTest();
	void setSplChrCheck();
	void forTest();
	void iTokenCollectionCheck();
	void specialCasesTokenizer();
	void specialCasesSemiExp();
	void sampleFileCheck();
	void getTokFunc();

	Toker toker;
	SemiExp semi;
	Test() :semi(&toker){}

};
// Function to check Alphanumeric Tokens
void Test::alphanumericTest() {
	std::cout << "\n =============================================================================\n";
	std::cout << "\n Requirement 1: Used Visual Studio 2015 and its C++ Windows Console Projects. \n \n";
	std::cout << "\n Requirement 2: Used the C++ standard library's streams for all I/O and new and deleted for all heap-based memory management. \n \n";
	std::cout << "\n Requirement 3: Provided C++ packages for Tokenizing, collecting SemiExpressions, and a scanner interface, ITokCollection. \n \n";
	std::cout << "\n =============================================================================\n";

	std::string fileSpec = "../Test_Interface/TestFiles/Requirement_Token_1_Aplhanumeric.txt";
	
	std::ifstream in(fileSpec);
	std::cout << "\n =============================================================================\n";

	std::cout << "\n\n Requirement 4.1: This is to show alphanumeric tokens  : Input file- \n";
	std::cout << "\n this is alphanumeric test123 \n";

	std::cout << "\n =============================OUTPUT==========================================\n";

	toker.attach(&in);

	toker.setShowCommentOnToker(true);
	while (in.good())
	{
		std::string tok = toker.getTok();
		if (tok == "\n")
			tok = "newline";
		std::cout << "\n -- " << tok;
	}
	
	
}
// Function to check Punctuator 
void Test::punctuatorTest() {

	std::string fileSpec = "../Test_Interface/TestFiles/Requirement_Token_2_punctuator.txt";

	std::ifstream in(fileSpec);
	std::cout << "\n =============================================================================\n";

	std::cout << "\n \nRequirement 4.2  : Punctuator output based on default special chars defined : Input file- \n\n";
	std::cout << "==<<::><:$@^.|\n \n ";
	std::cout << "\n =============================OUTPUT==========================================\n";

	toker.attach(&in);

	toker.setShowCommentOnToker(true);
	while (in.good())
	{
		std::string tok = toker.getTok();
		if (tok == "\n")
			tok = "newline";
		std::cout << "\n -- " << tok;
	}
	
	

}
// This function is to show the comments token
void Test::commentTest()
{
	std::string fileSpec = "../Test_Interface/TestFiles/Requirement_Token_3_Comment.txt";

	std::ifstream in(fileSpec);
	std::cout << "\n =============================================================================\n";

	std::cout << "\n\n Requirement 4.4 and 4.5: Comments in C and Cpp (After setShowCommentOnToker(true)) Input file- \n\n";
	std::cout << "//cpp comment \n";
	std::cout << "/* double line c \n";
	std::cout << "comment*/ \n";
	std::cout << "\n =============================OUTPUT==========================================\n";

	toker.attach(&in);

	toker.setShowCommentOnToker(true);
	while (in.good())
	{
		std::string tok = toker.getTok();
		if (tok == "\n")
			tok = "newline";
		std::cout << "\n -- " << tok;
	}

}
//This function is to test the String tokens
void Test::stringTest()
{
	std::string fileSpec = "../Test_Interface/TestFiles/Requirement_Token_4_String.txt";

	std::ifstream in(fileSpec);
	std::cout << "\n =============================================================================\n";

	std::cout << "\n\n Requirement 4.6 : String : Input file- \n \n";
	std::cout << "\"this is string check\" \n";
	std::cout << "'c' \n";
	std::cout << "\n =============================OUTPUT==========================================\n";


	toker.attach(&in);

	toker.setShowCommentOnToker(true);
	while (in.good())
	{
		std::string tok = toker.getTok();
		if (tok == "\n")
			tok = "newline";
		std::cout << "\n -- " << tok;
	}
	

}
// This function is to check termination conditions in a semi expression
void Test::semiTokenTerminationTest()
{
	std::string fileSpec = "../Test_Interface/TestFiles/Requirement_Semi_1_Semi_Expression_End.txt";
	std::fstream in(fileSpec);
	std::cout << "\n =============================================================================\n";
	std::cout << "\n\n Requirement 6,7 : Termination conditions ; { } : and new line in case of # : Input file- \n\n";
	std::cout << "#include <iostream> \n";
	std::cout << "#include \"tokenizer.h\" \n";
	std::cout << "private: \n";
	std::cout << "string name; \n";
	std::cout << "if(bool){}";
	std::cout << "\n =============================OUTPUT==========================================\n";

	toker.attach(&in);

	SemiExp semi(&toker);

	bool showSemiExpr = true;

	while (semi.get())
	{
		std::cout << "\n  -- semiExpression --" << "\n" << semi.show() << "\n";

	}
	
	if (semi.length() > 0)
	{
		std::cout << "\n  -- semiExpression --" << "\n" << semi.show() << "\n";
	}
}
//This function check the default special characters defined in program
void Test::setSplChrCheck()
{
	std::string fileSpec = "../Test_Interface/TestFiles/Requirement_Token_2_punctuator.txt";

	std::ifstream in(fileSpec);
	std::cout << "\n =============================================================================\n";

	std::cout << "\n \n Requirement  4.3 : Punctuator output after using set special char functions : Input file- \n";
	std::cout << "==<<::><:$@^.| " << "\n\n";
	std::cout << "\n =============================OUTPUT==========================================\n";

	toker.attach(&in);

	std::cout << "\n After setting $@ and . as double and single special char \n\n";
	toker.setSpecialCharPairsToker("$@");
	toker.setSpecialSingleCharsToker(".");
	while (in.good())
	{
		std::string tok = toker.getTok();
		if (tok == "\n")
			tok = "newline";
		std::cout << "\n -- " << tok;
	}



}
//It checks different for termination conditions
void Test::forTest()
{
	std::string fileSpec = "../Test_Interface/TestFiles/Requirement_Semi_2_For_Check.txt";
	std::fstream in(fileSpec);
	std::cout << "\n =============================================================================\n";

	std::cout << "\n\n Requirement 8 : For termination conditions conditions-  : Input file- \n\n";
	std::cout << "for(;;){} \n";
	std::cout << "for(int  i =0; i <10;i++) \n";
	std::cout << "return x; \n";
	std::cout << "for (Vector var : Vec){} \n";
	toker.attach(&in);
	std::cout << "\n =============================OUTPUT==========================================\n";


	bool showSemiExpr = true;

	while (semi.get())
	{
		std::cout << "\n  -- semiExpression --" << "\n" << semi.show() << "\n";

	}

	if (semi.length() > 0)
	{
		std::cout << "\n  -- semiExpression --" << "\n" << semi.show() << "\n";
	}
}
//This function shows the output of Itokcollection functions implemented in SemiExp
void Test::iTokenCollectionCheck()
{
	std::string fileSpec = "../Test_Interface/TestFiles/Requirement_Semi_3_Itoken_check.txt";
	std::fstream in(fileSpec);
	std::cout << "\n =============================================================================\n";
	std::cout << "\n\n Requirement 9 : This is Itoken collection functions check-  : Input file- \n\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "THIS is a SEMI expression; \n";
	std::cout << "\n =============================OUTPUT==========================================\n";
	toker.attach(&in);
	std::cout << "\n 9.1) With the help of get() Function we are able to get below semiExpressio\n";
		while (semi.get())
	{
		std::cout << "\n  -- semiExpression --" << "\n" << semi.show() << "\n";

	}
	if (semi.length() > 0)
	{
		std::cout << "\n  -- semiExpression --" << "\n" << semi.show() << "\n";
	}
	std::cout << "\n 9.2) This is show operation with new lines visible show(true) \n";
	std::cout << "\n  -- semiExpression --" << "\n" << semi.show(true) << "\n";
	semi.trimFront();
	std::cout << "\n\n 9.3) Output After Trim operation-- \n\n";
	std::cout << semi.show(true);
	std::cout << "\n\n 9.4) Output After to lower operation-- \n\n";
	semi.toLower();
	std::cout << semi.show(true);
	std::cout << "\n\n 9.5) The location at which \"semi\" is present is - \n\n";
	std::cout << semi.find("semi");
	std::cout << "\n\n 9.6)  Removing \"semi\" by using index -- \n\n";
	semi.remove(3);
	std::cout << semi.show(true);
	std::cout << "\n\n 9.7) Removing \"this\" by using value -- \n\n";
	semi.remove("this");
	std::cout << semi.show(true);
	std::cout << "\n\n 9.8) Adding to the vector using push_back function -- \n\n";
	semi.push_back("pushed");
	std::cout << semi.show(true);
	std::cout << "\n\n 9.9) Clearing the vector and showing its current length to verify clear -- \n\n";
	semi.clear();
	std::cout << semi.length();	
	
}
//This functions deals with some special cases in the Tokenizer
void Test::specialCasesTokenizer()
{

	std::string fileSpec = "../Test_Interface/TestFiles/Requirement_10_Tokenizer.txt";

	std::ifstream in(fileSpec);
	std::cout << "\n =============================================================================\n";

	std::cout << "\n \nRequirement 10.1 : It has been covered in two parts first for tokenizer and then SemiExp : Input file- \n\n";
	std::cout << "\n1. Special Case in string with double  inverted  comma inside it\n";
	std::cout << "\n2. Special Case in Char with sigle inverted  comma inside it\n";
	std::cout << "\n3. Special Case in string double escape character before inverted comma\n";
	std::cout << "\n4. Special Case in string with null return\n";

	std::cout << "\n =============================OUTPUT==========================================\n";

	toker.attach(&in);

	toker.setShowCommentOnToker(true);
	while (in.good())
	{
		std::string tok = toker.getTok();
		if (tok == "\n")
			tok = "newline";
		std::cout << "\n -- " << tok;
	}


}
//This function deals with some special cases in Semi Expression
void Test::specialCasesSemiExp()
{
	std::string fileSpec = "../Test_Interface/TestFiles/Requirement_10_SemiExp.txt";
	std::fstream in(fileSpec);
	std::cout << "\n =============================================================================\n";

	std::cout << "\n\n Requirement 10.2 : It deals with special cases of Semi expression-  : Input file- \n\n";
	std::cout << "\n1. Index based For Loop without curly braces\n";
	std::cout << "\n2. For loop without semicolon with with curly braces\n";
	std::cout << "\n3. For loop without semicolon without curly braces\n";
	std::cout << "\n4. Index for loop without any conditions inside. Each semicolon treated as indiviual token\n";
	std::cout << "\n5. # case when termination is not new line but end of file\n";

	toker.attach(&in);
	std::cout << "\n =============================OUTPUT==========================================\n";


	bool showSemiExpr = true;

	while (semi.get())
	{
		std::cout << "\n  -- semiExpression --" << "\n" << semi.show() << "\n";

	}

	if (semi.length() > 0)
	{
		std::cout << "\n  -- semiExpression --" << "\n" << semi.show() << "\n";
	}
}
// This function is to generate semiexpression of a sample program
void Test::sampleFileCheck()
{
	std::string fileSpec = "../Test_Interface/TestFiles/Sample_program.txt";
	std::fstream in(fileSpec);
	std::cout << "\n =============================================================================\n";

	std::cout << "\n\n This is to generate semiexpression of a sample program- \n\n";
	// the above sample program is from - http://www.cplusplus.com/reference/iterator/iterator/
	std::cout << " \n For showing Requirement 6,7,8 in a complete file are being satisfied \n";
	std::cout << "\n =============================OUTPUT==========================================\n";

	
	while (semi.get())
	{
		std::cout << "\n  -- semiExpression --" << "\n" << semi.show() << "\n";

	}
	if (semi.length() > 0)
	{
		std::cout << "\n  -- semiExpression --" << "\n" << semi.show() << "\n";
	}
}
// To demonstarte the getTok function
void Test::getTokFunc()
{
	std::string fileSpec = "../Test_Interface/TestFiles/Requirement_Token_4_String.txt";

	std::ifstream in(fileSpec);
	std::cout << "\n =============================================================================\n";

	std::cout << "\n\n Requirement 5 : Below we have called getTok() function once and displayed its output i.e one token. Input file - \n \n";
	std::cout << "\"this is string check\" \n";
	std::cout << "'c' \n";
	std::cout << "\n =============================OUTPUT==========================================\n";


	toker.attach(&in);
	
		std::string tok = toker.getTok();
		std::cout << "\n\n" << tok << " \n\n ";

	
	
}
int main() {

	Test test;
	test.alphanumericTest();
    test.punctuatorTest();
	test.setSplChrCheck();
	test.commentTest();
	test.stringTest();
	test.getTokFunc();
	test.semiTokenTerminationTest();
	test.forTest();
	test.iTokenCollectionCheck();
	test.specialCasesTokenizer();
	test.specialCasesSemiExp();
	test.sampleFileCheck();
	
	return 0;
}