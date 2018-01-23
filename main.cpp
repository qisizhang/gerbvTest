#include <QCoreApplication>
#include<QDebug>
#include"drawimage.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

     gerberFile* newFile=new gerberFile();
    fileinfo* fg=newFile->openGerber("D:/SC030W1601008.GBX");
    newFile->getGerData(fg);
    QVector<outBorder*> border=newFile->allBorder;
    QVector<gerberLine*> Line=newFile->allGerLine;
    qDebug()<<"bordersize:"<<border.size();
    qDebug()<<"linesize:"<<Line.size();
    //QVector<QVector> all=getBorderData(fg);
    gerberImage* gerImg=new gerberImage();
    gerImg->drawPic(border,Line);
    //qDebug()<<"size:"<<all.size();
    free(fg);
    fg=NULL;

    return a.exec();
}
