#ifndef LYRIC_H
#define LYRIC_H

#include <QVector>
#include <QString>
class Lyric
{
    public:
        Lyric();
        //获取文件
        void getFromFile(QString dir);
        //定位歌词列表行数
        QString getLineAt(int index);
        //获取数量
        int getCount();
        //获取索引
        int getIndex(qint64 pos);
        //获取歌词位置
        qint64 getPostion(int index);

    private:
        //QString singer;艺人名
        //QString title;曲名
        //QString album;专辑名
        //QString writer;编者
        QString filedir;//文件目录
        double offset;//偏移量
        QVector<qint64> postion;//位置
        QVector<QString> line;//线
};

#endif // LYRIC_H
