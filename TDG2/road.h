#ifndef ROAD_H
#define ROAD_H


#include <QPoint>
class QPainter;
class Road
{
public:
    Road(QPoint pos);
    void setNextWayPoint( Road *nextPoint);
       Road* nextWayPoint() const;
        const QPoint pos() const;

        void draw(QPainter *painter) const;

    private:
       const QPoint m_pos;
        Road * m_nextWayPoint;


};


#endif // ROAD_H
