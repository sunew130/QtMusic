#include "myplayer.h"
#include "Core/playmode.h"
#include <QMediaContent>
#include <QTime>

MyPlayer::MyPlayer()
{
    playerState = NOMUSIC;
    connect(&player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(playNext(QMediaPlayer::MediaStatus)));
    connect(&player, SIGNAL(durationChanged(qint64)), this, SIGNAL(durationChanged(qint64)));
    connect(&player, SIGNAL(durationChanged(qint64)), this, SLOT(musicChanged()));
    connect(&player, SIGNAL(positionChanged(qint64)), this, SIGNAL(positionChanged(qint64)));
    connect(this, SIGNAL(playerStateChanged(int)), this, SLOT(stateChanged(int)));
}

//播放
void MyPlayer::setPlay()
{
    player.play();
    emit playerStateChanged(PLAYING);
}

//暂停
void MyPlayer::setPause()
{
    player.pause();
    emit playerStateChanged(PAUSE);
}

//改变音乐
void MyPlayer::musicChanged()
{
    emit musicChanged(currentList, currentindex);
}

//获取当前播放状态
int MyPlayer::getPlayerState()
{
    return this->playerState;
}


//改变播放状态
void MyPlayer::stateChanged(int state)
{
    this->playerState = state;
}

//设置音量
void MyPlayer::setVoice(int voice)
{
    this->player.setVolume(voice);
}


//设置播放模式
void MyPlayer::setPlayMode(int mode)
{
    this->playMode = mode;
}

//拖拽播放位置
void MyPlayer::setPosition(qint64 pos)
{
    player.setPosition(pos);
}

//添加音乐
void MyPlayer::addMusics(QString name, QQueue<MusicInfo> q)
{
    MusicInfo musicInfo;
    while (!q.empty())
    {
        musicInfo = q.front();
        q.pop_front();
        list[name].push_back(QUrl::fromLocalFile(musicInfo.getDir()));
    }
}


//删除音乐
void MyPlayer::removeTheMusic(QString listName, int index)
{
    list[listName].removeAt(index);
    if (listName == currentList && index == currentindex)
    {
        player.stop();
        emit musicNotAvailable();
        emit playerStateChanged(NOMUSIC);
    }
}

//删除所有音乐
void MyPlayer::removeAllMusics(QString listName)
{
    list[listName].clear();
    if (list[currentList].size() == 0)
    {
        player.stop();
        emit musicNotAvailable();
        emit playerStateChanged(NOMUSIC);
    }
}

//设置当前索引
void MyPlayer::setCurrentIndex(int index)
{
    this->currentindex = index;
    this->player.setMedia(QMediaContent(list[currentList][index]));
}

//获取当前索引
int MyPlayer::getCurrentIndex()
{
    return this->currentindex;
}

//获取当前列表的音乐总数
int MyPlayer::mediaCount()
{
    return this->list[currentList].size();
}

//添加媒体
void MyPlayer::addMedia(QString listName, QUrl url)
{
    this->list[listName].push_back(url);
}

//清空列表
void MyPlayer::clear(QString listName)
{
    this->list[listName].clear();
    if (list[currentList].size() == 0)
        player.stop();
}


//播放下一首
void MyPlayer::playNext(QMediaPlayer::MediaStatus state)
{
    if (!(state == QMediaPlayer::EndOfMedia))
        return;
    switch (playMode)
    {
        case CurrentItemOnce:
            player.stop();
            emit playerStateChanged(PAUSE);
            break;
        case CurrentItemInLoop:
            player.play();
            emit playerStateChanged(PLAYING);
            break;
        case Sequential:
            currentindex++;
            if (currentindex < list[currentList].size())
            {
                setCurrentIndex(currentindex);
                player.play();
                emit playerStateChanged(PLAYING);
            }
            else
            {
                currentindex--;
                player.stop();
                emit playerStateChanged(PAUSE);
            }
            break;
        case Loop:
            currentindex++;
            if (currentindex < list[currentList].size())
            {
                setCurrentIndex(currentindex);
                player.play();
                emit playerStateChanged(PLAYING);
            }
            else
            {
                currentindex = 0;
                setCurrentIndex(currentindex);
                player.play();
                emit playerStateChanged(PLAYING);
            }
            break;
        case Random:
            QTime time;
            time = QTime::currentTime();
            qsrand(time.msec()+time.second()*1000);
            currentindex = qrand()%list[currentList].size();
            setCurrentIndex(currentindex);
            player.play();
            emit playerStateChanged(PLAYING);
            break;
    }
}

//播放当前音乐
void MyPlayer::playTheMusic(QString listName, int index)
{
    currentList = listName;
    this->setCurrentIndex(index);
    player.play();
    emit playerStateChanged(PLAYING);
}

//播放上一首
bool MyPlayer::playPre()
{
    if (this->mediaCount() == 0)
        return false;
    int index = this->getCurrentIndex();
    if(--index <= 0)
        index=0;
    this->setCurrentIndex(index);
    player.play();
    emit playerStateChanged(PLAYING);
    return true;
}

//播放下一首
bool MyPlayer::playNext()
{
    if (this->mediaCount() == 0)
        return false;
    int index = this->getCurrentIndex();
    if(++index == this->mediaCount())
        index=0;
    this->setCurrentIndex(index);
    player.play();
    emit playerStateChanged(PLAYING);
    return true;
}

//播放
void MyPlayer::play()
{
    player.play();
    emit playerStateChanged(PLAYING);
}


//暂停
void MyPlayer::pause()
{
    player.pause();
    emit playerStateChanged(PAUSE);
}
