#pragma once

#include <string>
#include <vector>

class PathToken;

typedef std::vector<PathToken> PathTokenList;

class PathToken
{
public:
	enum PathTokenType
	{
		Dot, TwoDots, DirSeparator, INDENTIFIER, Root
	};

	PathToken(PathTokenType type, const std::string& lexical) : type(type), lexical(lexical) {}

	constexpr inline PathTokenType getType() const noexcept {
		return type;
	}

	inline std::string getLexical() const noexcept {
		return lexical;
	}

private:
	PathTokenType type;
	std::string lexical;
};