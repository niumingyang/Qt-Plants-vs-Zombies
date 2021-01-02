#include "common.h"

Zombie::~Zombie(){
    delete walkmovie;
    delete eatmovie;
    delete premovie;
    delete zombielab;
}

void Zombie::hit(int att, int kind){
    HP -= att;
    if (kind == SNOWBULLET){
        if (!slowdown){
            slowdown = true;
            speed *= 2;
        }
    }
}

bool Zombie::move(Map& m){
    if (!eating) {
        zombielab->setMovie(walkmovie);
        walkmovie->start();
        cnt++;
        if (cnt >= speed){
            cnt = 0;
            y -= 1;
            zombielab->move(zombielab->pos()-QPoint(1, 0));
            if (y < locy(0)-50)
                return true;
        }
	}
	else {
        m.blocks[x][blocky(y+50)].eatPlant(attack);
        zombielab->setMovie(eatmovie);
        eatmovie->start();
        if (m.blocks[x][blocky(y+50)]._plant == nullptr){
            changepathcnt = 0;
            return false;
        }
        if (m.blocks[x][blocky(y+50)].plantonplant == nullptr && m.blocks[x][blocky(y+50)]._plant->get_changepath()){
            changepathcnt++;
            if (changepathcnt >= changepathCD){
                changepathcnt = 0;
                int dirt = 0;// 0代表up，1代表down
                if (x == 0) dirt = 1;
                else if (x == ALL_ROW-1) dirt = 0;
                else {
                    if (rand()%2) dirt = 1;
                    else dirt = 0;
                }
                if (dirt){
                    x++;
                    zombielab->move(zombielab->pos()+QPoint(0, gridh));
                    zombielab->setMovie(walkmovie);
                    walkmovie->start();
                }
                else{
                    x--;
                    zombielab->move(zombielab->pos()-QPoint(0, gridh));
                    zombielab->setMovie(walkmovie);
                    walkmovie->start();
                }
            }
        }
	}
    return false;
}

NormalZombie::NormalZombie(int _x, int _y, PVZ_Widget* w, int level){
    name = "普通僵尸";
    maxHP = HP = (int)270*(0.5+level*0.5);
    x = _x;
    y = _y;
    attack = 120/FPS;
    speed = (5.5*FPS)/82;
    eating = false;
    slowdown = false;
    score = 50;
    changepathCD = (int)(0.5*FPS);
    changepathcnt = 0;
    pretime = 3*FPS;
    cnt = 0;
    premovie = new QMovie(":/images/Zombies/Zombie/1.gif");
    walkmovie = new QMovie(":/images/Zombies/Zombie/Zombie.gif");
    eatmovie = new QMovie(":/images/Zombies/Zombie/ZombieAttack.gif");
    zombielab = new QLabel(w);
    zombielab->move(y, locx(x)-30);
    zombielab->setMovie(premovie);
    premovie->start();
    zombielab->show();
}

bool NormalZombie::run(Game &g){
    if (pretime > 0){
        pretime--;
        return false;
    }
    return move(g.map);
}

ConeheadZombie::ConeheadZombie(int _x, int _y, PVZ_Widget* w, int level){
    name = "路障僵尸";
    maxHP = HP = (int)640*(0.5+level*0.5);
    x = _x;
    y = _y;
    attack = 120/FPS;
    speed = (5.5*FPS)/82;
    eating = false;
    slowdown = false;
    score = 100;
    changepathCD = (int)(0.5*FPS);
    changepathcnt = 0;
    pretime = 3*FPS;
    cnt = 0;
    premovie = new QMovie(":/images/Zombies/ConeheadZombie/1.gif");
    walkmovie = new QMovie(":/images/Zombies/ConeheadZombie/ConeheadZombie.gif");
    eatmovie = new QMovie(":/images/Zombies/ConeheadZombie/ConeheadZombieAttack.gif");
    zombielab = new QLabel(w);
    zombielab->move(y, locx(x)-55);
    zombielab->setMovie(premovie);
    premovie->start();
    zombielab->show();
}

bool ConeheadZombie::run(Game &g){
    if (pretime > 0){
        pretime--;
        return false;
    }
    return move(g.map);
}

NewspaperZombie::NewspaperZombie(int _x, int _y, PVZ_Widget* w, int level){
    name = "读报僵尸";
    maxHP = HP = (int)420*(0.5+level*0.5);
    x = _x;
    y = _y;
    attack = 120/FPS;
    speed = (5.5*FPS)/82;
    eating = false;
    slowdown = false;
    score = 150;
    changepathCD = (int)(0.5*FPS);
    changepathcnt = 0;
    criticalpoint = maxHP*2/3;
    flag = false;
    pretime = 3*FPS;
    cnt = 0;
    premovie = new QMovie(":/images/Zombies/NewspaperZombie/1.gif");
    walkmovie = new QMovie(":/images/Zombies/NewspaperZombie/HeadWalk1.gif");
    eatmovie = new QMovie(":/images/Zombies/NewspaperZombie/HeadAttack1.gif");
    zombielab = new QLabel(w);
    zombielab->move(y, locx(x)-35);
    zombielab->setMovie(premovie);
    premovie->start();
    zombielab->show();
}

bool NewspaperZombie::run(Game &g){
    if (pretime > 0){
        pretime--;
        return false;
    }
    if (HP <= criticalpoint && !flag){
        flag = true;
        speed = (1.8*FPS)/82;
        if (slowdown) speed *= 2;
    }
    return move(g.map);
}

