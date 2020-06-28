#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"

namespace Ui {
class MainWindow;
}

class Road;
class Enemy;
class Bullet;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void getHpDamage(int damage = 1);//���ڴ������ط�Ѫ
    void removedEnemy(Enemy *enemy);//����Ϸ�������Ƴ�������ĵ���
    void removedBullet(Bullet *bullet);//����Ϸ�������Ƴ��Ѿ��ù����ӵ�
    void addBullet(Bullet *bullet);
    void awardGold(int gold);//��Ǯ��


    QList<Enemy *> enemyList() const;

protected:
    void paintEvent(QPaintEvent *);//��ͼ
    void mousePressEvent(QMouseEvent *);//��������ķ�ʽ�����Ʒ������İ���

private slots:
    void updateMap();
    void gameStart();

private:
    void loadTowerPositions();//ȷ����������λ��
    void addWayPoints();//����·������Ĺյ�
    bool loadWave();//���ز���
    bool canBuyTower() const;//�ж��Ƿ�����������
    void drawWave(QPainter *painter);//�����ڽ�������ġ�Wave"������
    void drawHP(QPainter *painter);//������������ġ�HP��������
    void drawPlayerGold(QPainter *painter);//������������Ľ����
    void doGameOver();


private:
    Ui::MainWindow *		ui;
    int						m_waves;//����
    int						m_playerHp;//����Ѫ��
    int						m_playerGold;//��ҵ�Ǯ
    bool					m_gameEnded;
    bool					m_gameWin;


    QList<TowerPosition>	m_towerPositionsList;//����������λ����Ϣ
    QList<Tower *>			m_towersList;//������������Ϣ
    QList<Road *>		    m_wayPointsList;//����·���Ϲյ���Ϣ
    QList<Enemy *>			m_enemyList;//����������Ϣ
    QList<Bullet *>			m_bulletList;//�����ڵ���Ϣ
};

#endif // MAINWINDOW_H