#pragma once

#include "../../filesystem/handle/file.h"

#include <nlohmann/json.hpp>


using json = nlohmann::json;


class JSONFstreamHandle : public json
{
public:
	struct JSONFileNotFound {
		std::string path;
	};

	JSONFstreamHandle() {}
	JSONFstreamHandle(const std::string& path) 
		: path_(path)
	{
		load();
	}
	
	~JSONFstreamHandle() {
		save();
	}


	static lit::LiteralValue* JSONValueToLiteralValue(json data) {
		if (data.is_string()) return new lit::LiteralValue(data.get<std::string>());
		if (data.is_number()) return new lit::LiteralValue(data.get<double>());
		if (data.is_boolean()) return new lit::LiteralValue(data.get<bool>());

		return nullptr;
	}

	static json LiteralValueToJSONValue(lit::LiteralValue* value) {
		if (value->index() == 0) return asStr(value);
		if (value->index() == 1) return asDbl(value);
		if (value->index() == 2) return asBool(value);

		return nullptr;
	}


	void load() {
		if (fsys::File::exists(path_)) {
			*((json*)this) = json::parse(std::ifstream(path_));

			fail_ = false;
		}

		else {
			fail_ = true;
			throw JSONFileNotFound {.path = path_};
		}
	}

	void save() {
		if (fsys::File::exists(path_))
			fsys::File::write(path_, dump(2));
	}


	constexpr bool fail() const noexcept {
		return fail_;
	}


private:
	std::string path_;

	bool fail_;
};
