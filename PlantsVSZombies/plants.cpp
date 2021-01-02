#include "common.h"

Plant::~Plant(){
    delete movie;
    delete plantlab;
}

bool Plant::get_changepath(){
    return changepath;
}

bool Plant::get_jumpover(){
    return jumpover;
}

void Plant::hit(int att){
	HP -= att;
}

Peashooter::Peashooter(int _x, int _y, PVZ_Widget* w){
    name = "豌豆射手";
    maxHP = HP = 300;
    x = _x;
	y = _y;
    attack = 20;
    speed = (int)(1.4*FPS);
    cnt = 0;
    bulletspeed = ceil((double)82/FPS);
    jumpover = true;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
    movie = new QMovie(":/images/Plants/Peashooter/Peashooter.gif");
    plantlab = new QLabel(w);
    plantlab->move(locy(y), locx(x));
    plantlab->setMovie(movie);
    movie->start();
    plantlab->show();
}

void Peashooter::run(Game& _game){
    bool ZombiesOnPath = false;
    if (_game.HaveZombie(x, locy(y), widw) != nullptr) {
        ZombiesOnPath = true;
    }
	if (ZombiesOnPath) {
		cnt++;
		if (cnt >= speed) {
			cnt = 0;
            Bullet *p = new Bullet(bulletspeed, attack, x, locy(y), NORMALBULLET, _game.w);
            _game.AddBullet(p);
		}
	}
}

Sunflower::Sunflower(int _x, int _y, PVZ_Widget* w){
    name = "向日葵";
    maxHP = HP = 300;
    attack = 50;
    x = _x;
	y = _y;
    speed = 20*FPS;
    cnt = 0;
    jumpover = true;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
    movie = new QMovie(":/images/Plants/SunFlower/SunFlower1.gif");
    plantlab = new QLabel(w);
    plantlab->move(locy(y), locx(x));
    plantlab->setMovie(movie);
    movie->start();
    plantlab->show();
}

void Sunflower::run(Game& _game){
	cnt++;
	if (cnt >= speed) {
		cnt = 0;
		_game.store.addSun(attack);
	}
}

Repeater::Repeater(int _x, int _y, PVZ_Widget* w){
    name = "双发射手";
    maxHP = HP = 300;
    x = _x;
	y = _y;
    attack = 20;
    speed = (int)(1.4*FPS);
    cnt = 0;
    bulletspeed = ceil((double)82/FPS);
    jumpover = true;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
    movie = new QMovie(":/images/Plants/Repeater/Repeater.gif");
    plantlab = new QLabel(w);
    plantlab->move(locy(y), locx(x));
    plantlab->setMovie(movie);
    movie->start();
    plantlab->show();
}

void Repeater::run(Game& _game){
    bool ZombiesOnPath = false;
    if (_game.HaveZombie(x, locy(y), widw) != nullptr) {
        ZombiesOnPath = true;
    }
	if (ZombiesOnPath) {
		cnt++;
		if (cnt >= speed) {
			cnt = 0;
            Bullet *p = new Bullet(bulletspeed, attack, x, locy(y), NORMALBULLET, _game.w);
            _game.AddBullet(p);
            Bullet *q = new Bullet(bulletspeed, attack, x, locy(y)+20, NORMALBULLET, _game.w);
            _game.AddBullet(q);
		}
	}
}

Snowpea::Snowpea(int _x, int _y, PVZ_Widget* w){
    name = "寒冰射手";
    maxHP = HP = 300;
    x = _x;
	y = _y;
    attack = 20;
    speed = (int)(1.4*FPS);
    cnt = 0;
    bulletspeed = ceil((double)82/FPS);
    jumpover = true;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
    movie = new QMovie(":/images/Plants/SnowPea/SnowPea.gif");
    plantlab = new QLabel(w);
    plantlab->move(locy(y), locx(x));
    plantlab->setMovie(movie);
    movie->start();
    plantlab->show();
}

void Snowpea::run(Game& _game){
    bool ZombiesOnPath = false;
    if (_game.HaveZombie(x, locy(y), widw) != nullptr) {
        ZombiesOnPath = true;
    }
	if (ZombiesOnPath) {
		cnt++;
		if (cnt >= speed) {
			cnt = 0;
            Bullet *p = new Bullet(bulletspeed, attack, x, locy(y), SNOWBULLET, _game.w);
            _game.AddBullet(p);
		}
	}
}

