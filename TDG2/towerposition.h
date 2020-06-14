#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QPoint>
#include <QSize>
#include <QPixmap>

class QPainter;

class TowerPosition
{
public:
    TowerPosition(QPoint pos, const QPixmap &sprite = QPixmap(":/image/TowerPosition1.png"));

    void setHasTower(bool hasTower = true);
    bool hasTower() const;
    const QPoint centerPos() const;
    bool containPoint(const QPoint &pos) const;

    void draw(QPainter *painter) const;

private:
    bool		m_hasTower;//用于表明该位置是否已经有塔存在
    QPoint		m_pos;//安放防御塔的“坑”的中心点位置
    QPixmap		m_sprite;//保存绘制图片

    static const QSize ms_fixedSize;
};
#endif // TOWERPOSITION_H
