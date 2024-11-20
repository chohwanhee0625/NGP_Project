#pragma once
#include "include.h"

class S_GAME_READY
{
public:
	bool			Ready_Flag;

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

//===============================================================================================

class INIT_DATA_P
{
public:
	bool	Player_ID;


public:	
	INIT_DATA_P() 
	{}
	INIT_DATA_P(bool id) 
		: Player_ID{id} 
	{}

public:
	std::string to_json();
	void from_json(std::string& j_str);
};

class INIT_DATA_R
{
public:
	// 0: Road
	// 1: Grass 
	std::vector<bool> Roads_Flags;
	// 
	// 0 : LEFT  -> PLUS  -> 왼쪽에서 태어나서 오른쪽으로 이동
	// 1 : RIGHT -> MINUS -> 오른쪽에서 태어나서 왼쪽으로 이동
	std::vector<bool> Dir_Flags;

public:
	std::string to_json();
	void from_json(std::string& j_str);
};

class INIT_DATA_C
{
public:
	std::vector<float>	Cars_Velocity;
	std::vector<std::array<float, 3>> Cars_Color_RGB;


public:
	std::string to_json();
	void from_json(std::string& j_str);
};

class INIT_DATA_W
{
public:
	// 나무를 심을 경우 1, 아니면 0으로 설정
	std::vector<std::array<bool, 12>> Woods_Flags;		// 한 줄에 나무 최대 몇개? 임시로 10

public:
	std::string to_json();
	void from_json(std::string& j_str);
};

//===============================================================================================

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



