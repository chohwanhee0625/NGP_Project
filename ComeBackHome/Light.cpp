#include "usingInclude.h"
#include "Basis.h"
#include "Light.h"
#include "extern.h"

//===========================================================================================

// ���� ���� �Լ�
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

	unsigned int lightPosLocation = glGetUniformLocation(gShaderProgramID, "u_lightPos"); //--- lightPos �� ����: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, light_pos[0], light_pos[1], light_pos[2]);
	unsigned int lightColorLocation = glGetUniformLocation(gShaderProgramID, "u_lightColor");  //--- lightColor �� ����: (1.0, 1.0, 1.0) ���
	glUniform3f(lightColorLocation, light_color[0], light_color[1], light_color[2]);

	// ��ħ: ���� �Ķ� �ϴ� : (0.529, 0.808, 0.922)
	//		���� ��ȫ �Ǵ� ��Ȳ�� : (1.0, 0.843, 0.678)
	// ������� :
	//		��Ȳ������ ���������� : (1.0, 0.412, 0.706)
	//		£�� ��ȫ �Ǵ� ���ֻ� : (0.545, 0.0, 0.545)
	//		�� :
	//		��ο� �Ķ� �Ǵ� ����� : (0.0, 0.0, 0.545)
	//		������ : (0.0, 0.0, 0.0
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
	float chicken_z_distance = -(gVec[0]->GetZpos()); // ġŲ z�Ÿ� ���� 0 ~ 15, -z�� ������ ���� ���̱⿡ -�� ���ȭ

	if (0 <= chicken_z_distance && chicken_z_distance <= 7.f) {
		// �Ÿ� 7�������� ������ ���� ( ������������ t ���� 0 ~ 1 ) - 1�� ���� 
		// 0���� 7���� z������ 0.0~1.0���� ���� t ������ ���
		sunset_t = chicken_z_distance / 7;
		SetSunsetInterpolation(sunset_t);

//		cout << "chicken_z, sunset_t, R,G,B : " << chicken_z_distance << ", " << sunset_t << ", " << lightColor[0] << ", " << lightColor[1] << ", " << lightColor[2] << "\n";
	}
	else if (7.f < chicken_z_distance && chicken_z_distance <= 20.f) {
		// ���� ���� t���� 0���� �ʱ�ȭ - 2�� ���� 
		// sunset_t�� 1.0���̱� ������ ���ο� night_t�� ���ϵ� -sunset_t(1.f)�� ���� night_t(0.0 ~ 1.0) ���� ��Ű��
		night_t = chicken_z_distance / 7 - sunset_t; 
		SetNightInterpolation(night_t);
		
//		cout << "chicken_z, night_t, R,G,B : " << chicken_z_distance << ", " << night_t << ", " << lightColor[0] << ", " << lightColor[1] << ", " << lightColor[2] << "\n";
	}

	unsigned int lightColorLocation = glGetUniformLocation(gShaderProgramID, "u_lightColor");  //--- lightColor �� ����: (1.0, 1.0, 1.0) ���
	glUniform3f(lightColorLocation, light_color[0], light_color[1], light_color[2]);
}

void Light::SetSunsetInterpolation(float t) // ���� ���� 
{
	// ���� RGB, �� RGB, ����t(0.0~1.0)
	light_color[0] = Interpolation(1., 1.0f, t); 
	light_color[1] = Interpolation(1., 0.4f, t);
	light_color[2] = Interpolation(1., 0.5f, t);
}

void Light::SetNightInterpolation(float t) // �� ����
{
	light_color[0] = Interpolation(1.0f, 0.3, t);
	light_color[1] = Interpolation(0.4f, 0.3, t);
	light_color[2] = Interpolation(0.5f, 0.5, t);
}
