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
static const int TowerCost = 0;//�˴��涨һ��������������Ҫ����Ǯ
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow),
    m_waves(0),//��ʼ����Ϊ0
    m_gameWin(false)//��ʼδʤ��
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
    foreach (const TowerPosition &towerPos, m_towerPositionsList)//�����������ġ��ӡ�
        towerPos.draw(&cachePainter);
    foreach (const Tower *tower, m_towersList)//����������
        tower->draw(&cachePainter);
    foreach (const Road *wayPoint, m_wayPointsList)//��������Ҫ�ߵ�·�ߣ�����ʾ���յ㼰��������յ�
        wayPoint->draw(&cachePainter);
    foreach (const Enemy *enemy, m_enemyList)//��������
        enemy->draw(&cachePainter);

    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);

}
void MainWindow::loadTowerPositions()//�涨�����Է��õ�λ��
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
void MainWindow::mousePressEvent(QMouseEvent *event)//����������Ʒ������ķ���
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

        return true;//Ŀǰ�ǲ���Ǯ������֮��Ĵ��������޸�

}
void MainWindow::Enemywaypoints()//��עÿһ�����������ת�۵㣬������ʼ����յ㡣
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
}//��ʱ�趨Ϊ6�����ˣ�ÿ������
void MainWindow::getHpDamage(int damage/* = 1*/)
{
    // ��ʱ��ʵ�֣��Ժ�������л��ط�Ѫ��Ϊ
}
void MainWindow::removeEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    m_enemyList.removeOne(enemy);
    delete enemy;
    if (m_enemyList.empty())
    {
        ++m_waves; // ��ǰ������1
        // ������ȡ��һ��
        if (!loadWave())
        {
            // ��û����һ��ʱ�������ʾ��Ϸʤ��
            // ������Ϸʤ����־Ϊtrue
            m_gameWin = true;
            // ��Ϸʤ��ת����Ϸʤ������

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
