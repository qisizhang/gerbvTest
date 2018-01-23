#ifndef DRAWIMAGE_H
#define DRAWIMAGE_H
#include"disposeGerber.h"

class gerberImage
{
public:
    gerberImage();
    void drawPic(QVector<outBorder*>& allBorder,QVector<gerberLine*> &allGerLine);
    void outputPic();
};
#endif // DRAWIMAGE_H
