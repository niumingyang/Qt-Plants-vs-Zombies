#pragma once
#include <string>
#include <QPixmap>
#include <QLabel>
#include <QSound>
#define MAX_PLANT_NUMBER 10

class Map;
class Game;
class PVZ_Widget;

class PlantCard{
  private:
    std::string name;
    int CD;
    int cnt;
    int price;
    QPixmap pm;
  public:
    void set(std::string _name, int _CD, int _price, QString path);
    void cooling();
    bool cooled();
    friend class Store;
};

class Store{
  private:
    int sun;
    int speed;
    int cnt;
    int selected;//表示选中哪个植物卡，-1表示未选中，-2表示选中铲子
    PlantCard allplant[MAX_PLANT_NUMBER];
    QLabel* lab[MAX_PLANT_NUMBER];
    QLabel* shadowlab[MAX_PLANT_NUMBER];
    QLabel* textlab[MAX_PLANT_NUMBER];
    QLabel* sunlab;
    QLabel* shovellab;
    QSound* plant;
  public:
    Store(PVZ_Widget* w, int level);
    int get_sun();
    void addSun(int add);
    void run(PVZ_Widget* w);
    bool enough(int choice);
    bool pay(int choice, int x, int y, Map &map, PVZ_Widget* w);
    void restart(int level);
    void cool2full();
    friend class Game;
};
