#include "fps.hpp"

//コンストラクタ
FPS::FPS(int fps) : loopCnt(0),
                    valueSkip(0),
                    secondSkipCnt(0),
                    LoopMax(0),
                    currentFrame(0),
                    currentFps(0),
                    Fps(fps),
                    valueSleep(microseconds(1500))

{
    FrameTime = nanoseconds((1000000000 / fps) - 1);
    FrameTimeO = nanoseconds((1000000000 / fps) + 1);
}
void FPS::SetFPS(int fps)
{
    Fps = fps;
    FrameTime = nanoseconds((1000000000 / fps) - 1); // 1フレームの時間
    FrameTimeO = nanoseconds((1000000000 / fps) + 1);
}
void FPS::GetFPS(std::function<void(void)> target)
{
    loopCnt++;

    currentTime = high_resolution_clock::now();

    if (duration_cast<milliseconds>(currentTime - pastTime) > currentFrame * FrameTime)
    {
        currentFrame++;
        if (duration_cast<milliseconds>(currentTime - pastTime) < currentFrame * FrameTimeO)
        { //描画タイミングに間に合った場合

            std::this_thread::sleep_for(valueSleep);

            target();

            std::cout << "FUNC_CALL_P_S:[ " << LoopMax << " ] FPS:[ " << currentFps - secondSkipCnt << " ] FRAME:[ " << currentFrame << " ] FRAMESKIP:[ " << secondSkipCnt << " F] SLEEP:[ " << valueSleep.count() << "microseconds]" << std::endl;
        }
        else
        { //描画タイミングに間に合わなかった場合：フレームスキップ
            if (valueSleep > microseconds(100))
            {
                valueSleep -= microseconds(100); //ウェイトを減らす
            }
            else if (valueSleep < microseconds(100))
            {
                valueSleep /= 10; //ウェイトを減らす
            }
            valueSkip++;
        }
    }

    if (duration_cast<milliseconds>(currentTime - pastTime) > milliseconds(1000) - duration_cast<milliseconds>(FrameTime))
    { //一秒おきの処理
        LoopMax = loopCnt;
        if (LoopMax > Fps * 5)
        {
            if (valueSleep < milliseconds(1))
            {
                valueSleep += microseconds(100);
            }
        } //十分に余力がある場合ウェイトを増やす
        if (LoopMax < Fps)
        {
            if (valueSleep > microseconds(4))
            {
                valueSleep /= 4;
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