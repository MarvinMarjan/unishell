#pragma once

#include <string>
#include <vector>

class PathToken;

typedef std::vector<PathToken> PathTokenList;

class PathToken
{
public:
	enum PathTokenType {
		Dot,
		TwoDots,
		DirSeparator,
		IDENTIFIER,
		Root
	};

	PathToken(const PathTokenType type, const std::string& lexical) : type(type), lexical(lexical) {}

	constexpr PathTokenType getType() const noexcept {
		return type;
	}

	constexpr std::string getLexical() const noexcept {
		return lexical;
	}

private:
	PathTokenType type;
	std::string lexical;
};