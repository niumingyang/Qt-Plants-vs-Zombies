#pragma once
#include <string>
#include <QMovie>
#include <QLabel>
#include <QSound>
#define MAX_PLANT_NUMBER 10

class Game;
class PVZ_Widget;

class Plant{
  protected:
    std::string name;
    int x, y;
    int maxHP;
    int HP;
    bool jumpover;//是否能被撑杆僵尸越过
    bool changepath;//是否能使僵尸改变道路
    bool OnGrassland;//能否种在草地上
    bool OnPlant;//能否种在植物上
    QMovie* movie;
    QLabel* plantlab;
  public:
    ~Plant();
    bool get_changepath();
    bool get_jumpover();
    void hit(int att);
    virtual void run(Game& _game){};
    friend class Block;
};

class Peashooter: public Plant{
  private:
    int attack;
    int speed;
    int cnt;
    int bulletspeed;
  public:
    Peashooter(int _x, int _y, PVZ_Widget* w);
    void run(Game& _game);
};

class Sunflower: public Plant{
  private:
    int attack;
    int speed;
    int cnt;
  public:
    Sunflower(int _x, int _y, PVZ_Widget* w);
    void run(Game& _game);
};

class Repeater: public Plant{
  private:
    int attack;
    int speed;
    int cnt;
    int bulletspeed;
  public:
    Repeater(int _x, int _y, PVZ_Widget* w);
    void run(Game& _game);
};

class Snowpea: public Plant{
  private:
    int attack;
    int speed;
    int cnt;
    int bulletspeed;
  public:
    Snowpea(int _x, int _y, PVZ_Widget* w);
    void run(Game& _game);
};

class Wallnut: public Plant{
  public:
    Wallnut(int _x, int _y, PVZ_Widget* w);
    void run(Game& _game){};
};

class Tallnut: public Plant{
  public:
    Tallnut(int _x, int _y, PVZ_Widget* w);
    void run(Game& _game){};
};

class Squash: public Plant{
  private:
    int attack;
  public:
    Squash(int _x, int _y, PVZ_Widget* w);
    void run(Game& _game);
};

class Cherrybomb: public Plant{
  private:
    int attack;
    int preparetime;
    int cnt;
    QSound* bomb;
  public:
    Cherrybomb(int _x, int _y, PVZ_Widget* w);
    void run(Game& _game);
};

class Gralic: public Plant{
  public:
    Gralic(int _x, int _y, PVZ_Widget* w);
    void run(Game& _game){};
};

class Pumpkin: public Plant{
  public:
    Pumpkin(int _x, int _y, PVZ_Widget* w);
    void run(Game& _game){};
};
