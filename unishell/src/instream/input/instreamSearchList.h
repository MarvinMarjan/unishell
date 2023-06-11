#pragma once

#include "../../filesystem/handle/file.h"
#include "../../utilities/cmdUtil.h"

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
	inline constexpr INSSearchList() {
		type = SearchListType::Command;
		index = 0;
		sequence = false;
	}

	constexpr void set(const StringList& other) {
		if (sequence) return;
		*((StringList*)this) = other;
		index = 0;
	}

	constexpr SearchListType getType() const noexcept {
		return type;
	}

	constexpr void setType(const SearchListType type) noexcept {
		this->type = type;
	}

	constexpr void setFromType() noexcept {
		this->type = type;

		switch (type)
		{
		case SearchListType::Nothing:
			set({});
			break;

		case SearchListType::Command:
			set(CmdUtil::cmdListToStr(__sys_commands));
			break;

		case SearchListType::RetCommand:
			set(CmdUtil::cmdListToStr(__sys_ret_commands));
			break;

		case SearchListType::Identifier:
			set(__environment->getIdNameList());
			break;

		case SearchListType::Files:
			set(fsys::File::fileListAsString(__workingPath->getPath()));
			break;
		}
	}

	constexpr void next() noexcept {
		if (index + 1 >= size()) index = 0;
		else index++;
	}

	constexpr std::string get() const noexcept {
		if (type == SearchListType::Files)
			return '\"' + (*this)[index] + '\"';
		return (*this)[index];
	}

	constexpr StringList getList() const noexcept {
		return *((StringList*)this);
	}


	bool sequence;

private:
	SearchListType type;
	int index;
};