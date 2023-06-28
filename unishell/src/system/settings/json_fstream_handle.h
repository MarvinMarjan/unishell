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

	JSONFstreamHandle() : fail_(false) {}
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
		if (data.is_array()) return JSONListToLiteralValueList(data);
		if (data.is_object()) return JSONObjectToLiteralValueObject(data);

		return nullptr;
	}

	static json LiteralValueToJSONValue(lit::LiteralValue* value) {
		if (value->index() == 0) return asStr(value);
		if (value->index() == 1) return asDbl(value);
		if (value->index() == 2) return asBool(value);
		if (value->index() == 3) return LiteralValueListToJSONValue(value);
		if (value->index() == 4) return LiteralValueObjectToJSONValue(value);

		return json();
	}



	static json LiteralValueListToJSONValue(lit::LiteralValue* value) {
		lit::LitList list = asList(value);
		json jVal;
		
		for (lit::LiteralValue* item : list)
			jVal.push_back(LiteralValueToJSONValue(item));

		return jVal;
	}

	static json LiteralValueObjectToJSONValue(lit::LiteralValue* value) {
		lit::LitObject obj = asObj(value);
		json jVal;

		for (const auto& [key, value] : obj)
			jVal[key] = LiteralValueToJSONValue(value);

		return jVal;
	}



	static lit::LiteralValue* JSONListToLiteralValueList(json jVal) {
		lit::LitList list;

		for (const auto& val : jVal)
			list.push_back(JSONValueToLiteralValue(val));

		return lit::lit(list);
	}

	static lit::LiteralValue* JSONObjectToLiteralValueObject(json jVal) {
		lit::LitObject obj;

		for (const auto& [key, value] : jVal.items())
			obj.insert({ key, JSONValueToLiteralValue(value) });

		return lit::lit(obj);
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
