#include "card.h"
#include "shop.h"

/* 卡片槽：主要是处理拖拽操作
 * */
const QMap<QString, int> Card::map = {{"SunFlower", 0}, {"Peashooter", 1}, {"CherryBomb", 2}, {"WallNut", 3},
                                      {"SnowPea", 4}, {"PotatoMine", 5}, {"Repeater", 6}};

const QVector<QString> Card::name = {"SunFlower", "Peashooter", "CherryBomb", "WallNut",
                                     "SnowPea", "PotatoMine", "Repeater"};
//价格
const QVector<int> Card::cost = {50, 100, 150, 50, 175, 25, 200};
//冷却时间
const QVector<int> Card::cool = {cooltime_SunFlower, cooltime_Peashooter,
                                 cooltime_CherryBomb, cooltime_WallNut,
                                 cooltime_SnowPea, cooltime_PotatoMine,
                                 cooltime_Repeater};

//-------------------------------------------------------------------------

//构造函数
Card::Card(QString s)
{
    text = s;//文本内容（用于图片文件名）
    counter = 0;//冷却时间
}
//返回矩形区域
QRectF Card::boundingRect() const
{
    return QRectF(-50, -30, 100, 60);
}

//-------------------------------绘制卡片槽----------------------------------
void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //忽略“未引用的形参”警告
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->scale(0.6, 0.58);

    //放上空卡片 和 植物图片
    painter->drawPixmap(QRect(-50, -70, 100, 140), QPixmap(":/images/Card.png"));
    painter->drawPixmap(QRect(-35, -42, 70, 70), QPixmap(":/images/" + text + ".png"));

    //写上价格
    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);
    painter->drawText(-30, 60, QString().sprintf("%3d", cost[map[text]]));


    if (counter < cool[map[text]])
    {
        // 透明度为200
        QBrush brush(QColor(0, 0, 0, 200));
        painter->setBrush(brush);
        // 根据冷却时间计算黑色矩形高度并绘制
        painter->drawRect(QRectF(-48, -68, 98, 132 * (1 - qreal(counter) / cool[map[text]])));
    }
}

//冷却时间未到达，继续冷却，counter++
void Card::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (counter < cool[map[text]])
        counter++;
}

//-----------------------------鼠标事件-------------------------------------

//鼠标按下
void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)

    //冷却时间未到，或者买不起，显示箭头
    if (counter < cool[map[text]])
        event->setAccepted(false);

    Shop *shop = qgraphicsitem_cast<Shop *>(parentItem());

    if (cost[map[text]] > shop->sun)
        event->setAccepted(false);

    setCursor(Qt::ArrowCursor);
}

/*鼠标按下，拖动卡片
 * https://doc.qt.io/qt-5/qgraphicsscenemouseevent.html#details
 * */

void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // 小于最小移动距离,不处理
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
            < QApplication::startDragDistance())
           return;

    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    QImage image(":/images/" + text + ".png");
    mime->setText(text);
    mime->setImageData(image);
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(image));
    drag->setHotSpot(QPoint(35, 35));
    drag->exec();
    setCursor(Qt::ArrowCursor);
}

//鼠标释放，恢复箭头
void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}
