#include "voiceplayer.h"

VoicePlayer::VoicePlayer()
{
    //背景音乐
    //创建播放器
    gameSound_BGM = new QMediaPlayer;
    //创建播放列表
    gameList_BGM = new QMediaPlaylist;
    //添加音乐
    gameList_BGM->addMedia(QUrl("qrc:/voice/BGM/music1.mp3"));
    gameList_BGM->addMedia(QUrl("qrc:/voice/BGM/music2.mp3"));
    gameList_BGM->addMedia(QUrl("qrc:/voice/BGM/music3.mp3"));
    gameList_BGM->addMedia(QUrl("qrc:/voice/BGM/music4.mp3"));
    gameList_BGM->addMedia(QUrl("qrc:/voice/BGM/music5.mp3"));
    //循环播放
    //gameList_BGM->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    gameSound_BGM->setPlaylist(gameList_BGM);
    gameSound_BGM->setVolume(20);
    //按钮及消除音效
    //创建播放器
    //创建播放列表
    gameSound_Voice = new QMediaPlayer;
    gameList_Voice = new QMediaPlaylist;
}

void VoicePlayer::Play_BGM()
{
    gameSound_BGM->play();
}

void VoicePlayer::Pause_BGM()
{
    gameSound_BGM->pause();
}

void VoicePlayer::Play_Voice(int i)
{
    QString url="qrc:/voice/button_Sound/sound.mp3";
    url.insert(29,QString::number(i));
    //cout<<url.toStdString()<<endl;
    gameList_Voice->addMedia(QUrl(url));
    gameList_Voice->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);//播放一次
    gameSound_Voice->setPlaylist(gameList_Voice);
    gameSound_Voice->setVolume(30);
    gameSound_Voice->play();
}

void VoicePlayer::Play_Music(int i){
    gameList_BGM->setCurrentIndex(i);
}

void VoicePlayer::Stop_Voice(){
    gameSound_BGM->stop();
}