PoleVaultingZombie::PoleVaultingZombie(int _x, int _y, PVZ_Widget* w, int level){
    name = "撑杆僵尸";
    maxHP = HP = (int)500*(0.5+level*0.5);
    x = _x;
    y = _y;
    attack = 120/FPS;
    speed = (3*FPS)/82;
    eating = false;
    slowdown = false;
    score = 150;
    changepathCD = (int)(0.5*FPS);
    changepathcnt = 0;
    flag = false;
    pretime = 3*FPS;
    cnt = 0;
    premovie = new QMovie(":/images/Zombies/PoleVaultingZombie/1.gif");
    walkmovie = new QMovie(":/images/Zombies/PoleVaultingZombie/PoleVaultingZombie.gif");
    eatmovie = new QMovie(":/images/Zombies/PoleVaultingZombie/PoleVaultingZombieAttack.gif");
    aftermovie = new QMovie(":/images/Zombies/PoleVaultingZombie/PoleVaultingZombieWalk.gif");
    zombielab = new QLabel(w);
    zombielab->move(y-100, locx(x)-45);
    zombielab->setMovie(premovie);
    premovie->start();
    zombielab->show();
    jump = new QSound(":/wavaudio/polevault.wav");
}

PoleVaultingZombie::~PoleVaultingZombie(){
    delete jump;
    if (!flag) delete aftermovie;
}

bool PoleVaultingZombie::run(Game &g){
    if (pretime > 0){
        pretime--;
        return false;
    }
    if (eating && !flag && g.map.blocks[x][blocky(y+50)]._plant->get_jumpover()){
        y -= gridw;
        zombielab->move(zombielab->pos()-QPoint(gridw, 0));
        flag = true;
        speed = (5.5*FPS)/82;
        jump->play();
        delete walkmovie;
        walkmovie = aftermovie;
        if (y < locy(0)-50) return true;
        else return false;
    }
    return move(g.map);
}

JackInTheBoxZombie::JackInTheBoxZombie(int _x, int _y, PVZ_Widget* w, int level){
    name = "小丑僵尸";
    maxHP = HP = (int)500*(0.5+level*0.5);
    x = _x;
    y = _y;
    attack = 120/FPS;
    speed = (3*FPS)/82;
    eating = false;
    slowdown = false;
    score = 200;
    changepathCD = (int)(0.5*FPS);
    changepathcnt = 0;
    bombattack = 1800;
    pretime = 3*FPS;
    cnt = 0;
    bombblock = (rand()%2 ? rand()%3 : rand()%(ALL_COLUMN-3)+3);
    premovie = new QMovie(":/images/Zombies/JackinTheBoxZombie/1.gif");
    walkmovie = new QMovie(":/images/Zombies/JackinTheBoxZombie/Walk.gif");
    eatmovie = new QMovie(":/images/Zombies/JackinTheBoxZombie/Attack.gif");
    zombielab = new QLabel(w);
    zombielab->move(y, locx(x)-50);
    zombielab->setMovie(premovie);
    premovie->start();
    zombielab->show();
    bomb = new QSound(":/wavaudio/cherrybomb.wav");
}

bool JackInTheBoxZombie::run(Game &g){
    if (pretime > 0){
        pretime--;
        return false;
    }
    int _y = blocky(y+50);
    if (_y == bombblock){
        HP = 0;
        bomb->play();
        for (int i = x-1; i <= x+1; ++i)
            for (int j = _y-1; j <= _y+1; ++j)
                if (i >= 0 && i < ALL_ROW && j >= 0 && j <= ALL_COLUMN)
                    g.map.blocks[i][j].eatPlant(bombattack);
    }
    return move(g.map);
}

CatapultZombie::CatapultZombie(int _x, int _y, PVZ_Widget* w, int level){
    name = "投石僵尸";
    maxHP = HP = (int)850*(0.5+level*0.5);
    x = _x;
    y = _y;
    attack = 1000/FPS;
    speed = (8*FPS)/82;
    eating = false;
    slowdown = false;
    score = 200;
    changepathCD = (int)(0.5*FPS);
    changepathcnt = 0;
    ballnum = 20;
    ballattack = 50;
    ballspeed = (int)(2.5*FPS);
    bulletspeed = ceil((double)82/FPS);
    ballcnt = 0;
    pretime = 3*FPS;
    cnt = 0;
    premovie = new QMovie(":/images/Zombies/Zomboni/1.gif");
    walkmovie = new QMovie(":/images/Zombies/Zomboni/2.gif");
    eatmovie = new QMovie(":/images/Zombies/Zomboni/4.gif");
    zombielab = new QLabel(w);
    zombielab = new QLabel(w);
    zombielab->move(y, locx(x)-85);
    zombielab->setMovie(premovie);
    premovie->start();
    zombielab->show();
}

bool CatapultZombie::run(Game &g){
    if (pretime > 0){
        pretime--;
        return false;
    }
    if (ballnum > 0){
        int PlantOnPath = -1;
        for (int j = 0; j <= blocky(y+50); j++) {
            if (g.map.blocks[x][j]._plant != nullptr) {
			    PlantOnPath = j; 
                break;
		    }
	    }
        if (PlantOnPath == -1){
            ballcnt = 0;
            return move(g.map);
        }
        else {
            ballcnt++;
            if (ballcnt >= ballspeed){
                ballcnt = 0;
                Bullet *p = new Bullet(bulletspeed, ballattack, x, y, ZOMBIEBULLET, g.w, PlantOnPath);
                g.AddBullet(p);
                ballnum--;
            }
            return false;
        }
    }
    else return move(g.map);
}
