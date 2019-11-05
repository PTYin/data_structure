//
// Created by Peter on 2019/10/10.
//
#include "core.h"

//--------------------------------------------------------------
// Setting
const int WIDTH = 900, HEIGHT = 600;
const double INFINITESIMAL = 0.0001;
using pty::AVLTree;
//--------------------------------------------------------------

//--------------------------------------------------------------
// Controlling
bool close = false;
bool clear = false;
//--------------------------------------------------------------

//--------------------------------------------------------------
// Status
int current = 0;
int bottom = 0x7fffffff, top = 0;
//--------------------------------------------------------------

std::vector<Point> points;
std::vector<Edge> edges;
std::map<int, std::vector<Edge> *> edgeMap;


//--------------------------------------------------------------
// Step
void initEdgeTable()
{
    if (points.size() < 3)
        return;
    for (int i = 1; i < points.size(); i++)
    {
        bottom = bottom > points[i - 1].y ? points[i - 1].y : bottom;
        top = top < points[i - 1].y ? points[i - 1].y : top;
        auto yMin = min(points[i - 1].y, points[i].y);

        if (points[i - 1].y == points[i].y)  // if line parallel with x axis
            continue;
        edges.emplace_back(points[i - 1].x, points[i - 1].y, points[i].x, points[i].y);


        if (edgeMap.count(yMin))
        {
            edgeMap[yMin]->push_back(edges[edges.size() - 1]);
        }
        else
        {
            auto vec = new std::vector<Edge>;
            vec->push_back(edges[edges.size() - 1]);
            edgeMap[yMin] = vec;
        }

    }

    bottom = bottom > points[points.size() - 1].y ? points[points.size() - 1].y : bottom;
    top = top < points[points.size() - 1].y ? points[points.size() - 1].y : top;
    // last edge
    edges.emplace_back(points[points.size() - 1].x, points[points.size() - 1].y, points[0].x, points[0].y);

    auto yMin = min(points[points.size() - 1].y, points[0].y);

    if (edgeMap.count(yMin))
    {
        edgeMap[yMin]->push_back(edges[edges.size() - 1]);
    }
    else
    {
        auto vec = new std::vector<Edge>;
        vec->push_back(edges[edges.size() - 1]);
        edgeMap[yMin] = vec;
    }
}

void scanLineFill()
{

    pty::Treap<Edge> activeEdgeTable;
    for (int line = bottom; line <= top; line++)
    {
        if (edgeMap.count(line))
            for (Edge edge : *edgeMap[line])
            {
                activeEdgeTable.insert(edge);
            }
        bool ableToDraw = false;
        std::vector<Edge> toRemove;
        Edge *last_ptr = nullptr;
        activeEdgeTable.traversal_in([&toRemove, &line, &ableToDraw, &last_ptr](pty::TreapNode<Edge> *node)
                                     {
                                         if (ableToDraw)
                                         {
                                             fill(last_ptr->xOfyMin - last_ptr->slopeInverse, node->get().xOfyMin,
                                                  line);
                                             ableToDraw = false;
                                         }
                                         else
                                         {
                                             ableToDraw = true;
                                         }

                                         /*
                                          * Precision loss can cause Balanced SearchTree's structure fault.
                                          * Therefore, after modifying one node's xOfyMin, it should still follow the origin order in the tree.*/
                                         if (last_ptr)
                                         {
                                             node->get().xOfyMin = (last_ptr->xOfyMin <
                                                                    node->get().xOfyMin + node->get().slopeInverse ?
                                                                    node->get().xOfyMin + node->get().slopeInverse :
                                                                    last_ptr->xOfyMin +
                                                                    INFINITESIMAL);  // solve Precision problem
                                         }
                                         else
                                         {
                                             node->get().xOfyMin += node->get().slopeInverse;
                                         }

                                         last_ptr = &node->get();

                                         if (line + 1 == node->get().yMax)
                                         {
                                             toRemove.push_back(node->get());
                                         }
                                     });
        for (auto edge:toRemove)
        {
            activeEdgeTable.remove(edge);
        }
    }
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

void drawEdges()
{
    glColor3d(1, 1, 1);
    glBegin(GL_LINE_STRIP);
    int points_size = points.size();
    for (unsigned i = 0; i < points_size - 1; i++)
    {
        glVertex2i(points[i].x, points[i].y);
        glVertex2i(points[i + 1].x, points[i + 1].y);
    }
    if (close)
    {
        glVertex2i(points[points_size - 1].x, points[points_size - 1].y);
        glVertex2i(points[0].x, points[0].y);
    }
    glEnd();
}

void fill(double left_f, double right_f, int y)
{
    int left = (int) left_f, right = (int) right_f;
    if (left == 0)
    {
        std::cout << " ";
    }
    glBegin(GL_LINES);
    glVertex2i(left, y);
    glVertex2i(right, y);
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
            if (current >= 2)
                drawEdges();
        }
        else if (current >= 2)
        {
            drawEdges();
            initEdgeTable();
            scanLineFill();
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
                current++;
                if (valid(Point(mx, my), points))
                    points.emplace_back(mx, my);
                break;
            case GLUT_RIGHT_BUTTON:
                if (valid(points[0], points))
                {
                    close = true;
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
    if (key == ' ')
    {
        glFlush();

        clear = true;
        close = false;
        points.clear();
        edges.clear();
        for (auto pair:edgeMap)
        {
            delete pair.second;
        }
        edgeMap.clear();

        glutPostRedisplay();
    }
}

void process(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(300, 300);
    glutCreateWindow("ScanLineFillPolygon"); // open the screen window

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, HEIGHT, 0.0);

    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
}
//--------------------------------------------------------------
