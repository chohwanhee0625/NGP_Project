#include "UI.h"
#include "Tools.h"
#include "stb_image.h"


UI::UI()
{
    vector<Vector3> v{ {-1,1,0.99},{-1,-1,0.99},{1,-1,0.99},{1,1,0.99} };
    vector<Vector3> n{ {0,0,-1},{0,0,-1} ,{0,0,-1} ,{0,0,-1} };
    vector<Vector2> t{ {0,0},{0,1},{1,1},{1,0} };
    vector<int> i{ 0,1,2,2,3,0 };

    vertices = v;
    normals = n;
    textures = t;
    indeices = i;
}

UI::~UI()
{
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    //glDeleteTextures(1, &texture);
}

void UI::InitBuffer()
{
    vector<Vector3> v{ {-1,1,0.99},{-1,-1,0.99},{1,-1,0.99},{1,1,0.99} };
    vector<Vector3> n{ {0,0,-1},{0,0,-1} ,{0,0,-1} ,{0,0,-1} };
    vector<Vector2> t{ {0,0},{0,1},{1,1},{1,0} };
    vector<int> i{ 0,1,2,2,3,0 };

    vertices = v;
    normals = n;
    textures = t;
    indeices = i;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &NBO);
    glGenBuffers(1, &TBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(Vector3), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(Vector2), textures.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indeices.size() * sizeof(int), indeices.data(), GL_STATIC_DRAW);
}

void UI::LoadTexture(const string& img_name)
{
    init_texture(texture, img_name, false);
}

void UI::Render()
{
    glBindVertexArray(VAO);
    auto view_location = glGetUniformLocation(gUIShaderProgramID, "view");
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));

    auto proj_location = glGetUniformLocation(gUIShaderProgramID, "proj");
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));

    auto world_location = glGetUniformLocation(gUIShaderProgramID, "world");
    glUniformMatrix4fv(world_location, 1, GL_FALSE, glm::value_ptr(world));

    auto tiworld_location = glGetUniformLocation(gUIShaderProgramID, "normalWorld");
    glUniformMatrix4fv(tiworld_location, 1, GL_FALSE, glm::value_ptr(world));

    auto light_location = glGetUniformLocation(gUIShaderProgramID, "lightPos");
    glUniform3f(light_location, 0, 0, 0);

    auto light_color = glGetUniformLocation(gUIShaderProgramID, "lightColor");
    glUniform3f(light_color, 1, 1, 1);

    auto color_loc = glGetUniformLocation(gUIShaderProgramID, "color");
    glUniform4f(color_loc, 1, 1, 1, 1);

    auto texture_location = glGetUniformLocation(gUIShaderProgramID, "outTexture");
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(texture_location, 0);
    glDrawElements(GL_TRIANGLES, indeices.size(), GL_UNSIGNED_INT, 0);
}

void UI::change_img(const string& new_img_name) {
    int widthImg, heightImg, numberOfChannel;
    unsigned char* data = my_load_image(new_img_name.c_str(), &widthImg, &heightImg, &numberOfChannel);

    if (data != NULL) {
        glBindTexture(GL_TEXTURE_2D, texture);

        if (numberOfChannel == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, numberOfChannel, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else if (numberOfChannel == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, numberOfChannel, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        my_image_free(data);
    }
    else {
        cout << "fail to load image" << endl;
    }
}

void UI::resize(float sx, float sy, float sz) {
    world = world * glm::scale(glm::mat4(1), glm::vec3(sx, sy, sz));
}

void UI::move(float dx, float dy, float dz) {
    world = glm::translate(glm::mat4(1), glm::vec3(dx, dy, dz)) * world;
}

bool UI::isIn(float x, float y) {
    auto lb = world * glm::vec4(-1, -1, 0, 1), rt = world * glm::vec4(1, 1, 0, 1);
    if (lb.x <= x && x <= rt.x && lb.y <= y && y <= rt.y) {
        return true;
    }
    return false;
}
