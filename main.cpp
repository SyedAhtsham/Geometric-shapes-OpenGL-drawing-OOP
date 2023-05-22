#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>

#include <GLUT/glut.h>
#include<iostream>
#include<math.h>
using namespace std;


struct Point{
    
    int x, y;
    
    Point(int xx, int yy)
    {
        x = xx;
        y = yy;
    }
    Point(const Point& p)
    {
        x = p.x;
        y = p.y;
    }
};


void drawLineInt(Point p1, Point p2)
{
    glLineWidth(4.0);

    glBegin(GL_LINES);

    glVertex2i(p1.x,p1.y);
    glVertex2i(p2.x, p2.y);
    
    glEnd();
    glFlush();
}



class Shape {
    
protected:
    char _type;
    
public:
    Shape(char type) {
        _type = type;
    }
    void draw(){ cout <<"Shape\n"; }
    
    virtual float calcArea(){
        return 0;
    }
    
    char getType() { return _type; }
    
    ~Shape(){
        
    }
    
};

class Line : public Shape {

private:
    Point point1, point2;
    
public:
    Line(Point p1=Point(0, 0), Point p2=Point(10,10), char type='L' ):point1(p1), point2(p2),Shape(type) {
    
        
    }
    
    Line(char type='L', const Line& l=Line()):point1(l.point1), point2(l.point2), Shape(type)
    {
    
        
    }
    
    void draw(){ drawLineInt(point1, point2); }
  
    float calcArea(){
        return 0;
    }
    
    
    Point getPoint1() const
    {
        return point1;
    }
    
    Point getPoint2() const{
        return point2;
    }
    
    float getLength() const{
        return sqrt(pow(point2.x - point1.x, 2) +
                    pow(point2.y - point1.y, 2) * 1.0);
    }
    
    ~Line()
    {
        
    }
    
};

class Circle : public Shape {
    
private:
    Point center;
    double radius;
    
public:
    Circle( Point a_center=Point(10,10), double radius=10.0,char type='C'):center(a_center),Shape(type) {
        this->radius = radius;

    }
    void draw(){
    
           glBegin(GL_LINE_LOOP);
         
          const double PI = 3.14159;

           for (double angle=0; angle<=2*PI; angle+=0.001)//You are using radians so you will have
               //to increase by a very small amount
                //This will have the coordinates  you want to draw a point at
           {
               Point p =  Point( center.x + radius*cos( angle ), center.y + radius*sin( angle ) );
        glVertex2d(p.x, p.y);
        
}
        glEnd();

    }
    float calcArea() {
        
        cout<<"\nArea of Circle: ";
    double area = 3.1416* (radius*radius);
        return area;
    }
  
    ~Circle()
    {
        
    }
};

class Triangle : public Shape {
private:
    Line line1, line2;
    double angle;
    
public:
    
    Triangle( Line l1=Line(Point(5,5), Point(10,10)), Line l2=(Point(10,10),Point(20,20)),
                        double a_angle=60.0,char type='T'):line1(l1), line2(l2), Shape(type), angle(a_angle)
    {
       
        
    }
    
     void draw(){
    
        line1.draw();
        line2.draw();
        drawLineInt(line1.getPoint2(), line2.getPoint2());
        
    }
     float calcArea() {
    
        
        float length = line1.getLength();
        float breadth = line2.getLength();
        float area = (length*breadth)/2;
        
        cout<<"\nArea of Triangle: ";
        return area;
        
    }
    
    ~Triangle(){}
};


void myInit(){ // *************** myInit **************
glClearColor(0.0, 0.0, 0.0, 0.0);
glColor3f(0.0, 0.0, 1.0);
glPointSize(4.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0, 640.0, 0.0, 480.0);
// set white background color
// set the drawing color


}


void drawShapes(Shape* _shape[], int size) {
    for (int i = 0; i < size; i++) {
        
        switch(_shape[i]->getType())
        {
            case 'L':
                static_cast<Line*>(_shape[i])->draw();
                break;
            case 'C':
                static_cast<Circle*>(_shape[i])->draw();
                break;
            case 'T':
                static_cast<Triangle*>(_shape[i])->draw();
                break;
            default:
                break;
                
        }
    
    }
}

void displayAreas(Shape* _shape[], int size) {
    for (int i = 0; i < size; i++) {
       switch(_shape[i]->getType())
        {
            case 'L':
                static_cast<Line*>(_shape[i])->calcArea();
                break;
            case 'C':
                static_cast<Circle*>(_shape[i])->calcArea();
                break;
            case 'T':
                static_cast<Triangle*>(_shape[i])->calcArea();
                break;
            default:
                break;
                
        }
    }
}


void myDisplay(void)
{
glClear(GL_COLOR_BUFFER_BIT);

    Shape *s[5];
    Point p0(400, 100);
    Point p01(560, 150);
    Point p1(100, 100);
    Point p2(300, 100);
    Point p3(100, 100);
    Point p4(100, 300);
    
    Line l1(p1, p2);
    Line l2(p3,p4);
    Point center(350, 300);
    s[0] = new Line(p0,p01);
    s[1] = new Circle(center,100);
    s[2] = new Triangle(l1,l2);

    drawShapes( s, 3 );
    displayAreas(s, 3);
    cout<<endl;
    
    for(int i=0; i<3; i++)
    {
        delete s[i];
    }
glFlush();
    
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
 

glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set the display mode
glutInitWindowSize(640, 480); // set the window size glutInitWindowPosition(100, 150); // set the window position on screen

// open the screen window
glutCreateWindow("Dots in opengl");
glutDisplayFunc(myDisplay); // register the redraw functions
myInit(); // some additional initialization as required
glutMainLoop();

}
