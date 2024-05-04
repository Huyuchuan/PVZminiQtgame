#include "map.h"

//地图：需要处理拖放事件，执行种植或铲除。


Map::Map()
{
    dragOver = false;
    setAcceptDrops(true);
}

QRectF Map::boundingRect() const
{
    return QRectF(-369, -235, 738, 470);
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
    //// painter->setPen(Qt::black);
    //// painter->drawRect(boundingRect());
}

//开始拖拽
void Map::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText())
    {
        //Sets the accept flag of the given gestureType object to the specified value.
        event->setAccepted(true);
        dragOver = true;
        update();
    }
    else
        event->setAccepted(false);
}
//拖拽离开
void Map::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    dragOver = false;
    update();
}
//拖拽后的结果：种植植物 或者 铲除植物
void Map::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dragOver = false;
    if (event->mimeData()->hasText())
    {
        QString s = event->mimeData()->text();
        QPointF pos = mapToScene(event->pos());
        pos.setX((int(pos.x()) - 249) / 82 * 82 + 290);
        pos.setY((int(pos.y()) - 81) / 98 * 98 + 130);
        L_DEBUG(QString("drag at position (%1, %2)\t").arg(pos.x()).arg(pos.y()));
        if (s == "Shovel")
        {
            Shovel *shovel = qgraphicsitem_cast<Shovel *>(scene()->items(QPointF(830, 15))[0]);
            shovel->removePlant(pos);
            L_INFO("Shovel a Plant\t");
        }
        else
        {
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(300, 15))[0]);
            shop->addPlant(s, pos);
            L_INFO("Add a Plant\t");
        }
    }
    update();
}
