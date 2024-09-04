#ifndef SHAPE_H
#define SHAPE_H

struct Point2D;
struct Point3D;
struct Edge;

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