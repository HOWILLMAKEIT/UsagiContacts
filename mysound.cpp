#include "mysound.h"

MySound::MySound(QObject *parent)
    : QObject{parent}
{
    ha.setSource(QUrl::fromLocalFile(":/sound/ha.wav"));
    ha.setLoopCount(1);  //循环次数
    ha.setVolume(0.25f); //音量  0~1之间

    highest_yaha.setSource(QUrl::fromLocalFile(":/sound/highest_yaha.wav"));
    highest_yaha.setLoopCount(1);
    highest_yaha.setVolume(0.25f);

    yaha.setSource(QUrl::fromLocalFile(":/sound/yaha.wav"));
    yaha.setLoopCount(1);
    yaha.setVolume(0.25f);

    wula.setSource(QUrl::fromLocalFile(":/sound/wuda.wav"));
    wula.setLoopCount(1);
    wula.setVolume(0.25f);

    wulayaha.setSource(QUrl::fromLocalFile(":/sound/wulayahayahawula.wav"));
    wulayaha.setLoopCount(1);
    wulayaha.setVolume(0.25f);
}
