#pragma once
#include "usingInclude.h"

struct Vector3 {
    float x{ 0 }, y{ 0 }, z{ 0 };
};

struct Vector2 {
    float x{ 0 }, y{ 0 };
};

class UI
{
private:
    GLuint VBO, VAO, EBO, NBO, TBO;
    vector<Vector3> vertices;
    vector<Vector3> normals;
    vector<Vector2> textures;
    vector<int> indeices;

    unsigned int texture;
    glm::mat4 world{ 1 };

    float x, y;                 // UI의 위치 (왼쪽 상단 기준)
    float width, height;        // UI의 크기

public:
    // 생성자
    UI();
    ~UI();

    void InitBuffer();
    void LoadTexture(const string& img_name);
    void Render();

    void load_obj(const char* filePath);
    void resize(float sx, float sy, float sz);
    void move(float dx, float dy, float dz);
    bool isIn(float x, float y);
};