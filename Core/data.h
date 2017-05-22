#ifndef DATA_H
#define DATA_H

#include "Core/musicinfo.h"
#include <QString>

class Data
{
    public:
        Data();
        //连接数据
        static bool connectData();
        //尝试连接列表
        static void tryConnectListList();
        //得到列表
        static QQueue <QString> getListList();
        //添加列表
        static bool addList(QString name);
        //删除列表
        static void deleteList(QString name);
        //获取列表ID
        static int getListId(QString name);

        //尝试连接列表
        static void tryConnectList(QString listName);
        //获取音乐名字
        static QString getMusicName(QString listName, int id);
        //获取音乐目录
        static QString getMusicDir(QString listName, int id);
        //获取音乐列表
        static QQueue <MusicInfo> getMusicList(QString listName);
        //添加音乐到列表后面
        static void addMusicsToEnd(QString listName, QQueue<MusicInfo> musics);
        //删除音乐
        static void deleteMusic(QString listName, int row);
        //清空所有音乐
        static void deleteAllMusic(QString listName);
        //尝试连接基础信息
        static void tryConnectBaseInfo();
        //获取列表数量
        static int getListCount();
        //改变列表数量
        static void changeListCount(int cnt);
        //获取当前背景
        static QString getCurrentBackground();
        //改变当前背景
        static void changeCurrentBackground(QString dir);
        //获取音量
        static int getSoundLevel();
        //改变音量
        static void changeSoundLevel(int voice);
        //获取播放模式
        static int getPlayMode();
        //改变音量模式
        static void changePlayMode(int mode);
};

#endif // DATA_H
