#version 330 core
// 조명 포함된 버텍스 쉐이더

//--- in_Position: attribute index 0 
//--- in_Color: attribute index 1

layout (location = 0) in vec3 in_Position; //--- 위치 변수: attribute position 0
layout (location = 1) in vec3 in_Color; //--- 컬러 변수: attribute position 1
layout (location = 2) in vec3 in_Normal; //--- 컬러 변수: attribute position 1

out vec3 out_FragPos;
out vec3 out_Color;
out vec3 out_Normal;


uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void Render2D() 
{
	out_Color = in_Color;
	gl_Position = vec4 (in_Position.x, in_Position.y, in_Position.z, 1.0);
}

void Render3D() 
{
	out_FragPos = vec3(modelTransform * vec4(in_Position,1.0));
	out_Color = in_Color;
	out_Normal = mat3(mat3(transpose(inverse(mat3(modelTransform))))) * in_Normal;
//	out_Normal = in_Normal;
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4(in_Position, 1.0);
}

void main(void) 
{
	Render3D();
}