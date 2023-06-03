#pragma once

#include "../utilities/stringUtil.h"
#include "../filesystem/file.h"

enum class SearchListType
{
	Nothing,
	Command,
	RetCommand,
	Identifier,
	Files
};

class INSSearchList : private StringList
{
public:
	INSSearchList() {
		type = SearchListType::Command;
		index = 0;
		sequence = false;
	}

	inline void set(const StringList& other) {
		if (sequence) return;
		*((StringList*)this) = other;
		index = 0;
	}

	constexpr inline SearchListType getType() const noexcept {
		return type;
	}

	constexpr inline void setType(SearchListType type) noexcept {
		this->type = type;
	}

	inline void setFromType() noexcept {
		this->type = type;

		switch (type)
		{
		case SearchListType::Nothing:
			set({});
			break;

		case SearchListType::Command:
			set(__sys_commands);
			break;

		case SearchListType::RetCommand:
			set(__sys_ret_commands);
			break;

		case SearchListType::Identifier:
			set(__environment->getIdNameList());
			break;

		case SearchListType::Files:
			set(fsys::File::fileListAsString(__workingPath->getPath()));
			break;
		}
	}

	inline void next() noexcept {
		if (index + 1 >= size()) index = 0;
		else index++;
	}

	inline std::string get() const noexcept {
		if (type == SearchListType::Files)
			return '\"' + (*this)[index] + '\"';
		return (*this)[index];
	}

	inline StringList getList() const noexcept {
		return *((StringList*)this);
	}


	bool sequence;

private:
	SearchListType type;
	int index;
};