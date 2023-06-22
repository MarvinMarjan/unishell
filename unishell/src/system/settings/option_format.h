#pragma once

#include "option.h"
#include "../../color/parser/color_parser.h"
#include "../../instream/scanner/instream_scanner.h"

#include <sstream>

std::string formatOption(const Option& option) noexcept;