#include "PacketClass.h"

//----------------INIT_DATA_P--------------------
std::string INIT_DATA_P::to_json()
{
	json jObject;
	jObject["ID"] = Player_ID;
	std::string j_str = jObject.dump(4);
	return j_str;
}

void INIT_DATA_P::from_json(std::string& j_str)
{
	auto jObject = json::parse(j_str);

	Player_ID = jObject.at("ID").get<bool>();
}

//----------------INIT_DATA_R--------------------
std::string INIT_DATA_R::to_json()
{
	json jObject;
	jObject["Roads"] = Roads_Flags;
	jObject["Dir"] = Dir_Flags;
	std::string j_str = jObject.dump(4);

	return j_str;
	return std::string();
}

void INIT_DATA_R::from_json(std::string& j_str)
{
	auto jObject = json::parse(j_str);

	Roads_Flags = jObject.at("Roads").get<std::vector<bool>>();
	Dir_Flags = jObject.at("Dir").get<std::vector<bool>>();
}

//----------------INIT_DATA_C--------------------
std::string INIT_DATA_C::to_json()
{
	json jObject;
	jObject["Velocity"] = Cars_Velocity;
	jObject["RGB"] = Cars_Color_RGB;

	std::string j_str = jObject.dump(4);

	return j_str;

}

void INIT_DATA_C::from_json(std::string& j_str)
{
	auto jObject = json::parse(j_str);

	Cars_Velocity = jObject.at("Velocity").get<std::vector<float>>();
	Cars_Color_RGB = jObject["RGB"].get<std::vector<std::array<float, 3>>>();

}

//----------------INIT_DATA_W--------------------
std::string INIT_DATA_W::to_json()
{
	json jObject;
	jObject["Wood"] = Woods_Flags;

	std::string j_str = jObject.dump(4);

	return j_str;
}

void INIT_DATA_W::from_json(std::string& j_str)
{
	auto jObject = json::parse(j_str);

	Woods_Flags = jObject.at("Wood").get<std::vector<std::array<bool, 12>>>();	// 일단 임시로 10

}

//----------------UPDATE_DATA--------------------
UPDATE_DATA& UPDATE_DATA::operator=(const UPDATE_DATA& rhs)
{
	if (this == &rhs) return *this;

	std::lock_guard lock(m_lock);

	Player_Pos_x = rhs.Player_Pos_x;
	Player_Pos_y = rhs.Player_Pos_y;
	Player_Pos_z = rhs.Player_Pos_z;
	Player_FaceDegree = rhs.Player_FaceDegree;
	GameOver_Flag = rhs.GameOver_Flag;
	return *this;
}

UPDATE_DATA::UPDATE_DATA(UPDATE_DATA& player_data)
{
	Player_Pos_x = player_data.Player_Pos_x;
	Player_Pos_y = player_data.Player_Pos_y;
	Player_Pos_z = player_data.Player_Pos_z;
	Player_FaceDegree = player_data.Player_FaceDegree;
	GameOver_Flag = player_data.GameOver_Flag;
}

std::string UPDATE_DATA::to_json()
{
	std::lock_guard lock(m_lock);
	json jObject;
	jObject["ID"] = Player_ID;
	jObject["OtherPos_x"] = Player_Pos_x;
	jObject["OtherPos_y"] = Player_Pos_y;
	jObject["OtherPos_z"] = Player_Pos_z;
	jObject["OtherFace"] = Player_FaceDegree;
	jObject["Over"] = GameOver_Flag;
	std::string j_str = jObject.dump(4);

	return j_str;
}

void UPDATE_DATA::from_json(std::string& j_str)
{
	std::lock_guard lock(m_lock);
	auto jObject = json::parse(j_str);

	Player_ID = jObject.at("ID").get<bool>();
	Player_Pos_x = jObject.at("OtherPos_x").get<float>();
	Player_Pos_y = jObject.at("OtherPos_y").get<float>();
	Player_Pos_z = jObject.at("OtherPos_z").get<float>();
	Player_FaceDegree = jObject.at("OtherFace").get<float>();
	GameOver_Flag = jObject.at("Over").get<bool>();

}

//----------------S_GAME_READY--------------------
std::string S_GAME_READY::to_json()
{
	json jObject;
	jObject["Ready"] = Ready_Flag;
	std::string j_str = jObject.dump(4);

	return j_str;
}

void S_GAME_READY::from_json(std::string& j_str)
{
	auto jObject = json::parse(j_str);

	Ready_Flag = jObject.at("Ready").get<bool>();
}

//----------------S_GAME_OVER--------------------
std::string S_GAME_OVER::to_json()
{
	json jObject;
	jObject["End"] = End_Flag;
	jObject["WinnerID"] = Winner_ID;
	std::string j_str = jObject.dump(4);

	return j_str;
}

void S_GAME_OVER::from_json(std::string& j_str)
{
	auto jObject = json::parse(j_str);
	End_Flag = jObject.at("End").get<bool>();
	Winner_ID = jObject.at("WinnerID").get<std::array<bool, 2>>();
}

//----------------S_GAME_END--------------------
std::string S_GAME_END::to_json()
{
	return std::string();
}

void S_GAME_END::from_json(std::string& j_str)
{
}
