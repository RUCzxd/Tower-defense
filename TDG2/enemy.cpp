#include "enemy.h"
#include "collision.h"
#include "mainwindow.h"
#include "road.h"
#include "tower.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

const QSize Enemy::ms_fixedSize(42, 42);
Enemy::Enemy(Road *startWayPoint, MainWindow *game, const QPixmap &sprite/* = QPixmap(":/image/monster4.png")*/)
    : QObject(0)
    , m_continuego(false)
    , m_maxHp(40)
    , m_currentHp(40)
    , m_moveSpeed(1.0)
    , m_rotationSprite(0.0)
    , m_pos(startWayPoint->pos())
    , m_destinationWayPoint(startWayPoint->nextWayPoint())
    , m_game(game)
    , m_sprite(sprite)
{

}
Enemy::~Enemy()
{
    m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}
void Enemy::draw(QPainter *painter)const
{
    if (!m_continuego)
        return;
    // 血条的长度
    // 其实就是2个方框,红色方框表示总生命,固定大小不变
    // 黄色方框表示当前生命,受m_currentHp / m_maxHp的变化影响
    static const int Life_Bar_Width = 20;
    painter->save();
    QPoint LifeBarPoint = m_pos + QPoint(-Life_Bar_Width / 2 - 5, -ms_fixedSize.height() / 3);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(LifeBarPoint, QSize(Life_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);
    painter->setBrush(Qt::yellow);
    QRect healthBarRect(LifeBarPoint, QSize((double)m_currentHp / m_maxHp * Life_Bar_Width, 2));
    painter->drawRect(healthBarRect);
    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    // 绘制敌人
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}
void Enemy::move()
{
    if (!m_continuego)
        return;
    if (ifcollision(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        // 敌人抵达了一个拐点
        if (m_destinationWayPoint->nextWayPoint())
        {
            // 还有下一个拐点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            // 没有下一个拐点就意味着到达终点
            m_game->getHpDamage();
            m_game->removeEnemy(this);
            return;
        }
    }
    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = m_destinationWayPoint->pos();
    double movementSpeed = m_moveSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;
    // 确定敌人选择方向
    // 图片向左,需要修正180度转右

}
void Enemy::cango()
{
    m_continuego = true;
}
QPoint Enemy::pos() const
{
    return m_pos;
}

