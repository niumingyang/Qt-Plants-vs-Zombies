#pragma once
#include "map.h"
#include "store.h"
#include "plants.h"
#include "bullets.h"
#include "zombies.h"
#include "pvz_widget.h"
#include "ui_pvz_widget.h"

#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <fstream>
#include <QApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QMovie>
#include <QSize>
#include <QTimer>
#include <QDebug>
#include <QIcon>
#include <QMediaPlayer>
#include <QSound>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDialog>

#define FPS 60
#define widw 1150
#define widh 600
#define cardw 100
#define cardh 60
#define scorelabelw 200
#define scorelabelh 60
#define sunlabelw 123
#define sunlabelh 34
#define shovellabelw 77
#define shovellabelh 55
#define fpslabelw 120
#define fpslabelh 50
#define gridw 82
#define gridh 100
#define locx(i) (183 + (i)*gridh)//地块编号转化为像素坐标
#define locy(j) (257 + (j)*gridw)//地块编号转化为像素坐标
#define blockx(i) (((i)-183)/gridh)//像素坐标转化为地块编号
#define blocky(j) (((j)-257)/gridw)//像素坐标转化为地块编号
#define cardnum(i, j) (((i)/cardw)*5 + (j)/cardh)//像素坐标转化为卡片编号
#define instore(w, h) (0<=w && w<=200 && 0<=h && h <= 300)  //检测是否选择了某个植物卡
#define ingrid(w, h) (257<=w && w<=995 && 183<=h && h<=483) //检测是否选择了某个地块
#define inshovel(w, h) (200<=w && w<=277 && 34<=h && h<=89)//检测是否选择了铲子

using namespace std;

enum PVZ_STATE { RUNNING, CHOOSING, BUYING, REMOVING, GAMEOVER, PAUSE };
enum PVZ_ZOMBIE { ZOMBIE, CONEHEAD, NEWSPAPER, POLEVAULTING, JACKINTHEBOX, CATAPULT };
enum PVZ_PLANT { PEASHOOTER, SUNFLOWER, REPEATER, SNOWPEA, WALLNUT, TALLNUT, SQUASH, CHERRYBOMB, GRALIC, PUMPKIN };
enum PVZ_HITKIND { NORMALBULLET, SNOWBULLET, ATTACK, ZOMBIEBULLET };

class Game{
  private:
    Map map;
    Store store;
    vector<Bullet*> bullets;
    vector<Zombie*> zombies;
    int raw_cd; //原始产生僵尸的时间间隔
    int cd; //当前产生僵尸的时间间隔
    int cnt; //产生僵尸的计时器
    int state; //当前游戏状态
    int score; //当前游戏得分
    int selectedx, selectedy;
    int scd; //得分增加的时间间隔
    int scnt; //得分增加的计时器
    int frame;
    int level;
    // ui
    PVZ_Widget* w;
    QLabel* mark;//标记被选中的地块
    QLabel* scorelab;
    QLabel* levellab;
    QLabel* gameoverlab;
    QLabel* pauselab;
    QLabel* fpslab;
    QMovie* arrow;
    QPixmap shovel;
    QMediaPlayer* gameplayer;
    void running(QKeyEvent *event);//键盘逻辑
    void choosing(QKeyEvent *event);//键盘逻辑
    void buying(QKeyEvent *event);//键盘逻辑
    void removing(QKeyEvent *event);//键盘逻辑
    void gameover(QKeyEvent *event);
    void pause(QKeyEvent *event);
    void keyprocess(int x, int y);
    int ZombiesAllowed();
    void GenerateZombies();
    void MoveBullet();
    bool UpdateZombie();
    void DelZombie();
    void updatescore();
    QSound* buttonclick;
    QSound* pausesound;
    QSound* firepea;
    QSound* normalhit;
    QSound* plastichit;
    QSound* shieldhit;
    QSound* chomp;
    QSound* shovelsound;
  public:
    Game(PVZ_Widget* _w, int _level = 1);
    Zombie* HaveZombie(int x, int y, int scope);
    void AddBullet(Bullet* p);
    void run();
    void showfps();
    friend class PVZ_Widget;
    friend class Peashooter;
    friend class Sunflower;
    friend class Repeater;
    friend class Snowpea;
    friend class Wallnut;
    friend class Tallnut;
    friend class Squash;
    friend class Cherrybomb;
    friend class Gralic;
    friend class Pumpkin;
    friend class Bullet;
    friend class NormalZombie;
    friend class ConeheadZombie;
    friend class NewspaperZombie;
    friend class PoleVaultingZombie;
    friend class JackInTheBoxZombie;
    friend class CatapultZombie;
};
