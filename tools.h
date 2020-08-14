#pragma once
#include <iostream>
#include <cctype>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

struct ExtWord
{
    std::string word;
    bool isEndLine = false;
};

namespace my_tools
{
    inline std::string strToLower(std::string sample)
    {
        std::transform(sample.begin(), sample.end(), sample.begin(), [](unsigned char c) { return std::tolower(c); });
        return sample;
    }

    inline void splitLineMiss(std::vector<ExtWord> &words, const std::string &line)
    {
        std::istringstream f(line);
        std::string s;

        while (getline(f, s, ' '))
        {
            ExtWord w;
            w.word = s;
            words.push_back(w);
        }

        words[words.size() - 1].isEndLine = true;
    }

    inline void splitLineDict(std::vector<std::string> &words, const std::string &line)
    {
        std::istringstream f(line);
        std::string s;

        while (getline(f, s, ' '))
        {
            words.push_back(s);
        }
    }

    inline void printList(const std::vector<std::string> &words)
    {
        for (auto str : words)
                std::cout << str << " ";
    }

    inline void printListExt(const std::vector<ExtWord> &words)
    {
        char ch;
        for (auto str : words)
        {
            ch = (str.isEndLine ? '\n' : ' ');
            std::cout << str.word << ch;
        }
    }
}
