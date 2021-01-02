#pragma once
#include <string>
#include <QMovie>
#include <QLabel>
#include <QSound>
#define MAX_ZOMBIE_NUMBER 6

class Map;
class PVZ_Widget;
class Game;

class Zombie{
  protected:
    std::string name;
    int x, y;
    int maxHP;
    int HP;
    int attack;// damage/100ms
    int speed;// 行进速度
    int cnt;
    int changepathCD;//切换道路CD
    int changepathcnt;//切换道路计时器
    int score;
    int pretime;//pretime之后开始进攻
    bool eating;//是否在吃植物
    bool slowdown;//是否被减速
    QMovie *premovie, *walkmovie, *eatmovie;
    QLabel *zombielab;
  public:
    virtual ~Zombie();
    void hit(int att, int kind);
    bool move(Map& m);
    virtual bool run(Game &g) = 0;
    friend class Game;
};

class NormalZombie: public Zombie{
  public:
    NormalZombie(int _x, int _y, PVZ_Widget* w, int level);
    bool run(Game &g);
};

class ConeheadZombie: public Zombie{
  public:
    ConeheadZombie(int _x, int _y, PVZ_Widget* w, int level);
    bool run(Game &g);
};

class NewspaperZombie: public Zombie{
  private:
    int criticalpoint;//临界点
    bool flag;
  public:
    NewspaperZombie(int _x, int _y, PVZ_Widget* w, int level);
    bool run(Game &g);
};

class PoleVaultingZombie: public Zombie{
  private:
    bool flag;//表示是否已经跳过植物
    QSound* jump;
    QMovie* aftermovie;
  public:
    ~PoleVaultingZombie();
    PoleVaultingZombie(int _x, int _y, PVZ_Widget* w, int level);
    bool run(Game &g);
};

class JackInTheBoxZombie: public Zombie{
  private:
    int bombblock;//爆炸的格子
    int bombattack;//爆炸伤害
    QSound* bomb;
  public:
    JackInTheBoxZombie(int _x, int _y, PVZ_Widget* w, int level);
    bool run(Game &g);
};

class CatapultZombie: public Zombie{
  private:
    int ballnum;
    int ballattack;
    int ballspeed;
    int bulletspeed;
    int ballcnt;
  public:
    CatapultZombie(int _x, int _y, PVZ_Widget* w, int level);
    bool run(Game &g);
};
