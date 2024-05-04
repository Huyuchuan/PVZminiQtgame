#ifndef SHOP_H
#define SHOP_H

#include "../plant/plant.h"
#include "other.h"
#include "card.h"
#include "sun.h"
#include "../plant/sunflower.h"
#include "../plant/peashooter.h"
#include "../plant/cherrybomb.h"
#include "../plant/wallnut.h"
#include "../plant/snowpea.h"
#include "../plant/potatomine.h"
#include "../plant/repeater.h"
#include "../zombie/basiczombie.h"
#include "../simpleQtLogger.h"

//卡片槽

class Shop : public Other
{
public:
    int sun;
    Shop();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void addPlant(QString s, QPointF pos);
private:
    int counter;
    int time;
};

#endif // SHOP_H
