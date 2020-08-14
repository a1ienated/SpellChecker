#include "SpellChecker.h"
#include <iostream>
#include <fstream>

SpellChecker::SpellChecker(const std::string &_inputName, const std::string &_outputName) 
	: inputName(_inputName), outputName(_outputName) {}

void SpellChecker::runCheck()
{
	if (parseData())
	{
		printInputData();
		processingData();
		printOutputData();
		writeToFile();
	}
}

bool SpellChecker::fullMatch(const std::string &checkedWord, const std::string &sample)
{
	std::string str1 = my_tools::strToLower(checkedWord);
	std::string str2 = my_tools::strToLower(sample);

	if (str1 == str2)
		return true;
	else
		return false;
}

std::string SpellChecker::swapped(const std::string &checkedWord, const std::string &sample)
{
	char ch;
	std::string editStr;
	std::string resultStr;

	for (size_t i = 0; i < checkedWord.size() - 1; i++)
	{
		editStr = checkedWord;

		ch = editStr[i];
		editStr[i] = editStr[i + 1];
		editStr[i + 1] = ch;

		if (fullMatch(editStr, sample))
		{
			resultStr = sample;
			break;
		}
	}

	if (resultStr.empty())
		return resultStr;
	else
		return resultStr;
}

std::string SpellChecker::remove(const std::string &checkedWord, const std::string &sample)
{
	std::string editStr;
	std::string resultStr;

	for (size_t i = 1; i < checkedWord.size(); i++)
	{
		editStr = checkedWord;
		editStr.erase(i, 1);

		if (fullMatch(editStr, sample))
		{
			resultStr = sample;
			break;
		}
	}

	if (resultStr.empty())
		return resultStr;
	else
		return resultStr;
}

std::string SpellChecker::insert(const std::string &checkedWord, const std::string &sample)
{
	std::string editStr = checkedWord;
	std::string resultStr;

	for (size_t i = 0; i < checkedWord.size() + 1; i++)
	{
		for (char j = 'a'; j <= 'z'; j++)
		{
			editStr.insert(i, 1, j);

			if (fullMatch(editStr, sample))
			{
				resultStr = sample;
				break;
			}

			editStr.erase(i, 1);
		}

		if (!resultStr.empty())
			break;
	}

	if (resultStr.empty())
		return resultStr;
	else
		return resultStr;
}

std::string SpellChecker::replace(const std::string &checkedWord, const std::string &sample)
{
	std::string editStr;
	std::string resultStr;

	for (size_t i = 0; i < checkedWord.size(); i++)
	{
		for (char j = 'a'; j <= 'z'; j++)
		{
			editStr = checkedWord;
			editStr.erase(i, 1);
			editStr.insert(i, 1, j);

			if (fullMatch(editStr, sample))
			{
				resultStr = sample;
				break;
			}
		}
	}

	if (resultStr.empty())
		return resultStr;
	else
		return resultStr;
}

bool SpellChecker::parseData()
{
	std::ifstream fIn;
	fIn.open(inputName);
	if (!fIn.is_open())
	{
		std::cout << "Input data file not found\n";
		return false;
	}

	bool readDic = true;
	std::string line;
	while (!fIn.eof())
	{
		getline(fIn, line);

		if (line == "===")
		{
			readDic = false;
			continue;
		}

		if (readDic)
			my_tools::splitLineDict(dictionary, line);
		else
			my_tools::splitLineMiss(misspelledWords, line);
	}
	
	fIn.close();
	return true;
}

void SpellChecker::processingData()
{	
	for (unsigned indx = 0; indx < misspelledWords.size(); indx++)
	{
		unsigned fixType = 0;
		unsigned numOfMatches = 0;
		std::string strVoc, strChecked;
		ExtWord midStr, strMiss;
		midStr = strMiss = misspelledWords.at(indx);
		midStr.word.clear();

		for (unsigned vocIndx = 0; vocIndx < dictionary.size(); vocIndx++)
		{
			strVoc = dictionary.at(vocIndx);

			if (fullMatch(strMiss.word, strVoc))
			{
				midStr.word = strMiss.word + " ";
				numOfMatches = 1;
				fixType |= FULL_MATCH;
				break;
			}
			else
			{
				strChecked = swapped(strMiss.word, strVoc);
				if (!strChecked.empty())
				{
					midStr.word += strChecked + " ";
					numOfMatches++;
					fixType |= SWAP_CH;
				}

				strChecked = remove(strMiss.word, strVoc);
				if (!strChecked.empty())
				{
					midStr.word += strChecked + " ";
					numOfMatches++;
					fixType |= DELETE_CH;
				}

				strChecked = insert(strMiss.word, strVoc);
				if (!strChecked.empty())
				{
					midStr.word += strChecked + " ";
					numOfMatches++;
					fixType |= INSERT_CH;
				}

				strChecked = replace(strMiss.word, strVoc);
				if (!strChecked.empty())
				{
					midStr.word += strChecked + " ";
					numOfMatches++;
					fixType |= REPLACE_CH;
				}
			}
		}

		if (fixType == NO_MATCH)
		{
			strMiss.word = "{" + strMiss.word + "?}";
			fixWords.push_back(strMiss);
		}
		
		if (fixType == FULL_MATCH)
		{
			midStr.word.pop_back();
			fixWords.push_back(midStr);
		}
		
		if ((fixType != FULL_MATCH) && (numOfMatches == 1))
		{
			midStr.word.pop_back();
			fixWords.push_back(midStr);
		}
		
		if ((fixType != FULL_MATCH) && (numOfMatches > 1))
		{
			midStr.word.pop_back();
			midStr.word = "{" + midStr.word + "?}";
			fixWords.push_back(midStr);
		}
	}
}

void SpellChecker::printInputData()
{
	std::cout << "\nInput:\n";
	my_tools::printList(dictionary);
	std::cout << "\n===\n";
	my_tools::printListExt(misspelledWords);
	std::cout << "===\n";
}

void SpellChecker::printOutputData()
{
	std::cout << "\nOutput:\n";
	my_tools::printListExt(fixWords);
}

void SpellChecker::writeToFile()
{
	std::ofstream fOut;
	fOut.open(outputName, std::ifstream::trunc);
	if (!fOut.good())
	{
		std::cout << "Can't open output file.";
		return;
	}

	for (auto str : fixWords)
		fOut << str.word << (str.isEndLine ? "\n" : " ");

	fOut.close();
}
