#ifndef MYPLAYER_H
#define MYPLAYER_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QQueue>
#include <QUrl>
#include <QMediaPlayer>
#include "Core/musicinfo.h"

class MyPlayer : public QObject
{
        Q_OBJECT

    public:
        //播放状态
        enum PlyaerState
        {
            NOMUSIC,//无音乐
            PAUSE,//暂停
            PLAYING//正在播放
        };

    public:
        MyPlayer();
        //设置播放
        void setPlay();
        //设置暂停
        void setPause();
        //设置当前曲目
        void setCurrentIndex(int index);
        //获取当前曲目
        int getCurrentIndex();
        //获取播放状态
        int getPlayerState();
        //媒体总数
        int mediaCount();
        //添加媒体
        void addMedia(QString listName, QUrl url);
        //清空列表
        void clear(QString listName);

    public slots:
        //设置音量
        void setVoice(int voice);
        //设置播放模式
        void setPlayMode(int mode);
        //添加音乐
        void addMusics(QString name, QQueue<MusicInfo> q);
        //删除音乐
        void removeTheMusic(QString listName, int index);
        //删除所有音乐
        void removeAllMusics(QString listName);
        //设置位置
        void setPosition(qint64 pos);
        //播放下一首
        void playNext(QMediaPlayer::MediaStatus state);
        //播放音乐
        void playTheMusic(QString listName, int index);
        //播放上一首
        bool playPre();
        //播放下一首
        bool playNext();
        //播放
        void play();
        //暂停
        void pause();

    private slots:
        //音乐改变
        void musicChanged();
        //音乐状态
        void stateChanged(int state);

    signals:
        //持续时间
        void durationChanged(qint64);
        //音乐改变
        void musicChanged(QString listName, int index);
        //播放位置改变
        void positionChanged(qint64);
        //音乐不允许
        void musicNotAvailable();
        //改变播放状态
        void playerStateChanged(int state);

    private:
        QMediaPlayer player;//播放类
        QString currentList;//当前列表
        QMap<QString, QVector <QUrl> > list;//列表映射
        int playMode;//播放模式
        int currentindex;//当前索引
        int playerState;//播放状态
};

#endif // MYPLAYER_H
