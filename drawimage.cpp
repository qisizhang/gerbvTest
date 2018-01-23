#include"drawimage.h"
#include<QPainter>
#include<QPainterPath>
#include<QPixmap>
#include<QDebug>
#include<QtMath>

gerberImage::gerberImage()
{

}

void gerberImage::drawPic(QVector<outBorder*> &allBorder,QVector<gerberLine*> &allGerLine)
{
    qDebug()<<"contiue";
//    QPixmap* pix=new QPixmap(QSize(300,300));
//    pix->fill(Qt::black);
    //QVector<gerberLine*> allGerLine;
    QImage image(1200,1200, QImage::QImage::Format_RGB32);

    QPainter p(&image);
    p.setPen(Qt::red);
    p.translate(600,600);
    p.rotate(-90);
    for(int i=0;i<allBorder.size();i++)
    {
        QPainterPath pp1;
        outBorder* oneBorder=allBorder[i];
        while(oneBorder)
        {
            if(oneBorder->D==D02)
            {
                pp1.moveTo(oneBorder->X,oneBorder->Y);
            }
            else if(oneBorder->D==D01)
            {
                pp1.lineTo(oneBorder->X,oneBorder->Y);
            }
            oneBorder=oneBorder->next;
        }
        p.drawPath(pp1);
    }
    for(int i=0;i<allGerLine.size();i++)
    {
        QPainterPath pp2;
        gerberLine* oneLine=allGerLine[i];
        while(oneLine)
        {
            if(oneLine->I==0&&oneLine->J==0)
            {
                if(oneLine->D==D02)
                {
                    pp2.moveTo(oneLine->X,oneLine->Y);
                }
                else if(oneLine->D==D01)
                {
                    pp2.lineTo(oneLine->X,oneLine->Y);
                }
            }
            else if(oneLine->I!=0||oneLine->J!=0)
            {
                double i=oneLine->I;
                double j=oneLine->J;
                double x=oneLine->X;
                double y=oneLine->Y;
                gerberLine* lastPoint=oneLine->last;
                double lastx=lastPoint->X;
                double lasty=lastPoint->Y;
                double radius=qSqrt(i*i+j*j);
                if(oneLine->bigG==G75)
                {
                    //QPoint ltCenter(lastx+i-radius,lasty+j+radius);
                    QRectF rect(lastx+i-radius,lasty+j+radius,2*radius,2*radius);
                    double startAngle=qAsin(-j/radius);
                    if(-i<=0&&-j>=0)
                        startAngle=qFabs(startAngle)+90;
                    if(-i<=0&&-j<=0)
                        startAngle=qFabs(startAngle)+180;
                    if(-i>=0&&-j<=0)
                        startAngle=qFabs(startAngle)+270;
                    double sweepLength=qAsin((y-lasty-j)/radius);
                    if((x-lastx-i)<=0&&(y-lasty-j)>=0)
                        sweepLength=qFabs(sweepLength)+90;
                    if((x-lastx-i)<=0&&(y-lasty-j)<=0)
                        sweepLength=qFabs(sweepLength)+180;
                    if((x-lastx-i)>=0&&(y-lasty-j)<=0)
                        sweepLength=qFabs(sweepLength)+270;

                    sweepLength=sweepLength-startAngle;
                    pp2.arcTo(rect,startAngle,sweepLength);
                }

            }
            oneLine=oneLine->next;
        }
        p.drawPath(pp2);
    }
    image.save("D:/gerber123456.png");
    qDebug()<<"sucess";
}

void gerberImage::outputPic()
{

}

