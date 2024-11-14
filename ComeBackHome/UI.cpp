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

    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawElements(GL_TRIANGLES, indeices.size(), GL_UNSIGNED_INT, 0);
}

void UI::load_obj(const char* filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    string line;
    map<string, int> tempMap;
    map<int, string> inverseTempMap;
    vector<Vector3> tempV, tempN;
    vector<Vector2> tempT;
    while (std::getline(file, line)) {
        istringstream iss(line);
        string token;
        iss >> token;

        if (token == "v") {
            // 정점 데이터
            Vector3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            tempV.push_back(vertex);
        }
        else if (token == "vn") {
            // 노말 데이터
            Vector3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            tempN.push_back(normal);
        }
        else if (token == "vt") {
            // 텍스쳐 좌표
            Vector2 texture;
            iss >> texture.x >> texture.y;
            tempT.emplace_back(texture);
        }
        else if (token == "f") {
            // 인덱스 데이터
            string faceData;
            getline(iss, faceData);
            istringstream faceIss(faceData);
            string space;
            getline(faceIss, space, ' ');
            for (int i = 0; i < 3; ++i) {
                string vertexIndexStr, texCoordIndexStr, normalIndexStr;

                getline(faceIss, vertexIndexStr, '/');
                getline(faceIss, texCoordIndexStr, '/');
                getline(faceIss, normalIndexStr, ' ');

                string key = vertexIndexStr + '/' + texCoordIndexStr + '/' + normalIndexStr + ' ';
                tempMap.emplace(key, tempMap.size());
                inverseTempMap.emplace(tempMap[key], key);
                indeices.push_back(tempMap[key]);
            }
        }
    }

    for (const auto& p : inverseTempMap) {
        istringstream iss(p.second);
        string vertexIndexStr, texCoordIndexStr, normalIndexStr;
        getline(iss, vertexIndexStr, '/');
        getline(iss, texCoordIndexStr, '/');
        getline(iss, normalIndexStr, ' ');
        vertices.emplace_back(tempV[stoi(vertexIndexStr) - 1]);

        textures.emplace_back(tempT[stoi(texCoordIndexStr) - 1]);

        normals.emplace_back(tempN[stoi(normalIndexStr) - 1]);
    }

    file.close();
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
