#pragma once
#pragma comment(lib, "winmm.lib")

#include <string>
#include <chrono>
#include <time.h>
#include <thread>
#include <iostream>

#define CPUMax 30000
#define CPUMin 10000

using namespace std::chrono;

// FPS管理クラス
class FPS
{
public:
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
    FPS(int);
    void SetFPS(int);
    void GetFPS();
};

//コンストラクタ
FPS::FPS(int fps=60) : loopCnt(0),
                    valueSkip(0),
                    secondSkipCnt(0),
                    LoopMax(0),
                    currentFrame(0),
                    currentFps(0)
{
    Fps = fps;

    valueSleep = microseconds(15000);
    FrameTime = nanoseconds((1000000000 / fps) - 1);
    FrameTimeO = nanoseconds((1000000000 / fps) + 1);
}
void FPS::SetFPS(int fps)
{
    Fps = fps;
    FrameTime = nanoseconds((1000000000 / fps) - 1); // 1フレームの時間
    FrameTimeO = nanoseconds((1000000000 / fps) + 1);
}
void FPS::GetFPS()
{
    loopCnt++;

    currentTime = high_resolution_clock::now();

    if (duration_cast<milliseconds>(currentTime - pastTime) > currentFrame * FrameTime)
    {
        currentFrame++;
        if (duration_cast<milliseconds>(currentTime - pastTime) < currentFrame * FrameTimeO)
        { //描画タイミングに間に合った場合

            std::this_thread::sleep_for(valueSleep);

            std::cout << "LOOP_MAX:[ " << LoopMax << " ] FPS:[ " << currentFps - secondSkipCnt << " ] FRAME:[ " << currentFrame << " ] FRAMESKIP:[ " << secondSkipCnt << " ] SLEEP:[ " << valueSleep.count() << "]" << std::endl;
        }
        else
        { //描画タイミングに間に合わなかった場合：フレームスキップ
            if (valueSleep > milliseconds(1))
            {
                valueSleep-= microseconds(100); //ウェイトを減らす
            }
            valueSkip++;
        }
    }
    if (duration_cast<milliseconds>(currentTime - pastTime) > milliseconds(1000) - duration_cast<milliseconds>(FrameTime))
    { //一秒おきの処理
        LoopMax = loopCnt;
        if (LoopMax > CPUMax)
        {
            if (valueSleep < milliseconds(15))
            {
                valueSleep+=microseconds(100);
            }
        } //十分に余力がある場合ウェイトを増やす
        if (LoopMax < CPUMin)
        {
            if (valueSleep > milliseconds(1))
            {
                valueSleep-=microseconds(100);
            }
        } //余裕が無い場合ウェイトを減らす
        currentFps = currentFrame;
        secondSkipCnt = valueSkip;
        valueSkip = 0;
        loopCnt = 0;
        currentFrame = 0;
        pastTime = currentTime;
    }
}