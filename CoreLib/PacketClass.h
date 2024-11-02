#pragma once
#include "include.h"

class PacketClass
{
public:
	PacketClass() {}
	PacketClass(int x, int y, int z) : x(x), y(y), z(z) {}

	int x, y, z;
	std::vector<std::array<float, 3>> colors;

	std::string to_json()
	{
		json jObject;
		jObject["x"] = x;
		jObject["y"] = y;
		jObject["z"] = z;
		jObject["colors"] = colors;

		std::string j_str = jObject.dump(4);

		return j_str;
	}

	void from_json(std::string& j_str)
	{
		auto jObject = json::parse(j_str);
		x = jObject.at("x").get<int>();
		y = jObject.at("y").get<int>();
		z = jObject.at("z").get<int>();
		colors = jObject["colors"].get<std::vector<std::array<float, 3>>>();
	}

	void print()
	{
		std::cout << x << ", " << y << ", " << z << "\n";
		for (auto& color : colors)
			std::cout << color[R] << ", " << color[G] << ", " << color[B] << "\n";
	}
};

