#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Point2D {
    float x;
    float y;

    // Constructor for the Point2D struct for ease of use
    Point2D(float x, float y) : x(x), y(y) {};
};

// Struct of a 3D vector with x,y,z coordinates
struct Point3D {
    float x;
    float y;
    float z;

    // Constructor for the Point3D struct for ease of use
    Point3D(float x, float y, float z) : x(x), y(y), z(z) {};
};

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
        int shapeType;

    Shape(int shapeType) 
    {
        switch(shapeType) 
        {
            case 0:
                vertices = 
                {
                    Point3D(-1.0f, -1.0f, 1.0f), Point3D(1.0f, -1.0f, 1.0f), Point3D(1.0f, 1.0f, 1.0f), Point3D(-1.0f, 1.0f, 1.0f), 
                    Point3D(-1.0f, -1.0f, -1.0f), Point3D(1.0f, -1.0f, -1.0f), Point3D(1, 1, -1), Point3D(-1.0f, 1.0f, -1.0f) 
                };
                edges = 
                {
                    Edge(0, 1), Edge(0, 3), Edge(0, 4), Edge(1, 2), Edge(1, 5), Edge(2, 3), 
                    Edge(2, 6), Edge(3, 7), Edge(4, 5), Edge(4, 7), Edge(5, 6), Edge(6, 7) 
                };
                break;
        }
    }
};