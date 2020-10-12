#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel(QWidget *parent = nullptr);
    QImage clear();
    void mouseReleaseEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void calcCircleCoord(int i, int j, int x1, int y1, QRgb value);
    void setType(char c);
    void drawTriangle();
    void drawLine();
    void saveImage();
    void loadImage();
    int RLEcompress(unsigned char *data,int length, unsigned char *cdata);
    int RLEdecompress(unsigned char *cdata, int length, unsigned char *data);
    QImage getImage();
   // int x1,y1,x2,y2;
private:
    int x1,y1,x2,y2;
    int count = 0;
    int pointNum;
    int xTriangle[2];
    int yTriangle[2];



};

#endif // MYLABEL_H
