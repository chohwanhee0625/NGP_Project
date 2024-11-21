#pragma once

class TimeManager {
private:
    LARGE_INTEGER frequency;   // ���ػ� Ÿ�̸� ���ļ�
    LARGE_INTEGER lastFrameTime; // ������ ������ �ð�
    float deltaTime;           // ���� �����Ӱ��� �ð� ���� (�� ����)

public:
    TimeManager() : 
        deltaTime{0.0}
    {
        // ���ļ� ��������
        QueryPerformanceFrequency(&frequency);
        // ���� �ð� �ʱ�ȭ
        QueryPerformanceCounter(&lastFrameTime);
    }
    void starttimer();
    // deltaTime ������Ʈ �Լ�
    void update();

    // deltaTime�� �� ������ ��ȯ
    float getDeltaTime() const {
        return deltaTime;
    }
};

