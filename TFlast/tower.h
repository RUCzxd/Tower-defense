#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class MainWindow;
class QTimer;

class Tower : QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/Tower2.png"));
    ~Tower();

    void draw(QPainter *painter) const;
    void checkEnemyInRange();
    void EnemyDead();//敌人已死，停止攻击
    void attackEnemy();//启动开火模式
    void chooseEnemyForAttack(Enemy *enemy);//选择敌人进行攻击
    void removeBullet();
    void damageEnemy();
    void EnemyOutRange();//敌人脱离范围，停止攻击

private slots:
    void shootWeapon();//发射子弹

private:
    bool			m_attacking;
    int				m_attackRange;	// 代表塔可以攻击到敌人的距离
    int				m_damage;		// 代表攻击敌人时造成的伤害
    int				m_fireFrequency;// 代表再次攻击敌人的时间间隔
    qreal			m_rotationSprite;//旋转角度

    Enemy *			m_chooseEnemy;//用于选择敌人
    MainWindow *	m_game;
    QTimer *		m_fireRateTimer;

    const QPoint	m_pos;
    const QPixmap	m_sprite;

    static const QSize ms_fixedSize;
};

#endif // TOWER_H
