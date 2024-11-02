#include "PacketClass.h"

std::string INIT_DATA_P::to_json()
{
	json jObject;
	jObject["ID"] = Player_ID;
	jObject["Pos_x"] = Player_Pos_x;
	jObject["Pos_y"] = Player_Pos_y;
	jObject["Pos_z"] = Player_Pos_z;

	std::string j_str = jObject.dump(4);

	return j_str;


}

void INIT_DATA_P::from_json(std::string& j_str)
{
	auto jObject = json::parse(j_str);

	Player_ID = jObject.at("ID").get<bool>();

	Player_Pos_x = jObject.at("Pos_x").get<float>();
	Player_Pos_y = jObject.at("Pos_y").get<float>();
	Player_Pos_z = jObject.at("Pos_z").get<float>();

}

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

	Woods_Flags = jObject.at("Wood").get<std::vector<bool>>();

}

std::string UPDATE_DATA::to_json()
{
	json jObject;
	jObject["ID"] = Player_ID;
	jObject["OtherPos_x"] = Other_Player_Pos_x;
	jObject["OtherPos_y"] = Other_Player_Pos_y;
	jObject["OtherPos_z"] = Other_Player_Pos_z;
	jObject["OtherFace"] = Other_Player_Face;
	jObject["Over"] = GameOver_Flag;
	std::string j_str = jObject.dump(4);

	return j_str;
}

void UPDATE_DATA::from_json(std::string& j_str)
{
	auto jObject = json::parse(j_str);

	Player_ID = jObject.at("ID").get<bool>();
	Other_Player_Pos_x = jObject.at("OtherPos_x").get<float>();
	Other_Player_Pos_y = jObject.at("OtherPos_y").get<float>();
	Other_Player_Pos_z = jObject.at("OtherPos_z").get<float>();
	Other_Player_Face = jObject.at("OtherFace").get<char>();
	GameOver_Flag = jObject.at("Over").get<bool>();

}
