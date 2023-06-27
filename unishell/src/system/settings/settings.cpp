#include "settings.h"

#include "../system.h"


Settings::Settings() {
	try {
		data_ = JSONFstreamHandle(UNISHLL_SETTINGS_DEFAULT_JSON_FILE_PATH);

		__sys_stat->settingJsonFileLoadFailed = false;
	}
	catch (const JSONFstreamHandle::JSONFileNotFound&) {
		__sys_stat->settingJsonFileLoadFailed = true;
	}
}