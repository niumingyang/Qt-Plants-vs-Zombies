#pragma once
#include <QMovie>
#include <QLabel>

class Map;
class PVZ_Widget;
class Game;

class Bullet{
  protected:
    int x, y;//行号与列像素坐标
    int speed;//1帧走过的像素点
    int attack;
    int kind;
    int target;
    bool hit;
    QMovie* movie;
    QLabel* bulletlab;
  public:
    ~Bullet();
    Bullet(int _speed, int _attack, int _x, int _y, int _kind, PVZ_Widget* w, int _target = -1);
    void move(Game &_game);
    friend class Game;
};
