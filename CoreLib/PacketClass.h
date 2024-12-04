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
public:
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
	int	Player_ID;


public:	
	INIT_DATA_P() 
	{}
	INIT_DATA_P(int id) 
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
	// 0 : LEFT  -> PLUS  -> ���ʿ��� �¾�� ���������� �̵�
	// 1 : RIGHT -> MINUS -> �����ʿ��� �¾�� �������� �̵�
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
	// ������ ���� ��� 1, �ƴϸ� 0���� ����
	std::vector<std::array<bool, 12>> Woods_Flags;		// �� �ٿ� ���� �ִ� �? �ӽ÷� 10

public:
	std::string to_json();
	void from_json(std::string& j_str);
};

//===============================================================================================

class UPDATE_DATA
{
public:
	bool	Player_ID;
	float	Player_Pos_x;
	float	Player_Pos_y;
	float	Player_Pos_z;
	float	Player_FaceDegree;
	bool	GameOver_Flag;

	UPDATE_DATA& operator=(const UPDATE_DATA& rhs);
public:
	UPDATE_DATA()
		: Player_ID(0), Player_Pos_x(0), Player_Pos_y(0), Player_Pos_z(0)
		, Player_FaceDegree(180.f), GameOver_Flag(0) {}
	UPDATE_DATA(UPDATE_DATA& player_data);
	std::string to_json();

	void from_json(std::string& j_str);
	
private:
	std::mutex m_lock;
};



