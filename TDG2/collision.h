#ifndef COLLISION_H
#define COLLISION_H
#include <QtMath>

inline bool ifcollision(QPoint point1, int r1, QPoint point2, int r2)
{
    const int x = point1.x() - point2.x();
    const int y = point1.y() - point2.y();
    const int distance = qSqrt(x * x + y * y);

    if (distance <= r1 + r2)
    {
        return true;
    }
    else
    {
      return false;
    }

}
//该函数是用来判断怪物是否到达拐点
//具体原理为：
//输入怪物的中心点和拐点的x,y坐标，同时规定碰撞半径
//所谓碰撞半径就是规定以这个点为圆心并以碰撞半径作圆，如果进入到圆中即为已经相撞
//计算这两个点之间的距离，如果距离小于等于二者规定的碰撞半径之和，可视为这两点相撞
#endif // COLLISION_H
