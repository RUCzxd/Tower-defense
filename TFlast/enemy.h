#ifndef ENEMY_H
#define ENEMY_H


#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class Road;
class QPainter;
class MainWindow;
class Tower;

class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy(Road *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/monster5.png"));
    ~Enemy();

    void draw(QPainter *painter) const;
    void move();//控制移动
    void getDamage(int damage);//获得伤害
    void getRemoved();//击败后移除
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    QPoint pos() const;

public slots:
    void doActivate();

private:
    bool			m_active;//用于判断怪物是否可以前进
    int				m_maxHp;//表示怪物的最大血量
    int				m_currentHp;//表示怪物的当前血量
    qreal			m_walkingSpeed;//表示怪物的移动速度
    qreal			m_rotationSprite;//用于旋转方向

    QPoint			m_pos;//怪物的中心点位置
    Road *		m_destinationWayPoint;//用于判断是否到达终点，及每到达一个拐点就判断还有无下一个拐点，如果没有，就意味着已经到了终点
    MainWindow *	m_game;
    QList<Tower *>	m_attackedTowersList;

    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;
};


#endif // ENEMY_H
