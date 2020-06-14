#ifndef TOWER_H
#define TOWER_H


#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
class MainWindow;
class QTimer;
class Tower:QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, MainWindow *game,const QPixmap &sprite = QPixmap(":/image/Tower1.png"));

    void draw(QPainter *painter) const;
    bool		m_attacking;
    int			m_attackrange;	// 攻击距离
    int			m_damage;		// 攻击伤害
    int			m_fireFrequency;// 攻击频率
    const QPoint	m_pos;//防御塔的中心点位置
    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;//防御塔尺寸规定
    qreal			m_rotationSprite;//旋转角度
    MainWindow *	m_game;
};
#endif // TOWER_H
