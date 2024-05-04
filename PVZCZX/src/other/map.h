#ifndef BLOCK_H
#define BLOCK_H

#include "other.h"
#include "../plant/plant.h"
#include "shop.h"
#include "shovel.h"
#include <QGraphicsSceneDragDropEvent>
#include "../simpleQtLogger.h"

//背景地图草地

class Map : public Other
{
public:
    Map();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
private:
    bool dragOver;
};

#endif // BLOCK_H
