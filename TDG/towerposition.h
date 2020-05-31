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
    bool		m_hasTower;//���ڱ�����λ���Ƿ��Ѿ���������
    QPoint		m_pos;
    QPixmap		m_sprite;//�������ͼƬ

    static const QSize ms_fixedSize;
};


#endif // TOWERPOSITION_H
