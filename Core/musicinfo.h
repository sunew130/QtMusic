#ifndef MUSICINFO_H
#define MUSICINFO_H

#include <QString>

class MusicInfo
{
    public:
        MusicInfo();
        //设置目录
        void setDir(QString dirStr) {dir = dirStr;}
        //设置歌曲名字
        void setName(QString nameStr) {name = nameStr;}
        //设置歌手
        void setArtist(QString artistStr) {artist = artistStr;}
        //获取目录
        QString getDir() {return dir;}
        //获取名字
        QString getName() {return name;}
        //获取歌手
        QString getArtist() {return artist;}

    private:
        QString dir;//目录
        QString name;//名字
        QString artist;//歌手
};

#endif // MUSICINFO_H
