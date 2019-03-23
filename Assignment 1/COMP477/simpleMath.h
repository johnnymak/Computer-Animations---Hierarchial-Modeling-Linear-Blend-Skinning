#ifndef SIMPLEMATH_H
#define SIMPLEMATH_H
//Vectors
struct Vec3
{
    double x, y, z;
    Vec3() {x=0; y=0; z=0;}
    Vec3(double a, double b, double c):x(a),y(b),z(c){}
};

struct Vec4
{
    double x, y, z, w;
    Vec4() {x=0; y=0; z=0; w=0;}
    Vec4(double a, double b, double c, double d):x(a),y(b),z(c),w(d){}
};

struct Vec2
{
    double x, y;
    Vec2() {x=0; y=0;}
    Vec2(double a, double b):x(a),y(b){}
};

struct Mat3
{
    double values[9];
    Mat3()
    {
        for (unsigned i=0; i<9; i++)
            values[i]=0;
    }
};

struct Mat4
{
    double values[16];
    Mat4()
    {
        for (unsigned i=0; i<16; i++)
            values[i]=0;
    }
};


//Vector operations
double dot2(Vec2 a, Vec2 b);

double dot3(Vec3 a, Vec3 b);

double dot4(Vec4 a, Vec4 b);


#endif
