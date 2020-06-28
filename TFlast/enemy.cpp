#include "enemy.h"
#include "road.h"
#include "tower.h"
#include "collision.h"
#include "mainwindow.h"

#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

static const int Life_Bar_Width = 20;

const QSize Enemy::ms_fixedSize(42,42);

Enemy::Enemy(Road*startWayPoint, MainWindow *game, const QPixmap &sprite/* = QPixmap(":/monster5.png")*/)
    : QObject(0)
    , m_active(false)
    , m_maxHp(50)//���Ѫ��
    , m_currentHp(50)//�ִ�Ѫ��
    , m_walkingSpeed(1.2)//�ƶ��ٶ�
    , m_rotationSprite(0.0)//��ת�Ƕ�
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

void Enemy::doActivate()
{
    m_active = true;
}

void Enemy::move()
{
    if (!m_active)
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
            // ��ʾ�������
            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }

    // ����ǰ�������·��
    // Ŀ�꺽�������
    QPoint targetPoint = m_destinationWayPoint->pos();
    // δ���޸������������ƶ�״̬,�ӿ�,����,m_walkingSpeed�ǻ�׼ֵ

    // ������׼��
    qreal movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;



}

void Enemy::draw(QPainter *painter) const
{
    if (!m_active)
        return;

    painter->save();

    QPoint healthBarPoint = m_pos + QPoint(-Life_Bar_Width / 2 -5, -ms_fixedSize.height() / 3);
    // ����Ѫ��
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Life_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp *Life_Bar_Width, 2));
    painter->drawRect(healthBarRect);

    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    // ���Ƶ���
    painter->drawPixmap(offsetPoint, m_sprite);

    painter->restore();
}

void Enemy::getRemoved()
{
    if (m_attackedTowersList.empty())
        return;

    foreach (Tower *attacker, m_attackedTowersList)
        attacker->EnemyDead();
    // ֪ͨgame,�˵����Ѿ�����
    m_game->removedEnemy(this);
}

void Enemy::getDamage(int damage)
{

    m_currentHp -= damage;

    // ����,��Ҫ�Ƴ�
    if (m_currentHp <= 0)
    {

        m_game->awardGold(100);//����һ�������һ��
        getRemoved();
    }
}

void Enemy::getAttacked(Tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}

// ���������Ѿ������˹�����Χ
void Enemy::gotLostSight(Tower *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}

QPoint Enemy::pos() const
{
    return m_pos;
}
