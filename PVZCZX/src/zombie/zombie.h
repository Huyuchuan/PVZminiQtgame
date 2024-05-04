#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include "../simpleQtLogger.h"
#include "../other/init.h"

/* 僵尸基类
 *
僵尸的属性包括：

* 生命值hp，用于判定死亡
* 状态state，用于记录状态
* 攻击力atk，用于造成伤害
* 速度speed，用于移动
* 动画movie，用于绘制GIF
* 动态head，用于绘制死亡僵尸头部GIF

僵尸的函数包括：

* boundingRect()，返回僵尸的边界矩形
* paint()，绘制僵尸
*
* collidesWithItem()，判定是否碰撞
* advance()，根据状态，进行碰撞检测，完成行动和状态转移
*
* setMovie()，设置动画的方便接口
*
* */

enum class ZombieType { WALK=0, ATTACK, DIE, BURN};//僵尸的四种状态，行走状态，攻击状态，死亡状态，烧焦状态

class Zombie : public QGraphicsItem
{
public:
    int hp;//生命值
    int atk;//攻击力
    qreal speed;//移动速度

    //僵尸状态
    ZombieType state;

    //僵尸属于第二类（植物是第一类）
    enum { Type = UserType + 2};


    Zombie();
    ~Zombie() override;
    QRectF boundingRect() const override;//检测具体区域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type() const override;
    void setMovie(QString path);//设置动图
    void setHead(QString path);
protected:
    QMovie *movie;
    QMovie *head;
};


#define ZOMBIE_ADVANCE(QSTRING1,QSTRING2,QSTRING3,QSTRING4)\
{\
    if (!phase)\
        return;\
    update();\
    QList<QGraphicsItem *> items = collidingItems();\
    if (hp <= 0)\
    {\
        if (state < ZombieType::DIE)\
        {\
            state = ZombieType::DIE;\
            setMovie(QSTRING1);\
            setHead(QSTRING2);\
        }\
        else if (movie->currentFrameNumber() == movie->frameCount() - 1)\
            delete this;\
        else {;}\
        return;\
    }\
    else if (!items.isEmpty())\
    {\
        Plant *plant = qgraphicsitem_cast<Plant *>(items[0]);\
        plant->hp -= atk;\
        if (state != ZombieType::ATTACK)\
        {\
            state = ZombieType::ATTACK;\
            setMovie(QSTRING3);\
        }\
        return;\
    }\
    else\
    {\
        state = ZombieType::WALK;\
        setMovie(QSTRING4);\
    }\
    setX(x() - speed);\
}

#endif // ZOOMBIE_H
