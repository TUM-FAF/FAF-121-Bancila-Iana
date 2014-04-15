
#ifndef BALL_H
#define BALL_H

#include <windows.h>

typedef struct _RECTD       // rc
{
    double left;
    double top;
    double right;
    double bottom;
} RECTD;

typedef struct RGBv
{
    int Red;	    // red component of color
    int Green;	    // green component of color
    int Blue;	    // blue component of color
} RGBv;

class Bubble
{
    public:
        double Diameter;
        int Size;
        RECTD Coord;
        float Direction;      // Degrees
        RGBv Color;

        Bubble()
        {
            // Setting the default color to (white)
            Color.Red = 0;
            Color.Green = 0;
            Color.Blue = 255;
        }
};

#endif // BALL_H
