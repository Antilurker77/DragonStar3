// ================================================================
//
// wordWrap.cpp
//
// ================================================================

#include "wordWrap.hpp"

#include <sstream>

std::vector<std::string> WordWrap::WrapString(std::string text, size_t charsPerLine) {
	std::vector<std::string> result;
	
	std::istringstream iss(text);
	std::vector<std::string> words;
	std::string token;
	std::string colorWord;

	while (std::getline(iss, token, ' ')) {
		words.push_back(token);
	}

	size_t charCount = 0;
	bool prevWasRichTextTag = false;
	std::string currentLine;

	for (size_t i = 0; i < words.size(); i++) {
		if (words[i][0] == '#') {
			colorWord = words[i];
			if (i < words.size() - 1) {
				std::string nextWord = words[i + 1];
				if (nextWord.find('#') != std::string::npos) {
					nextWord = nextWord.substr(0, nextWord.find_first_of('#'));
				}
				if (charCount + nextWord.length() > charsPerLine) {
					result.push_back(currentLine);
					currentLine = words[i] + " ";
					charCount = 0;
				}
				else {
					currentLine += " " + words[i];
				}
			}
			else {
				currentLine += " " + words[i];
			}
			prevWasRichTextTag = true;
		}
		else if (words[i].find('#') != std::string::npos) {
			size_t position = words[i].find_first_of('#');
			std::string left = words[i].substr(0, position);
			std::string right = words[i].substr(position);
			colorWord = right;

			if (charCount + left.length() > charsPerLine) {
				result.push_back(currentLine);
				currentLine = words[i] + " ";
				charCount = left.length();
			}
			else {
				currentLine += " " + words[i];
				charCount += left.length() + 1;
			}
		}
		else {
			size_t wordLength = words[i].length();
			if (charCount == 0) {
				currentLine += words[i];
				charCount = wordLength;
			}
			else if (charCount + wordLength > charsPerLine) {
				//if (prevWasRichTextTag) {
				//	currentLine += " ";
				//}
				result.push_back(currentLine);
				if (!colorWord.empty()) {
					currentLine = colorWord + " " + words[i];
				}
				else {
					currentLine = words[i];
				}
				charCount = wordLength;
			}
			else {
				currentLine += " " + words[i];
				charCount += wordLength + 1;
			}
			prevWasRichTextTag = false;
		}
	}
	// last line
	result.push_back(currentLine);


	return result;
}