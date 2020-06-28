#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "road.h"
#include "enemy.h"
#include "bullet.h"

#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>

static const int TowerCost = 300;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_waves(0)
    , m_playerHp(5)
    , m_playerGold(1000)
    , m_gameEnded(false)
    , m_gameWin(false)
{
    ui->setupUi(this);


    loadTowerPositions();
    addWayPoints();



    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

    // 设置300ms后游戏启动
    QTimer::singleShot(300, this, SLOT(gameStart()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::paintEvent(QPaintEvent *)
{
    if (m_gameEnded || m_gameWin)
    {
        QString text = m_gameEnded ? "Congratulations!!!You Lost!!!" : "You Win :)!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }

    QPixmap cachePix(":/Background2.png");
    QPainter cachePainter(&cachePix);

    foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&cachePainter);

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);

    foreach (const Road *wayPoint, m_wayPointsList)
        wayPoint->draw(&cachePainter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&cachePainter);

    drawWave(&cachePainter);
    drawHP(&cachePainter);
    drawPlayerGold(&cachePainter);

    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {

            m_playerGold -= TowerCost;
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
    if (m_playerGold >= TowerCost)
        return true;
    return false;
}

void MainWindow::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(400, 5, 100, 25), QString("WAVE : %1").arg(m_waves + 1));
}

void MainWindow::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(m_playerHp));
}

void MainWindow::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(200, 5, 200, 25), QString("GOLD : %1").arg(m_playerGold));
}

void MainWindow::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
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
void MainWindow::awardGold(int gold)
{
    m_playerGold += gold;
    update();
}



void MainWindow::addWayPoints()
{
    Road *wayPoint1 = new Road(QPoint(420, 285));
    m_wayPointsList.push_back(wayPoint1);

    Road *wayPoint2 = new Road(QPoint(35, 285));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    Road *wayPoint3 = new Road(QPoint(35, 195));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    Road *wayPoint4 = new Road(QPoint(445, 195));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    Road *wayPoint5 = new Road(QPoint(445, 100));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    Road*wayPoint6 = new Road(QPoint(35, 100));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);
}

void MainWindow::getHpDamage(int damage/* = 1*/)
{

    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void MainWindow::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
            m_gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}

void MainWindow::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void MainWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

void MainWindow::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
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
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
    }
    return true;
}//暂时设定为6波敌人，每次六个

QList<Enemy *> MainWindow::enemyList() const
{
    return m_enemyList;
}

void MainWindow::gameStart()
{
    loadWave();
}
