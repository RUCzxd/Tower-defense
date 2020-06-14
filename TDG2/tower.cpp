#include "tower.h"

#include "mainwindow.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Tower::ms_fixedSize(42, 42);
Tower::Tower(QPoint pos,MainWindow *game, const QPixmap &sprite/* = QPixmap(":/image/Tower1.png"*/)

    : m_attacking(false)
    , m_attackrange(70)
    , m_damage(15)
    , m_fireFrequency(1000)
    , m_rotationSprite(0.0)
    , m_pos(pos)
    , m_sprite(sprite)
    , m_game(game)
{

}
void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::white);
    // »æÖÆ¹¥»÷·¶Î§
    painter->drawEllipse(m_pos, m_attackrange, m_attackrange);

    // »æÖÆÆ«×ª×ø±ê
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    // »æÖÆÅÚËþ²¢Ñ¡ÔñÅÚËþ
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}
