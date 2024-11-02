#include "Basis.h"

void BasisComponent::WorldMatrix()
{
	initTotalworld();

	m_Total_world = glm::rotate(m_Total_world, glm::radians(m_x_degree), glm::vec3(1.0f, 0.0f, 0.0f)); // x�� ȸ�� �⺻
	m_Total_world = glm::rotate(m_Total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y�� ȸ�� �⺻ 
	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_x_distance, m_y_distance, m_z_distance)); // �⺻ �̵� 
	m_Total_world = glm::scale(m_Total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // �⺻ ����

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_Total_world));
}