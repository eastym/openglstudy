#pragma once
#pragma comment(lib, "winmm.lib")

#include <string>
#include <chrono>
#include <time.h>
#include <thread>
#include <iostream>
#include <functional>

#define CPUMax 30000
#define CPUMin 10000

using namespace std::chrono;

// FPS管理クラス
class FPS
{
private:
    //ループカウンタ
    int loopCnt;
    //現在のフレームスキップ数
    int valueSkip;
    //一秒おきのフレームスキップ数
    int secondSkipCnt;
    //設定のFPS値
    int Fps;
    //一秒おきのループカウンタ
    int LoopMax;
    //現在のフレーム
    int currentFrame;
    //現在のFPS値
    int currentFps;

    //スリープ値
    microseconds valueSleep;
    // 1フレームの時間
    nanoseconds FrameTime, FrameTimeO;

    high_resolution_clock::time_point currentTime, pastTime;

public:
    FPS(int fps);
    void SetFPS(int fps);
    void GetFPS(std::function<void(void)> target);
};
