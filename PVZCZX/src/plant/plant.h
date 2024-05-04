#ifndef PLANT_H
#define PLANT_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include "../simpleQtLogger.h"

#include "../other/init.h"

/*植物基类

植物的属性包括：

* 生命值hp，用于判定死亡
* 状态state，用于记录状态，坚果有普通状态和受损状态，樱桃有普通状态和爆炸状态
* 攻击力atk，用于造成伤害
* 计数器counter，用于计时
* 时间间隔time，用于判定是否行动
* 动画movie，用于加载GIF

植物的函数包括：

* boundingRect()，返回植物的边界矩形
* paint()，绘制植物
*
* collidesWithItem()，判定是否碰撞
* advance()，根据计数器和状态，进行碰撞检测，完成行动和状态转移
*
* setMovie()，设置动画的方便接口
*

这些函数可以重载，其他植物的类头文件基本相似，便于批量生成！！！

* */
class Plant : public QGraphicsItem
{
public:
    int hp;
    int state;
    enum { Type = UserType + 1};
    Plant();
    ~Plant() override;

    //支持重写的函数
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type() const override;
    //设置动画
    void setMovie(QString path);
protected:
    QMovie *movie;
    int atk;
    int counter;//用于计时，比如豌豆射手发射豌豆的间隔时间
    int time;
};
#endif // PLANT_H
