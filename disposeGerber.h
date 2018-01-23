#ifndef PARSEGERBER_H
#define PARSEGERBER_H
#include<QFile>
#include<QVector>

typedef struct file
{
    QFile* gerberFile;
    //char* data;
    //int ptr;
    int fileSize;
}fileinfo;

typedef enum
{
    D01,D02,D03
}D_pointMotion;

typedef enum
{
    G01,G02,G03,G74,G75,NOBIG
}G_pointMotion;

struct outBorder
{
   double X;
   double Y;
   D_pointMotion D;
   outBorder* next;
};

struct gerberLine
{
    double X;
    double Y;
    double I;
    double J;
    D_pointMotion D;
    G_pointMotion smlG;
    G_pointMotion bigG;
    gerberLine* next;
    gerberLine* last;
};
class gerberFile{
public:
    gerberFile ();
    ~gerberFile ();
    fileinfo* openGerber(const QString &filename);
    void getGerData(fileinfo* gf);
    //void getLineData(fileinfo* gf);
    QVector<outBorder*> allBorder;
    QVector<gerberLine*> allGerLine;
};

#endif // PARSEGERBER_H
