#pragma once
// �ʿ��� ���̺귯��, using, enum ����
//"#pragma once" ���ù��� ��� ������ ������ �̹� �� ��
// ���ԵǾ��ٸ� �ش� ��� ������ �ٽ� ��������
// �ʵ��� �����Ϸ��� �����մϴ�.

#include "include.h"
#include "PacketClass.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>


#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>


#define SQUARE 0.1 

class Basis;
class Camera;
class Light;
class Border;

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;




enum class Toggle
{
	Perpective = 0, // ����
	Light = 1,
	NearFar = 2,
	END = 10,
};

enum Dir
{
	STOP = 0,
	South = 1,
	West = 2,
	North = 3,
	East = 4,
};

enum myEnum
{
	OFF = 0,
	ON = 1,

	MINUS = -1,
	PLUS = 1,

	Third = 0,
	One = 1,

	LEFT = 0,
	RIGHT = 1,

	Near = 1,
	Far = 0,
};

typedef int Sign;




