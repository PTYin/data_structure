//
// Created by Peter on 2019/10/10.
//

#ifndef SLPF_TOOLKIT_HPP
#define SLPF_TOOLKIT_HPP


template<typename T>
T &max(T &x1, T &x2)
{
    return x1 > x2 ? x1 : x2;
}

template<typename T>
T &min(T &x1, T &x2)
{
    return x1 < x2 ? x1 : x2;
}

struct Point
{
    int x, y;

    Point(int x_, int y_) : x(x_), y(y_)
    {}

    bool operator==(const Point &o)
    {
        return x == o.x && y == o.y;
    }
};

struct Edge
{
    int yMax;
    double xOfyMin;
    double slopeInverse;

    Edge(int x1, int y1, int x2, int y2) :
            yMax(max(y1, y2)), xOfyMin(yMax != y1 ? x1 : x2), slopeInverse((double) (x2 - x1) / (double) (y2 - y1))
    {}

    bool operator==(const Edge &o)
    {
        return xOfyMin == o.xOfyMin && yMax == o.yMax && slopeInverse == o.slopeInverse;
    }

    bool operator!=(const Edge &o)
    {
        return !operator==(o);
    }

    bool operator<(const Edge &o)
    {
        return xOfyMin < o.xOfyMin || (xOfyMin == o.xOfyMin && slopeInverse < o.slopeInverse);
    }

    bool operator>(const Edge &o)
    {
        return xOfyMin > o.xOfyMin || (xOfyMin == o.xOfyMin && slopeInverse > o.slopeInverse);
    }
};


static bool intersecting(Point l1_start, Point l1_end, Point l2_start, Point l2_end)
{
    int s1 = (l1_end.x - l1_start.x) * (l2_start.y - l1_start.y) - (l1_end.y - l1_start.y) * (l2_start.x - l1_start.x) >
             0 ? 1 : -1;
    int s2 = (l1_end.x - l1_start.x) * (l2_end.y - l1_start.y) - (l1_end.y - l1_start.y) * (l2_end.x - l1_start.x) > 0
             ? 1 : -1;
    int s3 = (l2_end.x - l2_start.x) * (l1_start.y - l2_start.y) - (l2_end.y - l2_start.y) * (l1_start.x - l2_start.x) >
             0 ? 1 : -1;
    int s4 = (l2_end.x - l2_start.x) * (l1_end.y - l2_start.y) - (l2_end.y - l2_start.y) * (l1_end.x - l2_start.x) > 0
             ? 1 : -1;
    return s1 * s2 <= 0 && s3 * s4 <= 0;
}

template<typename CONTAINER>
bool valid(Point point, CONTAINER points)
{
    if (points.size() < 3)
        return true;
    Point last = points[points.size() - 1];
    int i = 0;
    if (point == points[0])
        i = 1;
    for (int j = i; j < points.size() - 2; j++)
        if (intersecting(points[j], points[j + 1], last, point))
            return false;
    return true;
}

#endif //SLPF_TOOLKIT_HPP
