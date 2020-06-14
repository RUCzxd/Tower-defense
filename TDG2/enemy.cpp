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
    // Ѫ���ĳ���
    // ��ʵ����2������,��ɫ�����ʾ������,�̶���С����
    // ��ɫ�����ʾ��ǰ����,��m_currentHp / m_maxHp�ı仯Ӱ��
    static const int Life_Bar_Width = 20;
    painter->save();
    QPoint LifeBarPoint = m_pos + QPoint(-Life_Bar_Width / 2 - 5, -ms_fixedSize.height() / 3);
    // ����Ѫ��
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(LifeBarPoint, QSize(Life_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);
    painter->setBrush(Qt::yellow);
    QRect healthBarRect(LifeBarPoint, QSize((double)m_currentHp / m_maxHp * Life_Bar_Width, 2));
    painter->drawRect(healthBarRect);
    // ����ƫת����,������+ƫ��=����
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    // ���Ƶ���
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}
void Enemy::move()
{
    if (!m_continuego)
        return;
    if (ifcollision(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        // ���˵ִ���һ���յ�
        if (m_destinationWayPoint->nextWayPoint())
        {
            // ������һ���յ�
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            // û����һ���յ����ζ�ŵ����յ�
            m_game->getHpDamage();
            m_game->removeEnemy(this);
            return;
        }
    }
    // ����ǰ�������·��
    // Ŀ�꺽�������
    QPoint targetPoint = m_destinationWayPoint->pos();
    double movementSpeed = m_moveSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;
    // ȷ������ѡ����
    // ͼƬ����,��Ҫ����180��ת��

}
void Enemy::cango()
{
    m_continuego = true;
}
QPoint Enemy::pos() const
{
    return m_pos;
}

