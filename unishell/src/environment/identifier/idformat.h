#pragma once


#include "identifier.h"
#include "../../data/litvalue/litformat.h"
#include "../../outstream/control/outformat.h"

#include <iomanip>
#include <sstream>


extern BaseColorStructure* __clr_identifier;
extern BaseColorStructure* __clr_sys_identifier;


// contains Identifier data as string
struct FormatedIdentifierData {
	std::string name;
	std::string value;
	std::string type;
};

FormatedIdentifierData formatIdentifier(const Identifier& identifier);

std::string formatedIdentifierDataToString(const FormatedIdentifierData& data) noexcept;