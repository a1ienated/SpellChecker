#pragma once
#include "tools.h"

class SpellChecker
{
public:
	SpellChecker(const std::string &inputName, const std::string &outputName);
	void runCheck();

private:
	bool fullMatch(const std::string &checkedWord, const std::string &sample);
	std::string swapped(const std::string &checkedWord, const std::string &sample);
	std::string remove(const std::string &checkedWord, const std::string &sample);
	std::string insert(const std::string &checkedWord, const std::string &sample);
	std::string replace(const std::string &checkedWord, const std::string &sample);

	bool parseData();
	void processingData();
	void printInputData();
	void printOutputData();
	void writeToFile();

	static const unsigned NO_MATCH		= 0x0;
	static const unsigned FULL_MATCH	= 0x1;
	static const unsigned SWAP_CH		= 0x2;
	static const unsigned DELETE_CH		= 0x4;
	static const unsigned INSERT_CH		= 0x8;
	static const unsigned REPLACE_CH	= 0x10;

	std::string inputName;
	std::string outputName;
	std::vector <std::string> dictionary;
	std::vector <ExtWord> misspelledWords;
	std::vector <ExtWord> fixWords;
};
