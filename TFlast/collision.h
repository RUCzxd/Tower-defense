#ifndef COLLISION_H
#define COLLISION_H
#include <QtMath>

inline bool ifcollision(QPoint point1, int radius1, QPoint point2, int radius2)
{
    const int x = point1.x() - point2.x();
    const int y = point1.y() - point2.y();
    const int distance = qSqrt(x * x + y * y);

    if (distance <= radius1 + radius2)
        return true;

    return false;
}
//�ú����������жϹ����Ƿ񵽴�յ�
//����ԭ��Ϊ��
//�����������ĵ�͹յ��x,y���꣬ͬʱ�涨��ײ�뾶
//��ν��ײ�뾶���ǹ涨�������ΪԲ�Ĳ�����ײ�뾶��Բ��������뵽Բ�м�Ϊ�Ѿ���ײ
//������������֮��ľ��룬�������С�ڵ��ڶ��߹涨����ײ�뾶֮�ͣ�����Ϊ��������ײ
#endif // COLLISION_H
