#include "SpellChecker.h"

int main(int argc, char** argv)
{
	std::string inputName = "input.txt";
	std::string outputName = "output.txt";

	SpellChecker spellCheck(inputName, outputName);
	spellCheck.runCheck();

	return 0;
}