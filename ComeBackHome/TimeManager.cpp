#include "usingInclude.h"
#include "TimeManager.h"
#include "extern.h"

void TimeManager::starttimer()
{
    // 주파수 가져오기
    QueryPerformanceFrequency(&frequency);
    // 시작 시간 초기화
    QueryPerformanceCounter(&lastFrameTime);
}

void TimeManager::update()
{
    LARGE_INTEGER currentFrameTime;
    QueryPerformanceCounter(&currentFrameTime);

    // deltaTime 계산 (초 단위)
    deltaTime = static_cast<float>(currentFrameTime.QuadPart - lastFrameTime.QuadPart) / frequency.QuadPart;
    lastFrameTime = currentFrameTime;
}
