#include "road.h"

#include <QPainter>
#include <QColor>
Road::Road(QPoint pos)
    : m_pos(pos)
    , m_nextWayPoint(NULL)
{
}

void Road::setNextWayPoint(Road *nextPoint)
{
    m_nextWayPoint = nextPoint;
}

Road* Road::nextWayPoint() const
{
    return m_nextWayPoint;
}

const QPoint Road::pos() const
{
    return m_pos;
}

void Road::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawEllipse(m_pos, 6, 6);
    painter->drawEllipse(m_pos, 2, 2);

    if (m_nextWayPoint)
        painter->drawLine(m_pos, m_nextWayPoint->m_pos);
    painter->restore();
}
