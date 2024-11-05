#pragma once
#include "include.h"

class S_GAME_READY
{
private:
	bool			Ready_Flag;

public:
	std::string		to_json();
	void			from_json(std::string& j_str);
};

class S_GAME_OVER
{
private:
	bool				End_Flag;
	std::array<bool, 2> Winner_ID;

public:
	std::string		to_json();
	void			from_json(std::string& j_str);
};

class S_GAME_END
{
private:
public:
	std::string		to_json();
	void			from_json(std::string& j_str);
};



class INIT_DATA_P
{
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

	std::vector<std::array<bool, 20>> Woods_Flags;		// 한 줄에 나무 최대 몇개? 임시로 20

public:
	std::string to_json();

	void from_json(std::string& j_str);

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



