#include "sun.h"
#include "shop.h"

//随机位置掉落
Sun::Sun()
{
    dest = QPointF(290 + qrand() % (82 * 7), 130 + qrand() % (98 * 5));
    setPos(QPointF(dest.x(), 70));
    speed = 60.0 * 50 / 1000;
    counter = 0;
    time = int(10.0 * 1000 / 33);
    movie = new QMovie(":/images/Sun.gif");
    movie->start();
    setAcceptedMouseButtons(Qt::LeftButton);
}
//在具体位置生成
Sun::Sun(QPointF pos)
{
    dest = QPointF(pos.x() + qrand() % 30 - 15, pos.y() + qrand() % 30 + 15);
    setPos(QPointF(dest.x(), pos.y()));
    speed = 60 * 50 / 1000;
    counter = 0;
    time = int(10.0 * 1000 / 33);
    movie = new QMovie(":/images/Sun.gif");
    movie->start();
    setAcceptedMouseButtons(Qt::LeftButton);
}

Sun::~Sun()
{
    if (movie)
        delete movie;
}

QRectF Sun::boundingRect() const
{
    return QRectF(-35, -35, 70, 70);
}

void Sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(), movie->currentImage());
}

//鼠标点击拾取阳光
void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(300, 15))[0]);
    shop->sun += 25;
    counter = time;
    event->setAccepted(true);
    L_INFO("Pick sun");
}

void Sun::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (++counter >= time)
        delete this;
    else if (y() < dest.y())
        setY(y() + speed);
}
