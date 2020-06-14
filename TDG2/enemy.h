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
class Enemy:public QObject
{
    Q_OBJECT
 public:
    Enemy(Road *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/monster4.png"));
     ~Enemy();
    void draw(QPainter *painter) const;
    void move();//�����ƶ�
    void getDamage(int damage);//����˺�
    void getRemoved();//���ܺ��Ƴ�
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    QPoint pos() const;
public slots:
    void cango();
private:
    bool			m_continuego;//�������жϹ����Ƿ���Լ���ǰ��
    int				m_maxHp;//��ʾ��������Ѫ��
    int				m_currentHp;//��ʾ������Դ�Ѫ��
    qreal			m_moveSpeed;//��ʾ������ƶ��ٶ�
    qreal			m_rotationSprite;//��ʾ�������ת�Ƕȣ�������ÿ���յ㽫ͼƬת��

    QPoint			m_pos;//��������ĵ�λ��
    Road *		m_destinationWayPoint;//�����ж��Ƿ񵽴��յ㣬��ÿ����һ���յ���жϻ�������һ���յ㣬���û�У�����ζ���Ѿ������յ�
    MainWindow *	m_game;
    QList<Tower *>	m_attackedTowersList;

    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;//�������ƹ���Ĵ�С

};

#endif // ENEMY_H
