#include "json.h"


// fromJson
START_HELP(JSONRetCmdFromJson)
return { .name = JSONRetCmdFromJson().symbol, .params = {{"Source", {lit::LitType::Literal}}}, .description = "converts ^0 JSON to a unishell value." };
END_HELP

// toJson
START_HELP(JSONRetCmdToJson)
return { .name = JSONRetCmdToJson().symbol, .params = {{"Source", {lit::LitType::Any}}}, .description = "converts ^0 value to a JSON string representation." };
END_HELP