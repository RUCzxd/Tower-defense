#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    Ui::MainWindow *ui;
    void loadTowerPositions();
    QList<TowerPosition> m_towerPositionsList;
    QList<Tower *> m_towersList; // 用来管理攻击塔的信息
    bool canBuyTower() const;

};

#endif // MAINWINDOW_H
