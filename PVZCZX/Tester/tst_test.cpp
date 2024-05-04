 #include <QtTest>

// add necessary includes here
#include <QTimer>
#include <QSound>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsItem>
#include <QtWidgets>
#include <QPainter>
#include <QGraphicsScene>
#include <QMovie>

#include "../src/other/button.h"
#include "../src/other/button.h"
#include "../src/other/button.h"
#include "../src/other/card.h"
#include "../src/other/map.h"
#include "../src/other/mower.h"
#include "../src/other/other.h"
#include "../src/other/pea.h"
#include "../src/other/shop.h"
#include "../src/other/shovel.h"
#include "../src/other/sun.h"
#include "../src/other/mainwindow.h"
#include "../src/plant/cherrybomb.h"
#include "../src/plant/peashooter.h"
#include "../src/plant/plant.h"
#include "../src/plant/potatomine.h"
#include "../src/plant/repeater.h"
#include "../src/plant/snowpea.h"
#include "../src/plant/sunflower.h"
#include "../src/plant/wallnut.h"
#include "../src/zombie/basiczombie.h"
#include "../src/zombie/bucketzombie.h"
#include "../src/zombie/conezombie.h"
#include "../src/zombie/footballzombie.h"
#include "../src/zombie/screenzombie.h"
#include "../src/zombie/zombie.h"
#include "../src/other/init.h"


class Test : public QObject
{
    Q_OBJECT

public:
    Test();
    ~Test();

private slots:
    void testType();
    void testBoundingRect();
    void testCollidesWithItem();

};

Test::Test()
{

}

Test::~Test()
{

}

void Test::testType()
{
    Plant plant;
    QCOMPARE(plant.type(), Plant::Type);
}

void Test::testBoundingRect()
{
    Plant plant;
    QCOMPARE(plant.boundingRect(), QRectF(-35, -35, 70, 70));
}

void Test::testCollidesWithItem()
{
    Plant plant;

    // 创建一个僵尸对象，并设置其位置
    Zombie zombie;
    zombie.setPos(plant.x(), plant.y());  // 假设僵尸在植物的同一位置

    // 现在，我们期望collidesWithItem返回true，因为僵尸在植物的同一位置
    QVERIFY(plant.collidesWithItem(&zombie, Qt::IntersectsItemShape));

    // 接下来，我们将僵尸移动到植物的远离位置
    zombie.setPos(plant.x() + 100, plant.y() + 100);  // 假设僵尸在植物的远离位置

    // 现在，我们期望collidesWithItem返回false，因为僵尸不再在植物的附近
    QVERIFY(!plant.collidesWithItem(&zombie, Qt::IntersectsItemShape));
}

QTEST_APPLESS_MAIN(Test)

#include "tst_test.moc"
