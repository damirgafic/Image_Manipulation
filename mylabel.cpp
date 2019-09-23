#include "mylabel.h"
#include "dialog.h"
#include "ui_dialog.h"
#include <iostream>
#include <tgmath.h>
#include <fstream>
#include <QMouseEvent>
#include <string>
using namespace std;
//
static int w =800;
static int h = 600;
QImage image(w, h, QImage::Format_RGB32);
char typeOf;
QRgb value;
int count = 0;

MyLabel::MyLabel(QWidget *parent) : QLabel (parent)
{

}
void MyLabel::mousePressEvent(QMouseEvent *ev){

   // std::cout<< "\n x =" << ev->x() << " y=" << ev->y();
    this->x1 = ev->x();
    this->y1 = ev->y();

}
void MyLabel::mouseReleaseEvent(QMouseEvent *ev){
   // std::cout<< "\nRelease point x =" << ev->x() << " y=" << ev->y();
    this->x2 = ev->x();
    this->y2 = ev->y();
    value = qRgb(100,110,10);
    if(typeOf=='t')
    {
        if(count<3){
            xTriangle[count] = x2;
            yTriangle[count] = y2;
            count++;
        if(count == 3)
        {
            drawTriangle();
            count = 0;
        }
        }
     }



    if(typeOf=='c') // circle object
    {
        int i=0;
        float j;
        float p;
        float xc,yc,x,y;
        float r = 0;
        xc=x1;
        yc=y1;
        x=x2;
        y=y2;

        r = sqrt(pow((xc-x),2) + pow((yc - y),2));
        j = r;
        p=(5/4)-r;
        while(i<j)
        {
            if(p<0)
                p=p+ 2*(i+1) + 1;
            else {
                p = p+2*(i+1)+1-2*(j-1);
                j = j -1;
            }
            ++i;
            x=i+x1;
            y=j+y1;
            image.setPixel(x,y,value); // x,y changed to draw all other octants
            x=-i+x1;
            y=-j+y1;
            image.setPixel(x,y,value);
            x=-j+x1;
            y=-i+y1;
            image.setPixel(x,y,value);
            x = j+x1;
            y = i+y1;
            image.setPixel(x,y,value);
            x = -i+x1;
            y = j+y1;
            image.setPixel(x,y,value);
            x = -j+x1;
            y = i+y1;
            image.setPixel(x,y,value);
            x=i+x1;
            y=-j+y1;
            image.setPixel(x,y,value);
            x=j+x1;
            y=-i+y1;
            image.setPixel(x,y,value);

            value = qRgb(0,0,255);

        }
        for(int i = 0; i<w; i++)
        {
            for(int j=0; j<h; j++)
            {

                if(pow(r,2) > pow((i-xc),2) + pow((j-yc),2))
                    image.setPixel(i,j,value);
            }
        }

        setPixmap(QPixmap::fromImage(image));
        show();
    }
    if(typeOf=='r') // rectangle object
    {


        if(x1>x2)
            std::swap(x1,x2);
        if(y1>y2)
            std::swap(y1,y2);


        for(int i=x1; i<x2;i++)
           {
                for(int j =y1; j<y2; j++){
                   image.setPixel(i,j,value); //should change pixel colors
               }
               setPixmap(QPixmap::fromImage(image));
               show();
           }
    }
    if(typeOf=='l')
    {
        drawLine();
    }
}

QImage MyLabel::clear(){
    QRgb value;
    value = qRgb(0,0,0);
    for(int i=0; i<w; i++)
    {
        for(int j =0; j<h; j++)
            image.setPixel(i,j,value);
    }
    return image;
}
void MyLabel::setType(char c){
    typeOf=c;
}

