#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Parameters
const int WIDTH = 800, HEIGHT = 600;
const int scale = 100;
const float focalLength = 5.0f;

// 2D Vector struct
struct Point2D {
    float x;
    float y;

    // Constructor for the Point2D struct for ease of use
    Point2D(float x, float y) : x(x), y(y) {};
};

// 3D Vector struct
struct Point3D {
    float x;
    float y;
    float z;

    // Constructor for the Point3D struct for ease of use
    Point3D(float x, float y, float z) : x(x), y(y), z(z) {};
};

// Edge struct, with first and second vertex defined
struct Edge {
    int vertexOne;
    int vertexTwo;

    // Constructor for the Edge struct for ease of use
    Edge(int vertexOne, int vertexTwo) : vertexOne(vertexOne), vertexTwo(vertexTwo) {};
};

class Shape
{
    public:
        vector<Point3D> vertices;
        vector<Edge> edges;

    // Default constructor
    Shape() {}

    // Constructor based on called shape type
    /*
        Shapes:
        0 -> Cube
    */
    Shape(int shapeType) 
    {
        switch(shapeType) 
        {
            // Cube
            case 0:
                this->vertices = 
                {
                    Point3D(-1.0f, -1.0f, 1.0f), Point3D(1.0f, -1.0f, 1.0f), Point3D(1.0f, 1.0f, 1.0f), Point3D(-1.0f, 1.0f, 1.0f), 
                    Point3D(-1.0f, -1.0f, -1.0f), Point3D(1.0f, -1.0f, -1.0f), Point3D(1, 1, -1), Point3D(-1.0f, 1.0f, -1.0f) 
                };
                this->edges = 
                {
                    Edge(0, 1), Edge(0, 3), Edge(0, 4), Edge(1, 2), Edge(1, 5), Edge(2, 3), 
                    Edge(2, 6), Edge(3, 7), Edge(4, 5), Edge(4, 7), Edge(5, 6), Edge(6, 7) 
                };
                break;
        }
    }

    // Transform a 3D point into a 2D one through weak-perspective projection.
    // Formula: Px/Py = X/Y * Fov / Fov + Z
    Point2D projectPoint(Point3D point)
    {
        Point2D returnPoint = Point2D(0, 0);
        returnPoint.x = (WIDTH / 2) + (point.x * focalLength) / (focalLength + point.z) * scale;
        returnPoint.y = (HEIGHT / 2) + (point.y * focalLength) / (focalLength + point.z) * scale;

        return returnPoint;
    }

    // Returns the 3D point after it has been returned in the rotation angle in the y axis.
    // Rotation done through matrix multiplication
    Point3D rotateShapeY(Point3D point, float rotation) 
    {
        Point3D returnPoint = Point3D(0, 0, 0);
        returnPoint.x = cos(rotation) * point.x - sin(rotation) * point.z;
        returnPoint.y = point.y;
        returnPoint.z = sin(rotation) * point.x + cos(rotation) * point.z;

        return returnPoint;
    }

    // Returns the 3D point after it has been returned in the rotation angle in the x axis.
    // Rotation done through matrix multiplication
    Point3D rotateShapeX(Point3D point, float rotation) 
    {
        Point3D returnPoint = Point3D(0, 0, 0);
        returnPoint.y = cos(rotation) * point.y - sin(rotation) * point.z;
        returnPoint.x = point.x;
        returnPoint.z = sin(rotation) * point.y + cos(rotation) * point.z;

        return returnPoint;
    }
};