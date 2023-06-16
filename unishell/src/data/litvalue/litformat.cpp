#include "litformat.h"

#include "../../system/global/global.h"

#include <sstream>

std::string lit::literalValueToString(LiteralValue* val, const bool color) noexcept
{
	if (!val) return ((color) ? nullformat("null") : "null");

	if (val->index() == 0) return ((color) ? qtd(asStr(val)) : asStr(val));
	else if (val->index() == 1) return formatDouble(asDbl(val), color);
	else if (val->index() == 2) return boolToString(asBool(val), color);
	else if (val->index() == 3) return formatList(val);
	else if (val->index() == 4) return formatObject(val);

	return std::string();
}


std::string lit::formatObject(LiteralValue* lit) noexcept
{
	std::stringstream str;

	str << "Object( ";

	std::map<std::string, LiteralValue*> obj = asObj(lit);

	auto objEnd = obj.end();

	if (obj.size() > 0) objEnd--;

	for (auto it = obj.begin(); it != obj.end(); it++)
		str << it->first << ": " << litToStr(it->second, true) << ((it != objEnd) ? ", " : "");

	str << " )";

	return str.str();
}


std::string lit::formatList(LiteralValue* lit) noexcept
{
	std::stringstream str;

	str << "List( ";

	std::vector<LiteralValue*> list = asList(lit);

	for (size_t i = 0; i < list.size(); i++)
		str << litToStr(list[i], true) << ((i + 1 < list.size()) ? ", " : "");

	str << " )";

	return str.str();
}


std::string lit::formatDouble(const double value, const bool color) noexcept
{
	std::string strNum = tostr(value);
	size_t pos = strNum.find_last_not_of('0');

	if (pos != std::string::npos && strNum[pos] == '.')
		pos--;

	strNum.erase(pos + 1);

	return ((color) ? numformat(strNum) : strNum);
}



std::string lit::colorizeStrType(const std::string& type) noexcept
{
	if (type == "Literal")		return clr(type, __clr_type_literal->toString());
	else if (type == "Number")	return clr(type, __clr_type_number->toString());
	else if (type == "Bool")	return clr(type, __clr_type_bool->toString());
	else if (type == "List")	return clr(type, __clr_type_list->toString());
	else if (type == "Object")	return clr(type, __clr_type_object->toString());
	else if (type == "Any")		return clr(type, __clr_type_any->toString());

	else return type;
}



TokenEnum lit::typeToTokenEnum(const LiteralValue::Type type) noexcept
{
	switch (type) {
	case lit::LitType::Literal:	return LITERAL;
	case lit::LitType::Number:	return NUMBER;
	case lit::LitType::Bool:	return BOOLEANVAL;
	case lit::LitType::List:	return LIST;
	case lit::LitType::Object:	return OBJECT;
	case lit::LitType::Null:	return NULLVAL;
	}

	return LITERAL;
}


std::string lit::getTypeAsString(const LiteralValue::Type type, const bool colorize) noexcept
{
	std::string ret;

	switch (type) {
	case LiteralValue::Type::Literal:	ret = "Literal"; break;
	case LiteralValue::Type::Number:	ret = "Number";	 break;
	case LiteralValue::Type::Bool:		ret = "Bool";	 break;
	case LiteralValue::Type::List:		ret = "List";	 break;
	case LiteralValue::Type::Object:	ret = "Object";  break;
	case LiteralValue::Type::Null:		ret = "Null";	 break;
	case LiteralValue::Type::Any:		ret = "Any";	 break;

	default: ret = "Unknown";
	}

	if (colorize)
		ret = colorizeStrType(ret);

	return ret;
}