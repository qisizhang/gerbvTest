#include"disposeGerber.h"
#include<stdio.h>
#include<sstream>
#include<QDebug>
#include<QFileInfo>
gerberFile::gerberFile()
{

}

fileinfo* gerberFile::openGerber(const QString &filename)
{
    fileinfo* gerberFile=(fileinfo*)malloc(sizeof(fileinfo));
    QFile* gf=new QFile(filename);
    if (!gf->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"error!";
            return NULL;
        }
//        QTextStream in(gf);
//          while (!in.atEnd())
//          {
//              QString line = in.readLine();
//              qDebug()<<line;

//          }
     QFileInfo info(*gf);
//     qDebug()<<"size:"<<info.size();
    //gerberFile->ptr=0;
    gerberFile->fileSize=info.size();
    //gerberFile->data=NULL;
    gerberFile->gerberFile=gf;
    return gerberFile;
}

void gerberFile::getGerData(fileinfo* gf)
{
//    QVector<outBorder*> allBorder;
//    QVector<gerberLine*> allGerLine;
    QFile* fg=gf->gerberFile;
    QTextStream in(fg);
    //int pos=0;
    while(!in.atEnd())
    {
        QString line=in.readLine();
        if(line.left(1)=="X"||line.left(3)=="G01")
        {
            gerberLine* singleLine=(gerberLine*)malloc(sizeof(gerberLine));
            singleLine->D=D02;
            singleLine->smlG=G01;
            singleLine->bigG=NOBIG;
            singleLine->next=NULL;
            singleLine->last=NULL;
            singleLine->X=0;
            singleLine->Y=0;
            singleLine->I=0;
            singleLine->J=0;
            QString nextLine=line;
            //while(!nextLine.left(3)=="G36")
            for(nextLine;nextLine.left(3)!="G36";nextLine=in.readLine())
            {
                if(nextLine!="G75*")
                {
                    if(!nextLine.contains('I')&&!nextLine.contains('J'))
                    {
                    gerberLine* nextGerLine=(gerberLine*)malloc(sizeof(gerberLine));
                    nextGerLine->I=0.0;
                    nextGerLine->J=0.0;
                    nextGerLine->smlG=G01;
                    nextGerLine->bigG=NOBIG;
                    int x=nextLine.indexOf('X');
                    int y=nextLine.indexOf('Y');
                    int d=nextLine.indexOf('D');
                    int star=nextLine.indexOf('*');
                    QString strx=nextLine.mid(x+1,y-x-1);
                    QString stry=nextLine.mid(y+1,d-y-1);
                    QString dCode=nextLine.mid(d+1,star-d-1);
                    if(dCode=="01")
                        nextGerLine->D=D01;
                    else if(dCode=="02")
                        nextGerLine->D=D02;
                    nextGerLine->X=strx.toDouble()/1000*2;
                    nextGerLine->Y=stry.toDouble()/1000*2;
                    //qDebug()<<"NOBIGX:"<<nextGerLine->X;
                    gerberLine* subLine=singleLine;
                    while(subLine->next)
                        subLine=subLine->next;
                    subLine->next=nextGerLine;
                    nextGerLine->last=subLine;
                    nextGerLine->next=NULL;
                    }
                    else if(nextLine.contains("I")||nextLine.contains("J"))
                    {
                        if(nextLine.left(1)=="G")
                        {
                        gerberLine* nextGerLine=(gerberLine*)malloc(sizeof(gerberLine));
                        nextGerLine->bigG=G74;

                        int x=nextLine.indexOf('X');
                        int y=nextLine.indexOf('Y');
                        int i=nextLine.indexOf(('I'));
                        int j=nextLine.indexOf(('J'));
                        int d=nextLine.indexOf('D');
                        int g=nextLine.indexOf('G');
                        int star=nextLine.indexOf('*');
                        QString strx=nextLine.mid(x+1,y-x-1);
                        QString stry=nextLine.mid(y+1,i-y-1);
                        QString stri=nextLine.mid(i+1,j-i-1);
                        QString strj=nextLine.mid(j+1,d-j-1);
                        QString dCode=nextLine.mid(d+1,star-d-1);
                        QString gCode=nextLine.mid(g+1,x-g-1);
                        if(dCode=="01")
                            nextGerLine->D=D01;
                        else if(dCode=="02")
                            nextGerLine->D=D02;
                        if(gCode=="02")
                            nextGerLine->smlG=G02;
                        else if(gCode=="03")
                            nextGerLine->smlG=G03;
                        nextGerLine->X=strx.toDouble()/1000*2;
                        nextGerLine->Y=stry.toDouble()/1000*2;
                        nextGerLine->I=stri.toDouble()/1000*2;
                          qDebug()<<"G74I:"<<nextGerLine->I;
                        nextGerLine->J=strj.toDouble()/1000*2;
                        qDebug()<<"G74J:"<<nextGerLine->I;
                        gerberLine* subLine=singleLine;
                        while(subLine->next)
                            subLine=subLine->next;
                        subLine->next=nextGerLine;
                        nextGerLine->last=subLine;
                        nextGerLine->next=NULL;
                        }
                    }
                }
                else if(nextLine=="G75*")
                {
                    for(nextLine=in.readLine();nextLine!="G74*";nextLine=in.readLine())
                    {
                        gerberLine* nextGerLine=(gerberLine*)malloc(sizeof(gerberLine));
                        nextGerLine->bigG=G75;

                        int x=nextLine.indexOf('X');
                        int y=nextLine.indexOf('Y');
                        int i=nextLine.indexOf(('I'));
                        int j=nextLine.indexOf(('J'));
                        int d=nextLine.indexOf('D');
                        int g=nextLine.indexOf('G');
                        int star=nextLine.indexOf('*');
                        QString strx=nextLine.mid(x+1,y-x-1);
                        QString stry=nextLine.mid(y+1,i-y-1);
                        QString stri=nextLine.mid(i+1,j-i-1);
                        QString strj=nextLine.mid(j+1,d-j-1);
                        QString dCode=nextLine.mid(d+1,star-d-1);
                        QString gCode=nextLine.mid(g+1,x-g-1);
                        if(dCode=="01")
                            nextGerLine->D=D01;
                        else if(dCode=="02")
                            nextGerLine->D=D02;
                        if(gCode=="02")
                            nextGerLine->smlG=G02;
                        else if(gCode=="03")
                            nextGerLine->smlG=G03;
                        nextGerLine->X=strx.toDouble()/1000*2;
                        //qDebug()<<"G75X:"<<nextGerLine->X;
                        nextGerLine->Y=stry.toDouble()/1000*2;
                        //qDebug()<<"G75Y:"<<nextGerLine->Y;
                        nextGerLine->I=stri.toDouble()/1000*2;
                        //qDebug()<<"G75I:"<<nextGerLine->I;
                        nextGerLine->J=strj.toDouble()/1000*2;
                        //qDebug()<<"G75J:"<<nextGerLine->J;
                        gerberLine* subLine=singleLine;
                        while(subLine->next)
                            subLine=subLine->next;
                        subLine->next=nextGerLine;
                        nextGerLine->last=subLine;
                        nextGerLine->next=NULL;
                    }
                }
            }
            allGerLine.append(singleLine);
            qDebug()<<nextLine;
            line=nextLine;
        }

        if(line.left(3)=="G36")
        {
            outBorder* singleBorder=(outBorder*)malloc(sizeof(outBorder));
            singleBorder->D=D02;
            singleBorder->next=NULL;
            singleBorder->X=0;
            singleBorder->Y=0;
            for(QString nextLine=in.readLine();nextLine.left(3)!="G37";nextLine=in.readLine())
            {
                if(nextLine.right(4)=="D02*"&&!nextLine.contains("I")&&!nextLine.contains("J"))
                {
                    outBorder* nextBorder=(outBorder*)malloc(sizeof(outBorder));
                    nextBorder->D=D02;
                    int x=nextLine.indexOf('X');
                    int y=nextLine.indexOf('Y');
                    int d=nextLine.indexOf('D');
                    QString strx=nextLine.mid(x+1,y-x-1);
                    QString stry=nextLine.mid(y+1,d-y-1);
                    nextBorder->X=strx.toDouble()/1000*2;
                    //qDebug()<<"G3637X:"<<nextBorder->X;
                    nextBorder->Y=stry.toDouble()/1000*2;

                    outBorder* subBorder=singleBorder;
                    while(subBorder->next)
                        subBorder=subBorder->next;
                    subBorder->next=nextBorder;
                    nextBorder->next=NULL;

                }
                else if(nextLine.right(4)=="D01*"&&!nextLine.contains("I")&&!nextLine.contains("J"))
                {
                    outBorder* nextBorder=(outBorder*)malloc(sizeof(outBorder));
                    nextBorder->D=D01;
                    int x=nextLine.indexOf('X');
                    int y=nextLine.indexOf('Y');
                    int d=nextLine.indexOf('D');
                    QString strx=nextLine.mid(x+1,y-x-1);
                    QString stry=nextLine.mid(y+1,d-y-1);
                    //qDebug()<<"D01:"<<strx<<":"<<stry;
                    nextBorder->X=strx.toDouble()/1000*2;
                    nextBorder->Y=stry.toDouble()/1000*2;

                    outBorder* subBorder=singleBorder;
                    while(subBorder->next)
                        subBorder=subBorder->next;
                    subBorder->next=nextBorder;
                    nextBorder->next=NULL;
                }
                else{
                        continue;
                    }

            }
            allBorder.append(singleBorder);
        }
    }
    gf->gerberFile->close();
/*    item[0]=allBorder;
    item[1]=allGerLine;
    imageItem.append(item)*/;
//    imageItem.append(allGerLine);
//    return imageItem;
}

