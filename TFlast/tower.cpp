#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "mainwindow.h"
#include "collision.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Tower::ms_fixedSize(42, 42);

Tower::Tower(QPoint pos, MainWindow *game, const QPixmap &sprite/* = QPixmap(":/Tower2.png"*/)
    : m_attacking(false)
    , m_attackRange(70)
    , m_damage(15)
    , m_fireFrequency(1000)
    , m_rotationSprite(0.0)
    , m_chooseEnemy(NULL)
    , m_game(game)
    , m_pos(pos)
    , m_sprite(sprite)
{
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

Tower::~Tower()
{
    delete m_fireRateTimer;
    m_fireRateTimer = NULL;
}

void Tower::checkEnemyInRange()
{
    if (m_chooseEnemy)
    {
        // ���������,��Ҫ��ת��̨��׼����
        // ������׼��
        QVector2D normalized(m_chooseEnemy->pos() - m_pos);
        normalized.normalize();
        m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;

        // ����������빥����Χ
        if (!ifcollision(m_pos, m_attackRange, m_chooseEnemy->pos(), 1))
            EnemyOutRange();
    }
    else
    {
        // ��������,���Ƿ��е����ڹ�����Χ��
        QList<Enemy *> enemyList = m_game->enemyList();
        foreach (Enemy *enemy, enemyList)
        {
            if (ifcollision(m_pos, m_attackRange, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}

void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::white);
    // ���ƹ�����Χ
    painter->drawEllipse(m_pos, m_attackRange, m_attackRange);

    // ����ƫת����,������+ƫ��=����
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    // ����������ѡ������
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

void Tower::attackEnemy()
{
    m_fireRateTimer->start(m_fireFrequency);
}

void Tower::chooseEnemyForAttack(Enemy *enemy)
{
    m_chooseEnemy = enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);
}

void Tower::shootWeapon()
{
    Bullet *bullet = new Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet->move();
    m_game->addBullet(bullet);
}

void Tower::EnemyDead()
{
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}

void Tower::EnemyOutRange()//�������뷶Χ��ֹͣ����
{
    m_chooseEnemy->gotLostSight(this);
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}
