#pragma once

#include <string>
#include <vector>

class PathToken;


using PathTokenList = std::vector<PathToken>;


class PathToken
{
public:
	enum Type {
		Dot,
		TwoDots,
		DirSeparator,
		IDENTIFIER,
		Root
	};

	PathToken(const Type type, const std::string& lexical) : type(type), lexical(lexical) {}

	constexpr Type getType() const noexcept {
		return type;
	}

	constexpr std::string getLexical() const noexcept {
		return lexical;
	}

private:
	Type type;
	std::string lexical;
};