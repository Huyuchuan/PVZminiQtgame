#include "mainwindow.h"
#include "../simpleQtLogger.h"

/*MainWindow控制整个游戏的运行，具体流程为：
1. 播放背景音乐
2. 创建场景，设置边界
3. 创建商店（卡片槽）、卡片、铲子、地图、割草机，加入场景（背景图）
4. 创建视图，设置背景和大小
5. 创建计时器，将计时器事件timeout()绑定到场景advance()
6. 将计时器事件绑定到僵尸生成函数addZombie()和胜负判断函数check()
*/


//初始化！！！在源文件！！！
int MainWindow::ZOMBIE_GEN_TIMES_NOW=0;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //设置图标：https://www.cnblogs.com/it-tsz/p/10741114.html
    setWindowIcon(QIcon("./images/window.ico"));

    //随机数种子
    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));

    sound = new QSound(":/images/music.wav");
    sound->setLoops(QSound::Infinite);//-1 无限循环播放音乐

    timer = new QTimer;

    //创建场景
    scene = new QGraphicsScene(this);
    //图形项QGraphicsPixmapItem自身的坐标系是以图像左上角为坐标原点
    //x、y轴分别向右、向下递增
    //？？？？？还是有点迷惑
    //https://blog.csdn.net/hejinjing_tom_com/article/details/107687085
    scene->setSceneRect(150, 0, 900, 600);
    /*
     * 索引算法，是指在场景中进行图形项查找的算法。
     * QGraphicsScene中提供了两种选择，
     * 它们在一个枚举类型QGraphicsScene::ItemIndexMethod中，分别是：
            QGraphicsSecne::BspTreeIndex ：应用Binary Space Partition tree，适合于大量的静态图形项。这个是默认值。
            QGraphicsScene::NoIndex ：不用索引，搜索场景中所有的图形项，适合于经常进行图形项的添加、移动和删除等操作的情况。
        我们可以使用setItemIndexMethod()函数进行索引算法的更改。
    */
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    L_INFO("Create a scene");

    //加入卡片槽等部件
    Shop *shop = new Shop;
    shop->setPos(520, 45);
    scene->addItem(shop);

    Shovel *shovel = new Shovel;
    shovel->setPos(830, 40);
    scene->addItem(shovel);

    Button *button = new Button(sound, timer);
    button->setPos(970, 20);
    scene->addItem(button);

    Map *map = new Map;
    map->setPos(618, 326);
    scene->addItem(map);

    for (int i = 0; i < 5; ++i)
    {
        Mower *mower = new Mower;
        mower->setPos(210, 130 + 98 * i);
        scene->addItem(mower);
    }
    L_INFO("Add card slot and other parts");

    //背景图场景
    view = new QGraphicsView(scene, this);
    view->resize(902, 602);

    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/images/Background.jpg"));

    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    //绑定信号和槽函数
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &MainWindow::addZombie);//
    connect(timer, &QTimer::timeout, this, &MainWindow::check);

    //播放音乐，启动定时器等等
    sound->play();
    timer->start(33);
    view->show();
    L_INFO("load music");
}

MainWindow::~MainWindow()
{
    delete sound;
    delete timer;
    delete scene;
    delete view;
}

//生成僵尸
void MainWindow::addZombie()
{
    /*
    // static int low = 4;
    // static int high = 8;
    // static int maxtime = 20 * 1000 / 33;//设置一个maxtime
    // static int time = maxtime / 2;//轮次为无穷，因为没有停止的控制
    */
    static int time = GEN_ONE_TIME;
    static int counter = 0;//僵尸的数量

    if (ZOMBIE_GEN_TIMES_NOW < ZOMBIE_GEN_TIMES)
    {
        if (++counter >= time)
        {
            /*
            // //这是什么逻辑？？？
            // if (++low > high)
            // {
            //     maxtime /= 1.3;
            //     high *= 2;
            // }
            */
            ZOMBIE_GEN_TIMES_NOW++;
            counter = 0;//--------再次置为0

            //随机生成类型和出现位置
            //time = qrand() % (2 * maxtime / 3) + maxtime / 3;
            int type = qrand() % 100;
            int i = qrand() % 5;
            QString zz;
            Zombie *zombie;
            if (type < 40){
                zombie = new BasicZombie();
                zz = "BasicZombie";
            }
            else if (type < 70){
                zombie = new ConeZombie();
                zz = "ConeZombie";
            }
            else if (type < 80){
                zombie = new BucketZombie();
                zz = "BucketZombie";
            }
            else if (type < 90){
                zombie = new ScreenZombie();
                zz = "ScreenZombie";
            }
            else{
                zombie = new FootballZombie();
                zz = "FootballZombie";
            }

            zombie->setPos(1028, 130 + 98 * i);

            scene->addItem(zombie);

            L_DEBUG(QString("Zombie of type %1 appear at (%2, %3)").arg(zz).arg(zombie->x()).arg(zombie->y()).toStdString().c_str());
        }
    }
    
}

//检查胜负状态,使用静态变量！！！
void MainWindow::check()
{
    static int time = GEN_ONE_TIME/10;
    static int counter = 0;
    if (++counter >= time)
    {
        //判断是否输了
        counter = 0;
        const QList<QGraphicsItem *> items = scene->items();
        foreach (QGraphicsItem *item, items)
        {
            //僵尸到达了左边
            if (item->type() == Zombie::Type && item->x() < 200)
            {
                scene->addPixmap(QPixmap(":/images/ZombiesWon.png"))->setPos(336, 92);//输的图片
                scene->advance();
                timer->stop();
                return;
            }
        }

        //没输，再判断是不是最后一次，如果是的话：并且没有僵尸了，就赢了
        if (ZOMBIE_GEN_TIMES_NOW == ZOMBIE_GEN_TIMES)//最后一次生成僵尸
        {
            foreach (QGraphicsItem *item, items)
            {
                //还有僵尸就return
                if (item->type() == Zombie::Type)
                {
                    return;
                }
            }

            //到这里说明没有僵尸了，赢了！！！
            scene->addPixmap(QPixmap(":/images/PlantsWin.jpg"))->setPos(336, 92);//赢的图片
            scene->advance();
            timer->stop();
            return;
        }
        

    }
}
