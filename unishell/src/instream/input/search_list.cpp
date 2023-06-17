#include "search_list.h"

#include "../../environment/environment.h"
#include "../../path/handler/path_handler.h"


void INSSearchList::setFromType() noexcept
{
	this->type = type;

	switch (type)
	{
	case SearchListType::Nothing:
		set({});
		break;

	case SearchListType::Command:
		set(cmdListToStr(__sys_commands));
		break;

	case SearchListType::RetCommand:
		set(cmdListToStr(__sys_ret_commands));
		break;

	case SearchListType::Identifier:
		set(__environment->getIdNameList());
		break;

	case SearchListType::Files:
		set(fsys::File::fileListAsString(__workingPath->getPath()));
		break;
	}
}