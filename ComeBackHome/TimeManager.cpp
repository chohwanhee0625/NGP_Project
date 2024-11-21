#include "usingInclude.h"
#include "TimeManager.h"
#include "extern.h"

void TimeManager::starttimer()
{
    // ���ļ� ��������
    QueryPerformanceFrequency(&frequency);
    // ���� �ð� �ʱ�ȭ
    QueryPerformanceCounter(&lastFrameTime);
}

void TimeManager::update()
{
    LARGE_INTEGER currentFrameTime;
    QueryPerformanceCounter(&currentFrameTime);

    // deltaTime ��� (�� ����)
    deltaTime = static_cast<float>(currentFrameTime.QuadPart - lastFrameTime.QuadPart) / frequency.QuadPart;
    lastFrameTime = currentFrameTime;
}
