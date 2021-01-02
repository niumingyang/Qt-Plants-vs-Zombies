#pragma once
#include <vector>
#define ALL_ROW 3
#define ALL_COLUMN 9

class Game;
class Plant;
class Zombie;
class Bullet;
class PVZ_Widget;

class Block{
  public:
    int x, y;
    Plant* _plant;
    Plant* plantonplant;
    Block();
    void set(int _x, int _y);
    bool addPlant(int choice, PVZ_Widget* w);
    void delPlant();
    void delPlantOnPlant();
    void eatPlant(int att, int whichfirst = 0);
    void restart();
};

class Map{
  public:
    Map();
    Block blocks[ALL_ROW][ALL_COLUMN+2];
    void update(Game& _game);
    void restart();
};
