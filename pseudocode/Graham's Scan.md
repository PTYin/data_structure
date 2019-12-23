# Graham's Scan

```cpp
bool valid(Point p1, Point p2, Point p3)
{
    return 向量(p2-p1)与向量(p3-p2)叉积 > 0;
}
void graham()
{
    sort(points.begin(), points.end(), [](Point p1, Point p2)
         {
             return 向量(p1-minYPoint)与x轴夹角<向量(p2-minYPoint)与x轴夹角;
         });

    for(int i=1;i<points.size();i++)
    {
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
            while(!valid(trace[size()-2], trace[trace.size()-1], points[i]));
            trace.push_back(points[i]);
        }
    }
}
```

