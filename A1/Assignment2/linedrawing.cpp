#include "linedrawing.h"
#include <math.h>

linedrawing::linedrawing()
{
}
 QImage image(1920, 1080, QImage::Format_RGB888);
 QRgb v = qRgb(0,0,0);

    int linedrawing::sign(float a)
    {
        if(a>0)
        {
            return 1;
        }
        else if(a<0)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

    void linedrawing::dda_linedraw(int x1,int y1,int x2,int y2)
    {
        float length;
        if(abs(x2-x1)>abs(y2-y1))
        {
            length = abs(x2-x1);
        }
        else
        {
            length = abs(y2-y1);
        }

        float dx,dy;
        dx = (float)((x2 - x1)/length);
        dy = (float)((y2 - y1)/length);

        float x,y;
        x = x1 + (0.5 * sign(dx));
        y = y1 + (0.5 * sign(dy));

        int i = 0;
        while(i < length){
            image.setPixel(floor(x),floor(y),qRgb(255,255,255));
            x = x + dx;
            y = y + dy;
            i++;
        }

    }

    void linedrawing::bresenems(int x1,int y1,int x2,int y2)
    {
        int i = 0;
        int x = x1;
        int y = y1;
        int intercg;
        int del_x = abs(x2-x1);
        int del_y = abs(y2-y1);
        int s1 = sign(x2-x1);
        int s2 = sign(y2-y1);

        if(del_y > del_x){
            int temp;
            temp = del_x;
            del_x = del_y;
            del_y = temp;
            intercg = 1;
        }
        else{
            intercg = 0;
        }

        float eb = 2*del_y - del_x;

        for(i = 1; i<del_x ;i++){
            image.setPixel(floor(x),floor(y),qRgb(255,255,255));
            while(eb >= 0){
                if (intercg == 1){
                    x = x + s1;
                }
                else{
                    y = y + s2;
                }
                eb = eb - (2*del_x);
            }
            if (intercg == 1){
                y = y + s2;
            }
            else{
                x = x + s1;
            }
            eb = eb + (2*del_y);
        }
        image.setPixel(floor(x2),floor(y2),qRgb(255,255,255));
    }

    QImage linedrawing::retImage(){
        return image;
    }



