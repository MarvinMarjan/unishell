#pragma once

#include "option.h"
#include "../../color/parser/color_parser.h"
#include "../../instream/scanner/instream_scanner.h"

#include <sstream>

std::string formatSection(const Section& section, int& optionIndex) noexcept;
std::string formatOption(const Option& option, int space = -1) noexcept;
