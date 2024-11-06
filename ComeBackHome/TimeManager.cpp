#include "usingInclude.h"
#include "TimeManager.h"

void TimeManager::update()
{
    LARGE_INTEGER currentFrameTime;
    QueryPerformanceCounter(&currentFrameTime);

    // deltaTime 계산 (초 단위)
    deltaTime = static_cast<float>(currentFrameTime.QuadPart - lastFrameTime.QuadPart) / frequency.QuadPart;
    lastFrameTime = currentFrameTime;
}
