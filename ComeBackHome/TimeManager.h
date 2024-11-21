#pragma once

class TimeManager {
private:
    LARGE_INTEGER frequency;   // 고해상도 타이머 주파수
    LARGE_INTEGER lastFrameTime; // 마지막 프레임 시간
    float deltaTime;           // 이전 프레임과의 시간 차이 (초 단위)

public:
    TimeManager() : 
        deltaTime{0.0}
    {
        // 주파수 가져오기
        QueryPerformanceFrequency(&frequency);
        // 시작 시간 초기화
        QueryPerformanceCounter(&lastFrameTime);
    }
    void starttimer();
    // deltaTime 업데이트 함수
    void update();

    // deltaTime을 초 단위로 반환
    float getDeltaTime() const {
        return deltaTime;
    }
};

