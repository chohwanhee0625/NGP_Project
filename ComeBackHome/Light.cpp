#include "usingInclude.h"
#include "Basis.h"
#include "Light.h"
#include "extern.h"

//===========================================================================================

// 선형 보간 함수
float Interpolation(float a, float b, float t) {
	return a + t * (b - a);
}

void Light::InitLight()
{
	light_pos[0] = 5.f;
	light_pos[1] = 15.f;
	light_pos[2] = -7.f;

	light_color[0] = 1.f; 
	light_color[1] = 1.f;
	light_color[2] = 1.f;

	unsigned int lightPosLocation = glGetUniformLocation(gShaderProgramID, "u_lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, light_pos[0], light_pos[1], light_pos[2]);
	unsigned int lightColorLocation = glGetUniformLocation(gShaderProgramID, "u_lightColor");  //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
	glUniform3f(lightColorLocation, light_color[0], light_color[1], light_color[2]);

	// 아침: 밝은 파란 하늘 : (0.529, 0.808, 0.922)
	//		옅은 분홍 또는 주황색 : (1.0, 0.843, 0.678)
	// 저녁노을 :
	//		주황색에서 빨간색으로 : (1.0, 0.412, 0.706)
	//		짙은 분홍 또는 자주색 : (0.545, 0.0, 0.545)
	//		밤 :
	//		어두운 파랑 또는 보라색 : (0.0, 0.0, 0.545)
	//		검은색 : (0.0, 0.0, 0.0
}

void Light::SetTransform()
{
	total_view = glm::mat4{ 1.0f };

	light_pos = glm::vec3{ 0.0f, 25.0f, 30.f};

	unsigned int viewLocation = glGetUniformLocation(gShaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(total_view));
}

void Light::Update()
{
	float chicken_z_distance = -(gVec[0]->GetZpos()); // 치킨 z거리 범위 0 ~ 15, -z가 앞으로 가는 것이기에 -로 양수화

	if (0 <= chicken_z_distance && chicken_z_distance <= 7.f) {
		// 거리 7스텝으로 나눠서 보간 ( 선형보간에서 t 범위 0 ~ 1 ) - 1차 보간 
		// 0부터 7까지 z범위를 0.0~1.0으로 만들어서 t 범위로 사용
		sunset_t = chicken_z_distance / 7;
		SetSunsetInterpolation(sunset_t);

//		cout << "chicken_z, sunset_t, R,G,B : " << chicken_z_distance << ", " << sunset_t << ", " << lightColor[0] << ", " << lightColor[1] << ", " << lightColor[2] << "\n";
	}
	else if (7.f < chicken_z_distance && chicken_z_distance <= 20.f) {
		// 보간 시작 t값을 0으로 초기화 - 2차 보간 
		// sunset_t가 1.0몇이기 때문에 새로운 night_t를 구하되 -sunset_t(1.f)를 빼서 night_t(0.0 ~ 1.0) 범위 지키기
		night_t = chicken_z_distance / 7 - sunset_t; 
		SetNightInterpolation(night_t);
		
//		cout << "chicken_z, night_t, R,G,B : " << chicken_z_distance << ", " << night_t << ", " << lightColor[0] << ", " << lightColor[1] << ", " << lightColor[2] << "\n";
	}

	unsigned int lightColorLocation = glGetUniformLocation(gShaderProgramID, "u_lightColor");  //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
	glUniform3f(lightColorLocation, light_color[0], light_color[1], light_color[2]);
}

void Light::SetSunsetInterpolation(float t) // 노을 보간 
{
	// 시작 RGB, 끝 RGB, 보간t(0.0~1.0)
	light_color[0] = Interpolation(1., 1.0f, t); 
	light_color[1] = Interpolation(1., 0.4f, t);
	light_color[2] = Interpolation(1., 0.5f, t);
}

void Light::SetNightInterpolation(float t) // 밤 보간
{
	light_color[0] = Interpolation(1.0f, 0.3, t);
	light_color[1] = Interpolation(0.4f, 0.3, t);
	light_color[2] = Interpolation(0.5f, 0.5, t);
}
