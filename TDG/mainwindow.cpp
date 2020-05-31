#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
static const int TowerCost = 0;//此处规定一个初级防御塔需要多少钱
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadTowerPositions();
}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPixmap cachePix(":/image/Background2.png");
    QPainter cachePainter(&cachePix);
    foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&cachePainter);
    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);
    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);

}
void MainWindow::loadTowerPositions()//规定塔可以放置的位置
{
    QPoint pos[] =
    {
        QPoint(65, 220),
        QPoint(155, 220),
        QPoint(245, 220),
        QPoint(335, 220),

        QPoint(100, 125),
        QPoint(195, 125),
        QPoint(280, 125),
        QPoint(370, 125),

        QPoint(80, 35),
        QPoint(170, 35),
        QPoint(260, 35),
        QPoint(350, 35)
    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
        m_towerPositionsList.push_back(pos[i]);

}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {


            it->setHasTower();

            Tower *tower = new Tower(it->centerPos(), this);
            m_towersList.push_back(tower);
            update();
            break;
        }

        ++it;
    }
}

bool MainWindow::canBuyTower() const
{

        return true;//目前是不花钱就能买，之后的代码会进行修改

}


