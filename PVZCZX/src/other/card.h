#ifndef CARD_H
#define CARD_H

#include "other.h"

//空的卡片，没有植物图像和阳光价格，这个等之后添加，这样就很方便

class Card : public Other
{
public:
    int counter;//冷却时间
    QString text;//文本内容（用于图片文件名）

    Card(QString s);

    //map vector容器，存储植物名称和价格、冷却时间等对应关系
    const static QMap<QString, int> map;
    const static QVector<QString> name;
    const static QVector<int> cost;
    const static QVector<int> cool;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;

    //鼠标事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
};

#endif // CARD_H
