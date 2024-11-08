#include "UI.h"
#include "Tools.h"

static vector<Vector3> vertices{ {-1,1,0.99},{-1,-1,0.99},{1,-1,0.99},{1,1,0.99} };
static vector<Vector3> normals{ {0,0,-1},{0,0,-1} ,{0,0,-1} ,{0,0,-1} };
static vector<Vector2> textures{ {0,0},{0,1},{1,1},{1,0} };
static vector<int> indeices{ 0,1,2,2,3,0 };
//Border UI::border{ vertices,normals,textures,indeices };

void UI::InitBuffer()
{
	//border.InitBuffer();
}

void UI::load(const string& img_name, const char* sound_name, bool loop, float volume)
{
	init_texture(texture, img_name, false);
}

void UI::draw() const
{
	//glBindVertexArray(border.m_vao);
	//auto view_location = glGetUniformLocation(gShaderProgramID, "view");
	//glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));

	//auto proj_location = glGetUniformLocation(gShaderProgramID, "proj");
	//glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));

	//auto world_location = glGetUniformLocation(gShaderProgramID, "world");
	//glUniformMatrix4fv(world_location, 1, GL_FALSE, glm::value_ptr(world));

	//auto tiworld_location = glGetUniformLocation(gShaderProgramID, "normalWorld");
	//glUniformMatrix4fv(tiworld_location, 1, GL_FALSE, glm::value_ptr(world));

	//auto light_location = glGetUniformLocation(gShaderProgramID, "lightPos");
	//glUniform3f(light_location, 0, 0, 0);

	//auto light_color = glGetUniformLocation(gShaderProgramID, "lightColor");
	//glUniform3f(light_color, 1, 1, 1);

	//auto color_loc = glGetUniformLocation(gShaderProgramID, "color");
	//glUniform4f(color_loc, 1, 1, 1, 1);

	//glBindTexture(GL_TEXTURE_2D, texture);
	//glDrawElements(GL_TRIANGLES, border.indeices.size(), GL_UNSIGNED_INT, 0);

}

void UI::resize(float sx, float sy, float sz)
{
	world = world * glm::scale(glm::mat4(1), glm::vec3(sx, sy, sz));
}

void UI::move(float dx, float dy, float dz)
{
	world = glm::translate(glm::mat4(1), glm::vec3(dx, dy, dz)) * world;
}

bool UI::isIn(float x, float y)
{
	auto lb = world * glm::vec4(-1, -1, 0, 1), rt = world * glm::vec4(1, 1, 0, 1);
	if (lb.x <= x && x <= rt.x && lb.y <= y && y <= rt.y) {
		return true;
	}
	return false;
}
