#include "mainwindow.h"
#include "enemy.h"
#include "ui_mainwindow.h"
#include "road.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#include <QMap>
static const int TowerCost = 0;//此处规定一个初级防御塔需要多少钱
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow),
    m_waves(0),//初始波数为0
    m_gameWin(false)//初始未胜利
{
    ui->setupUi(this);
    loadTowerPositions();
    Enemywaypoints();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);
    QTimer::singleShot(30, this, SLOT(gameStart()));

}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPixmap cachePix(":/image/Background2.png");
    QPainter cachePainter(&cachePix);
    foreach (const TowerPosition &towerPos, m_towerPositionsList)//画出防御塔的“坑”
        towerPos.draw(&cachePainter);
    foreach (const Tower *tower, m_towersList)//画出防御塔
        tower->draw(&cachePainter);
    foreach (const Road *wayPoint, m_wayPointsList)//画出怪物要走的路线，并标示出拐点及出发点和终点
        wayPoint->draw(&cachePainter);
    foreach (const Enemy *enemy, m_enemyList)//画出怪物
        enemy->draw(&cachePainter);

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
void MainWindow::mousePressEvent(QMouseEvent *event)//用鼠标来控制防御塔的放置
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
void MainWindow::Enemywaypoints()//标注每一个航线上面的转折点，包括起始点和终点。
{
       Road *wayPoint1 = new Road (QPoint(420, 285));
        m_wayPointsList.push_back(wayPoint1);

        Road  *wayPoint2 = new Road (QPoint(35, 285));
        m_wayPointsList.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);

       Road  *wayPoint3 = new Road (QPoint(35, 195));
        m_wayPointsList.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);

        Road  *wayPoint4 = new Road (QPoint(445, 195));
        m_wayPointsList.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);

        Road *wayPoint5 = new Road (QPoint(445, 100));
        m_wayPointsList.push_back(wayPoint5);
        wayPoint5->setNextWayPoint(wayPoint4);

        Road  *wayPoint6 = new Road (QPoint(35, 100));
        m_wayPointsList.push_back(wayPoint6);
        wayPoint6->setNextWayPoint(wayPoint5);


}
bool MainWindow::loadWave()
{
    if (m_waves >= 6)
        return false;
    Road *startWayPoint = m_wayPointsList.back();
    int enemyStartInterval[] = { 100, 500, 600, 1000, 3000, 6000 };
    for (int i = 0; i < 6; ++i)
    {
        Enemy *enemy = new Enemy(startWayPoint, this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(cango()));
    }
    return true;
}//暂时设定为6波敌人，每次六个
void MainWindow::getHpDamage(int damage/* = 1*/)
{
    // 暂时空实现，以后这里进行基地费血行为
}
void MainWindow::removeEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    m_enemyList.removeOne(enemy);
    delete enemy;
    if (m_enemyList.empty())
    {
        ++m_waves; // 当前波数加1
        // 继续读取下一波
        if (!loadWave())
        {
            // 当没有下一波时，这里表示游戏胜利
            // 设置游戏胜利标志为true
            m_gameWin = true;
            // 游戏胜利转到游戏胜利场景

        }
    }
}
void MainWindow::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    update();
}
QList<Enemy *> MainWindow::enemyList() const
{
    return m_enemyList;
}
void MainWindow::gameStart()
{
    loadWave();
}
