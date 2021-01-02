#include "common.h"

Bullet::Bullet(int _speed, int _attack, int _x, int _y, int _kind, PVZ_Widget* w, int _target){
    speed = _speed;
	attack = _attack;
    hit = false;
	x = _x;
	y = _y;
    target = _target;
    kind = _kind;
    switch(kind){
        case NORMALBULLET:
            movie = new QMovie(":/images/Plants/PB00.gif");
        break;
        case SNOWBULLET:
            movie = new QMovie(":/images/Plants/PB-10.gif");
        break;
        case ZOMBIEBULLET:
            movie = new QMovie(":/images/Plants/PB11.gif");
        break;
        default: movie = new QMovie(":/images/Plants/PB00.gif");
    }
    bulletlab = new QLabel(w);
    bulletlab->move(y+28, locx(x));
    bulletlab->setMovie(movie);
    movie->start();
    bulletlab->show();
}

Bullet::~Bullet(){
    delete movie;
    delete bulletlab;
}

void Bullet::move(Game &_game){
    if (kind == ZOMBIEBULLET){
        if (blocky(y+gridw) == target) {
            _game.map.blocks[x][target].eatPlant(attack, 1);
            hit = true;
            return;
        }
        if (y <= -gridw){
            hit = true;
            return;
        }
        y -= speed;
        bulletlab->move(bulletlab->pos()-QPoint(speed, 0));
        return;
    }
    Zombie* tmp = _game.HaveZombie(x, y, gridw);
    if (tmp != nullptr) {
        tmp->hit(attack, kind);
        hit = true;
        return;
    }
    if (y>=locy(ALL_COLUMN+1)){
        hit = true;
        return;
    }
    y += speed;
    bulletlab->move(bulletlab->pos()+QPoint(speed, 0));
}
