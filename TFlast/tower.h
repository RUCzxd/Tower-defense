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
    void EnemyDead();//����������ֹͣ����
    void attackEnemy();//��������ģʽ
    void chooseEnemyForAttack(Enemy *enemy);//ѡ����˽��й���
    void removeBullet();
    void damageEnemy();
    void EnemyOutRange();//�������뷶Χ��ֹͣ����

private slots:
    void shootWeapon();//�����ӵ�

private:
    bool			m_attacking;
    int				m_attackRange;	// ���������Թ��������˵ľ���
    int				m_damage;		// ����������ʱ��ɵ��˺�
    int				m_fireFrequency;// �����ٴι������˵�ʱ����
    qreal			m_rotationSprite;//��ת�Ƕ�

    Enemy *			m_chooseEnemy;//����ѡ�����
    MainWindow *	m_game;
    QTimer *		m_fireRateTimer;

    const QPoint	m_pos;
    const QPixmap	m_sprite;

    static const QSize ms_fixedSize;
};

#endif // TOWER_H
