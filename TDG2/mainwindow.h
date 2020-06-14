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
    void getHpDamage(int damage = 1);//���ڴ�����ط�Ѫ
    void removeEnemy(Enemy *enemy);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);//��������ķ�ʽ�����Ʒ������İ���
    bool loadWave();//���ڼ�����һ������
    QList<Enemy *> enemyList() const;
private slots:
    void updateMap();
    void gameStart();
private:
    Ui::MainWindow *ui;
    void loadTowerPositions();
    QList<TowerPosition> m_towerPositionsList;
    QList<Tower *> m_towersList; // ����������������Ϣ
    bool canBuyTower() const;
    void Enemywaypoints();
    QList<Road *>m_wayPointsList;//��MainWindow����ʱʹ��
    QList<Enemy *>m_enemyList;
    int	m_waves;//���ڼ�¼������Ϯ�Ĳ���
    bool m_gameWin;//����ֵ���ж��Ƿ��ʤ


};


#endif // MAINWINDOW_H
