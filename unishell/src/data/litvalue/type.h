#pragma once

#include "../../instream/scanner/instream_token.h"
#include "../../system/exception/system_exception.h"

#include <variant>
#include <map>


#define asStr(pLit)		std::get<std::string>(*pLit)
#define asDbl(pLit)		std::get<double>(*pLit)
#define asBool(pLit)	std::get<bool>(*pLit)
#define asList(pLit)	std::get<std::vector<lit::LiteralValue*>>(*pLit)
#define asObj(pLit)		std::get<std::map<std::string, lit::LiteralValue*>>(*pLit)
#define asBlock(pLit)	std::get<lit::Block>(*pLit)


extern std::string* __userInput;


namespace lit
{

	
	using LitList = std::vector<LiteralValue*> ;
	using LitObject = std::map<std::string, LiteralValue*>;


	// private, users can't manipulate directly with it
	using Block = std::vector<TokenList>;


	using LiteralValueDecl = std::variant<std::string, double, bool, LitList, LitObject, Block>;


	class LiteralValue : public LiteralValueDecl
	{
	public:
		enum class Type
		{
			Literal,
			Number,
			Bool,
			List,
			Object,
			Block,

			Null,
			Any
		};

		using TypeList = std::vector<Type>;

		using List = LitList;
		using Object = LitObject;


		LiteralValue(const LiteralValueDecl& other) : LiteralValueDecl(other) {}

		LiteralValue(const Block& other)		: LiteralValueDecl(other) {}
		LiteralValue(const LitObject& other)	: LiteralValueDecl(other) {}
		LiteralValue(const LitList& other)		: LiteralValueDecl(other) {}
		LiteralValue(const std::string& other)	: LiteralValueDecl(other) {}
		LiteralValue(const double other)		: LiteralValueDecl(other) {}
		LiteralValue(const bool other)			: LiteralValueDecl(other) {}


		constexpr Type type() const noexcept {
			return typeof((LiteralValue*)this);
		}


		static constexpr Type typeof(LiteralValue* value) noexcept {
			if (!value) return Type::Null;
			return (Type)value->index();
		}
	};


	using LitType = LiteralValue::Type;
	using LitTypeList = LiteralValue::TypeList;



	template <typename T>
	inline LiteralValue* lit(const T& value) noexcept {
		return new LiteralValue(LiteralValueDecl(value));
	}

	inline LiteralValue* lit(const int value) noexcept {
		return new LiteralValue(LiteralValueDecl((double)value));
	}

	LiteralValue* getListFromTokenList(const TokenList& source);
	LiteralValue* getObjFromTokenList(const TokenList& source);
	

} // namespace lit