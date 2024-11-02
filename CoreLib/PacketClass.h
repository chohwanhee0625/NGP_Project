#pragma once
#include "include.h"


class INIT_DATA_P
{
<<<<<<< taejun
private:

	bool	Player_ID;
	float	Player_Pos_x;
	float	Player_Pos_y;
	float	Player_Pos_z;

public:	

	std::string to_json();

	void from_json(std::string& j_str);
	
};



class INIT_DATA_R
{
private:
	std::vector<bool> Roads_Flags;
	std::vector<bool> Dir_Flags;

public:
	std::string to_json();

	void from_json(std::string& j_str);

};


class INIT_DATA_C
{
private:
	std::vector<float>	Cars_Velocity;
	std::vector<std::array<float, 3>> Cars_Color_RGB;


public:
	std::string to_json();

	void from_json(std::string& j_str);

};


class INIT_DATA_W
{
private:

	std::vector<bool> Woods_Flags;

public:
	std::string to_json();

	void from_json(std::string& j_str);

=======
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
>>>>>>> main
};


class UPDATE_DATA
{
private:
	bool	Player_ID;
	float	Other_Player_Pos_x;
	float	Other_Player_Pos_y;
	float	Other_Player_Pos_z;
	char	Other_Player_Face;
	bool	GameOver_Flag;


public:
	std::string to_json();

	void from_json(std::string& j_str);
	
};



