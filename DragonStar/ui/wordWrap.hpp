// ================================================================
//
// wordWrap.hpp
// 
// Function that seperates strings based on length.
//
// ================================================================

#pragma once

#include <string>
#include <vector>

namespace WordWrap {

	// Each vector element is one line of text.
	std::vector<std::string> WrapString(std::string text, size_t charsPerLine);
}