void MyLabel::drawTriangle()
{
   int i = 0; // to keep track of cordinates
   int j; // to prevent from going out of bounds
   while(i<3){
       if(i==2)
       {
           j = -1;
       }
       else {
           j=i;
       }
       int k = 0;
       float steps = 0;
       int dX,dY = 0;
       float xi,yi;
       float x,y;

       dX = xTriangle[j+1]-xTriangle[i];
       dY = yTriangle[j+1]-yTriangle[i];

       if(abs(dX)>abs(dY))
           steps = abs(dX);
       else
           steps = abs(dY);
       xi = abs(dX)/steps;
       yi = abs(dY/steps);
       x = xTriangle[i];
       y = yTriangle[i];
       if(x>=xTriangle[j+1] && y >= yTriangle[j+1]){ //downwards right slope
           xi = -(abs(xi));
           yi = -(abs(yi));
       }
       else if(x<=xTriangle[j+1] && y<=yTriangle[j+1]) // upwards left slope
       {
           xi = abs(xi);
           yi = abs(yi);
       }
       else if(x<xTriangle[j+1] && y > yTriangle[j+1]) // upwards right
       {
           xi = (abs(xi));
           yi = -(abs(yi));
       }
       else if(x>xTriangle[j+1] && y<yTriangle[j+1]) // downwards left
       {
           xi = -(abs(xi));
           yi = (abs(yi));
       }
       i++;
       do{ // step 5
           image.setPixel(round(x),round(y),value); // 5a // need to round x and y
           x = x + xi; // 5b // need to adjust +/- xi/yi depending where x/y is
           y = y + yi; // 5c
           k = k + 1; // 5c

       }while(k<steps); // step 6

       setPixmap(QPixmap::fromImage(image));
       show();
   }
   \

}
void MyLabel::drawLine()
{
    int k = 0; // loop counter for steps
    float steps = 0;
    int dX,dY = 0; // delta variables
    float xi,yi = 0;
    float x,y = 0;


    dX = x2 - x1; // step 1
    dY = y2 - y1; // step 1
    if(abs(dX) > abs(dY)) // step 2
        steps = abs(dX); // step 2
    else
        steps = abs(dY);
    xi = abs(dX)/steps; // step 3
    yi = abs(dY)/steps; // step 3
    x = x1;
    y = y1;
    if(x>=x2 && y >= y2){ //downwards right slope
        xi = -(abs(xi));
        yi = -(abs(yi));
    }
    else if(x<=x2 && y<=y2) // upwards left slope
    {
        xi = abs(xi);
        yi = abs(yi);
    }
    else if(x<x2 && y > y2) // upwards right
    {
        xi = (abs(xi));
        yi = -(abs(yi));
    }
    else if(x>x2 && y<y2) // downwards left
    {
        xi = -(abs(xi));
        yi = (abs(yi));
    }

    do{ // step 5
        image.setPixel(round(x),round(y),value); // 5a // need to round x and y
        x = x + xi; // 5b // need to adjust +/- xi/yi depending where x/y is
        y = y + yi; // 5c
        k = k + 1; // 5c

    }while(k<steps); // step 6
    setPixmap(QPixmap::fromImage(image));
    show();
}
void MyLabel::saveImage(){
    ofstream myFile;
    unsigned char r,g,b,a;

    myFile.open("image.ppm");
    myFile << "P3\n";
    myFile << w << " " << h << endl;

    cout << endl << image.pixel(10,10);
    r = int(image.pixel(10,10)) >> 16 & 0xff;
    g = int(image.pixel(10,10)) >> 8 & 0xff;
    b = int(image.pixel(10,10)) >> 0 & 0xff;
    cout << "\nr value is: " <<(int)r;
    cout << "\ng value is: " <<(int)g;
    cout << "\nb value is: " <<(int)b;


    image.save("test.ppm",nullptr,-1);
    for(int i = 0; i<w; i++){
        for(int j = 0; j<h; j++)
        {
           r = ((int) image.pixel(i,j)) >> 16 & 0xff;
           g = ((int) image.pixel(i,j)) >> 8 & 0xff;
           b = ((int) image.pixel(i,j)) >> 0 & 0xff;
           //a = ((int) image.pixel(i,j)) >> 0 & 0xff;

           myFile << (int)r << " " << (int)g << " "  << (int)b << " " << "\t ";

        }
        myFile << endl;
    }
}

void MyLabel::loadImage(){
    string type1;
    int h1,w1;
    int val;

    image.load("test.ppm", nullptr);
    setPixmap(QPixmap::fromImage(image));
    show();
    fstream inFile;
    inFile.open("C:/Users/damir/Documents/Computer Graphics/build-Assignment2-Desktop_Qt_5_13_0_MinGW_32_bit-Debug/image.ppm");
    if (!inFile) {
        cout << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    inFile >> type1 >> w1 >> h1;
    while(inFile >> val)
    {

    }


}
QImage MyLabel::getImage()
{
    return image;
}
int MyLabel::RLEcompress(unsigned char *data, int length, unsigned char *cdata){
    ofstream myFile;
    unsigned char r,g,b,a;
    int l=0;


    myFile.open("imageCompress.ppm");
    myFile << "CSUEB3\n";
    myFile << w << " " << h << endl;

     r =  (image.pixel(0,0)) >> 16 & 0xff;
     g = ( image.pixel(0,0)) >> 8 & 0xff;
     b = ( image.pixel(0,0)) >> 0 & 0xff;
    for(int i = 0; i<w; i++){

        for(int j=0;j<h;i++)
        {
            int count = 1;
            while(i < h-1 && j<w-1 && image.pixel(j,i)==image.pixel(j,i))
            {
                count++;
                j++;
            }
            r =  (image.pixel(i,j)) >> 16 & 0xff;
            myFile << (int)r << " " << count << " ";

        }
    }
    return length;
}
