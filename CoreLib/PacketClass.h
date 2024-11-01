#pragma once
#include "include.h"

class PacketClass
{
	int x, y, z;

	std::string to_json()
	{
		json jObject;
		jObject["x"] = x;
		jObject["y"] = y;
		jObject["z"] = z;

		std::string j_str = jObject.dump(4);

		return j_str;
	}

	void from_json(std::string& j_str)
	{
		auto jObject = json::parse(j_str);
		x = jObject.at("x").get<int>();
		y = jObject.at("y").get<int>();
		z = jObject.at("z").get<int>();
	}
};

