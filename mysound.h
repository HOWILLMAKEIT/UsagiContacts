#ifndef MYSOUND_H
#define MYSOUND_H

#include <QObject>
#include<QSoundEffect>
class MySound : public QObject
{
    Q_OBJECT
public:
    explicit MySound(QObject *parent = nullptr);
    QSoundEffect  ha ;
    QSoundEffect  highest_yaha ;
    QSoundEffect  yaha ;
    QSoundEffect  wula;
    QSoundEffect  wulayaha;
signals:
};

#endif // MYSOUND_H
