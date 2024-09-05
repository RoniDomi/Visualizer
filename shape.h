#ifndef SHAPE_H
#define SHAPE_H

struct Point2D
{
    float x;
    float y;
};
struct Point3D
{
    float x;
    float y;
    float z;
};
struct Edge
{
    int vertexOne;
    int vertexTwo;
};

class Shape
{
    public:
        Shape();
        Shape(int shapeType);
        Point2D projectPoint(Point3D point);
        Point3D rotateShapeY(Point3D point, float rotation);
        Point3D rotateShapeX(Point3D point, float rotation);
    protected:
    private:
};

#endif