Wallnut::Wallnut(int _x, int _y, PVZ_Widget* w){
    name = "坚果墙";
    maxHP = HP = 4000;
    x = _x;
	y = _y;
    jumpover = true;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
    movie = new QMovie(":/images/Plants/WallNut/WallNut.gif");
    plantlab = new QLabel(w);
    plantlab->move(locy(y), locx(x));
    plantlab->setMovie(movie);
    movie->start();
    plantlab->show();
}

Tallnut::Tallnut(int _x, int _y, PVZ_Widget* w){
    name = "高坚果";
    maxHP = HP = 8000;
    x = _x;
	y = _y;
    jumpover = false;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
    movie = new QMovie(":/images/Plants/TallNut/TallNut.gif");
    plantlab = new QLabel(w);
    plantlab->move(locy(y), locx(x)-30);
    plantlab->setMovie(movie);
    movie->start();
    plantlab->show();
}

Squash::Squash(int _x, int _y, PVZ_Widget* w){
    name = "倭瓜";
    attack = 1800;
    maxHP = HP = 300;
    x = _x;
	y = _y;
    jumpover = true;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
    movie = new QMovie(":/images/Plants/Squash/Squash.gif");
    plantlab = new QLabel(w);
    plantlab->move(locy(y)-9, locx(x)-130);
    plantlab->setMovie(movie);
    movie->start();
    plantlab->show();
}

void Squash::run(Game& _game){
    Zombie* tmp;
    if ((tmp = _game.HaveZombie(x, locy(y), gridw)) != nullptr){
        while (tmp != nullptr){
            tmp->hit(attack, ATTACK);
            tmp = _game.HaveZombie(x, locy(y), gridw);
        }
        _game.map.blocks[x][y].delPlant();
    }
    else if ((tmp = _game.HaveZombie(x, locy(y+1), gridw)) != nullptr){
        while (tmp != nullptr){
            tmp->hit(attack, ATTACK);
            tmp = _game.HaveZombie(x, locy(y+1), gridw);
        }
        _game.map.blocks[x][y].delPlant();
    }
}

Cherrybomb::Cherrybomb(int _x, int _y, PVZ_Widget* w){
    name = "樱桃炸弹";
    attack = 1800;
    maxHP = HP = 300;
    x = _x;
	y = _y;
    jumpover = true;
    preparetime = 1*FPS;
    cnt = 0;
    changepath = false;
    OnGrassland = true;
    OnPlant = false;
    movie = new QMovie(":/images/Plants/CherryBomb/CherryBomb.gif");
    plantlab = new QLabel(w);
    plantlab->move(locy(y)-15, locx(x));
    plantlab->setMovie(movie);
    movie->start();
    plantlab->show();
    bomb = new QSound(":/wavaudio/cherrybomb.wav");
}

void Cherrybomb::run(Game& _game){
    bool ZombiesInrange = false;
    for (int i = x-1; i < x+2; ++i){
        if (_game.HaveZombie(i, locy(y-1), 3*gridw) != nullptr){
            ZombiesInrange = true;
            break;
        }
    }
	if (ZombiesInrange) {
		cnt++;
		if (cnt >= preparetime) {
            Zombie* tmp;
            for (int i = x-1; i < x+2; ++i){
                while ((tmp = _game.HaveZombie(i, locy(y-1), 3*gridw)) != nullptr)
                    tmp->hit(attack, ATTACK);
            }
            bomb->play();
            _game.map.blocks[x][y].delPlant();
		}
	}
}

Gralic::Gralic(int _x, int _y, PVZ_Widget* w){
    name = "大蒜";
    maxHP = HP = 400;
    x = _x;
	y = _y;
    jumpover = true;
    changepath = true;
    OnGrassland = true;
    OnPlant = false;
    movie = new QMovie(":/images/Plants/Garlic/Garlic.gif");
    plantlab = new QLabel(w);
    plantlab->move(locy(y)+5, locx(x)+15);
    plantlab->setMovie(movie);
    movie->start();
    plantlab->show();
}

Pumpkin::Pumpkin(int _x, int _y, PVZ_Widget* w){
    name = "南瓜头";
    maxHP = HP = 4000;
    x = _x;
	y = _y;
    jumpover = true;
    changepath = false;
    OnGrassland = false;
    OnPlant = true;
    movie = new QMovie(":/images/Plants/PumpkinHead/PumpkinHead1.gif");
    plantlab = new QLabel(w);
    plantlab->move(locy(y)-7, locx(x)+26);
    plantlab->setMovie(movie);
    movie->start();
    plantlab->show();
}
