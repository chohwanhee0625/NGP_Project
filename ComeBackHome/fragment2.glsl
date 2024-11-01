#version 330 core
// ���� ���Ե� �����׸�Ʈ ���̴�

//--- out_color: ���ؽ� ���̴����� �Է¹޴� ���� ��
//--- fragcolor: ����� ������ ������ ������ ���۷� ���� ��.

in vec3 out_FragPos;
in vec3 out_Color;
in vec3 out_Normal;

out vec4 fragcolor; //--- ���� ���

uniform vec3 u_lightPos;
uniform vec3 u_lightColor;
uniform vec3 u_viewPos;

uniform int u_lightOn;


void RenderColor()
{
	fragcolor = vec4 (out_Color, 1.0);
}

void RenderAmbient_Light()
{
	float ambientLight = 0.5;
	vec3 ambient = ambientLight * u_lightColor; 

	vec3 result = ambient * out_Color;

	if (u_lightOn == 1) {
		fragcolor = vec4 (result, 1.0); 
	}
	else {
		fragcolor = vec4 (0.3 * out_Color, 1.0); 
	}
}

void RenderDiffuse_Light()
{
	float ambientLight = 0.5; 
	vec3 ambient = ambientLight * u_lightColor; 

	vec3 normalVector = normalize(out_Normal);
	vec3 lightDir = normalize(u_lightPos - out_FragPos); 
	float diffuseLight = max(dot(normalVector, lightDir), 0.0); 
	vec3 diffuse = diffuseLight * u_lightColor; 

	vec3 result = (ambient + diffuse) * out_Color;
	if (u_lightOn == 1) {
		fragcolor = vec4 (result, 1.0); 
	}
	else {
		fragcolor = vec4 (0.3 * out_Color, 1.0); 
	}
}


void RenderPhongShading_Light()
{
	float ambientLight = 0.5; 
	vec3 ambient = ambientLight * u_lightColor; 

	vec3 normalVector = normalize(out_Normal);
	vec3 lightDir = normalize(u_lightPos - out_FragPos); 
	float diffuseLight = max(dot(normalVector, lightDir), 0.0); 
	vec3 diffuse = diffuseLight * u_lightColor; 

	int shininess = 128; 
	vec3 viewDir = normalize(u_viewPos - out_FragPos);
	vec3 reflectDir = reflect(-lightDir, normalVector); 
	float specularLight = max(dot(viewDir, reflectDir), 0.0); 
	specularLight = pow(specularLight, shininess); 
	vec3 specular = specularLight * u_lightColor; 



	vec3 result = (ambient + diffuse + specular) * out_Color;
	if (u_lightOn == 1) {
		fragcolor = vec4 (result, 1.0); 
	}
	else {
		fragcolor = vec4 (0.3 * out_Color, 1.0); 
	}
}

void main(void) 
{
    //RenderAmbient_Light();
    //RenderDiffuse_Light();
	RenderPhongShading_Light();

}