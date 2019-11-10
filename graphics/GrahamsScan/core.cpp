//
// Created by Peter on 2019/11/5.
//

#include "core.h"

//--------------------------------------------------------------
// Setting
const int WIDTH = 900, HEIGHT = 600;
const int RANDOM_COUNT = 20;
const int MAX = 0x7fffffff;
//--------------------------------------------------------------

//--------------------------------------------------------------
// Controlling
bool close = false;
bool clear = false;
bool generating = false;
//--------------------------------------------------------------

//--------------------------------------------------------------
// Status
Point minYPoint(0, MAX);
//--------------------------------------------------------------

std::vector<Point> points;
std::vector<Point> trace;


//--------------------------------------------------------------
// Step

void randomGenerate(int number)
{
    srand(time(nullptr));
    for(int i=1;i<=number;i++)
    {
        int x = rand()%WIDTH, y = rand()%HEIGHT;
        for(Point point:points)
            if(x == point.x && y == point.y)
                continue;
        points.push_back(Point(x, y));

        if(y<minYPoint.y || (y == minYPoint.y && x < minYPoint.x))
        {
            minYPoint = points.back();
        }
    }
}

void GrahamsScan()
{
    pty::quick_sort_recursive<Point>(points, 0, points.size()-1, [](Point e1, Point e2)->bool
    {
        return atan2(e1.x-minYPoint.x, e1.y-minYPoint.y)<atan2(e2.x-minYPoint.x,e2.y-minYPoint.y);
//        }
    });

//    for(Point point:points)
//    {
//        if(point.x != minYPoint.x)
//        {
//            std::cout << atan2(point.x-minYPoint.x, point.y-minYPoint.y)<<std::endl;
//            std::cout<<"###############"<<(double)(point.y-minYPoint.y)/(point.x-minYPoint.x)<<std::endl;
//        }
//    }
    trace.push_back(minYPoint);
    unsigned first = 0;
    if(points.front()==minYPoint)
        first = 1;

    trace.push_back(points[first]);

    for(unsigned i=first+1;i<points.size();i++)
    {
        if(points[i] == minYPoint)
            continue;
        if(valid(trace[trace.size()-2], trace[trace.size()-1], points[i]))
        {
            trace.push_back(points[i]);
        }
        else
        {
            do
            {
                trace.pop_back();
            }
            while(!valid(trace[trace.size()-2], trace[trace.size()-1], points[i]));
            trace.push_back(points[i]);
        }
    }
    trace.push_back(minYPoint);

    glColor3d(1, 1, 1);
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<trace.size()-1;i++)
    {
        glVertex2i(trace[i].x, trace[i].y);
        glVertex2i(trace[i+1].x, trace[i+1].y);
    }
    glEnd();

}
//--------------------------------------------------------------


//--------------------------------------------------------------
// Draw
void drawPoints()
{
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    for (auto point : points)
    {
        glColor3f(1.f, 0.f, 0.f);
        glVertex2i(point.x, point.y);
    }
    glEnd();
}
//--------------------------------------------------------------

//--------------------------------------------------------------
// GL Action
void renderScene()
{
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!clear)
    {
        if (!close)
        {
            drawPoints();
        }
        else
        {
            drawPoints();
            GrahamsScan();
        }
    }


    glFlush();
}

void mouse(int button, int state, int mx, int my)
{
    if (state == GLUT_DOWN)
    {
        switch (button)
        {
            case GLUT_LEFT_BUTTON:
                clear = false;
                for(Point point:points)
                    if(mx == point.x && my == point.y)
                        return;

                points.push_back(Point(mx, my));

                if((points.back()).y<minYPoint.y || ((points.back()).y == minYPoint.y && (points.back()).x < minYPoint.x))
                {
                    minYPoint = points.back();
                }
                break;
            case GLUT_RIGHT_BUTTON:
                clear = false;
                if(!generating)
                {
                    generating = true;
                    randomGenerate(RANDOM_COUNT);
                    generating = false;
                }
                break;
            default:
                break;
        }
        glutPostRedisplay();
    }

}

void keyboard(unsigned char key, int x, int y)
{
    if (key == '\r')
    {

        if(points.size() >= 3)
            close = true;
        glutPostRedisplay();
    }
    else if(key == ' ')
    {
        glFlush();

        clear = true;
        close = false;
        generating = false;
        points.clear();
        trace.clear();
        minYPoint = Point(0, MAX);
        glutPostRedisplay();
    }
}

int process(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(300, 300);
    glutCreateWindow("Graham's Scan"); // open the screen window

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, HEIGHT, 0.0);

    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
//--------------------------------------------------------------