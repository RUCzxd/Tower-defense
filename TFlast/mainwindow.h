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

    void getHpDamage(int damage = 1);//用于处理基地费血
    void removedEnemy(Enemy *enemy);//在游戏界面中移除被消灭的敌人
    void removedBullet(Bullet *bullet);//在游戏界面中移除已经用过的子弹
    void addBullet(Bullet *bullet);
    void awardGold(int gold);//加钱的


    QList<Enemy *> enemyList() const;

protected:
    void paintEvent(QPaintEvent *);//画图
    void mousePressEvent(QMouseEvent *);//用鼠标点击的方式来控制防御塔的安放

private slots:
    void updateMap();
    void gameStart();

private:
    void loadTowerPositions();//确定安放塔的位置
    void addWayPoints();//添加路径上面的拐点
    bool loadWave();//加载波数
    bool canBuyTower() const;//判断是否可以买防御塔
    void drawWave(QPainter *painter);//画出在界面上面的“Wave"及数字
    void drawHP(QPainter *painter);//画出界面上面的“HP”及数字
    void drawPlayerGold(QPainter *painter);//画出界面上面的金币数
    void doGameOver();


private:
    Ui::MainWindow *		ui;
    int						m_waves;//波数
    int						m_playerHp;//基地血量
    int						m_playerGold;//玩家的钱
    bool					m_gameEnded;
    bool					m_gameWin;


    QList<TowerPosition>	m_towerPositionsList;//管理防御塔位置信息
    QList<Tower *>			m_towersList;//管理防御塔信息
    QList<Road *>		    m_wayPointsList;//管理路径上拐点信息
    QList<Enemy *>			m_enemyList;//管理敌人信息
    QList<Bullet *>			m_bulletList;//管理炮弹信息
};

#endif // MAINWINDOW_H
