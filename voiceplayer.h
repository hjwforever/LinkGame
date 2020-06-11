#ifndef VOICEPLAYER_H
#define VOICEPLAYER_H

#include <QtMultimedia/QMediaPlayer>
#include<QtMultimedia/QMediaPlaylist>
#include<iostream>
#include<QSound>

using namespace std;

class VoicePlayer
{
public:
    VoicePlayer();
    QMediaPlayer *gameSound_BGM ;    //创建背景音乐播放器
    QMediaPlaylist *gameList_BGM;       //创建背景音乐播放链表
    QMediaPlayer *gameSound_Voice ;   //创建其他音效播放器
    QMediaPlaylist *gameList_Voice;      //创建其他音效播放链表
    void Play_BGM();                               //播放背景音乐
    void Pause_BGM();                            //暂停播放背景音乐
    void Play_Voice(int i);                       //播放点击按钮或消除音效
    void Play_Music(int i);
    void Stop_Voice();
    QString url;
    QSound *music;
};

#endif // VOICEPLAYER_H
