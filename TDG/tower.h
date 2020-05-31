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
    int			m_attackrange;	// ¹¥»÷¾àÀë
    int			m_damage;		// ¹¥»÷ÉËº¦
    int			m_fireFrequency;// ¹¥»÷ÆµÂÊ
    const QPoint	m_pos;
    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;
    qreal			m_rotationSprite;
    MainWindow *	m_game;
};
#endif // TOWER_H



