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
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void getHpDamage(int damage = 1);//用于处理基地费血
    void removeEnemy(Enemy *enemy);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);//用鼠标点击的方式来控制防御塔的安放
    bool loadWave();//用于加载下一波怪物
    QList<Enemy *> enemyList() const;
private slots:
    void updateMap();
    void gameStart();
private:
    Ui::MainWindow *ui;
    void loadTowerPositions();
    QList<TowerPosition> m_towerPositionsList;
    QList<Tower *> m_towersList; // 用来管理攻击塔的信息
    bool canBuyTower() const;
    void Enemywaypoints();
    QList<Road *>m_wayPointsList;//在MainWindow绘制时使用
    QList<Enemy *>m_enemyList;
    int	m_waves;//用于记录怪物来袭的波数
    bool m_gameWin;//用其值来判断是否获胜


};


#endif // MAINWINDOW_H
