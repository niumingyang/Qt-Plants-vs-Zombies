#include "common.h"

Game::Game(PVZ_Widget* _w, int _level): map(), store(_w, _level), state(RUNNING), score(0), level(_level){
    // logic init
    srand(time(0));
    raw_cd = (int)(10*FPS*(1.2-level*0.2));
    cd = raw_cd;
    cnt = 0;
    scd = 1*FPS;
    scnt = 0;
    selectedx = selectedy = 0;
    frame = 0;
    // ui init
    w = _w;
    mark = nullptr;
    arrow = new QMovie(":/images/interface/PointerDown.gif");
    shovel = QPixmap(":/images/interface/Shovel.png");
    scorelab = new QLabel(w);
    scorelab->setGeometry(widw-scorelabelw-10, 0, scorelabelw, scorelabelh);
    scorelab->setAlignment(Qt::AlignHCenter |Qt::AlignRight);
    scorelab->setStyleSheet(QString("color:black;"
                                    "font-weight: bold;"
                                    "font-size: 24px;"));
    scorelab->setText("得分："+QString::number(score));
    scorelab->show();
    levellab = new QLabel(w);
    levellab->setGeometry(widw-scorelabelw-10, widh-scorelabelh, scorelabelw, scorelabelh);
    levellab->setAlignment(Qt::AlignBottom|Qt::AlignRight);
    levellab->setStyleSheet(QString("color:black;"
                                    "font-weight: bold;"
                                    "font-size: 24px;"));
    vector<QString> lev{"简单", "正常", "困难"};
    levellab->setText("难度："+lev[level]);
    levellab->show();
    fpslab = new QLabel(w);
    fpslab->setGeometry((widw-fpslabelw)/2, 0, fpslabelw, fpslabelh);
    fpslab->setAlignment(Qt::AlignCenter);
    fpslab->setStyleSheet(QString("color:black;"
                                    "font-weight: bold;"
                                    "font-size: 24px;"));
    fpslab->setText("FPS: "+QString::number(frame));
    fpslab->show();
    gameplayer = new QMediaPlayer;
    gameplayer->setMedia(QUrl("qrc:/audio/awooga.mp3"));
    gameplayer->setVolume(50);
    gameplayer->play();
    //加载音效
    buttonclick = new QSound(":/wavaudio/buttonclick.wav");
    pausesound  = new QSound(":/wavaudio/pause.wav");
    firepea     = new QSound(":/wavaudio/firepea.wav");
    normalhit   = new QSound(":/wavaudio/splat1.wav");
    plastichit  = new QSound(":/wavaudio/plastichit.wav");
    shieldhit   = new QSound(":/wavaudio/shieldhit.wav");
    chomp       = new QSound(":/wavaudio/chomp.wav");
    shovelsound = new QSound(":/wavaudio/shovel.wav");
}

void Game::running(QKeyEvent *event){
    switch (event->key()){
        case Qt::Key_B:
            state = CHOOSING;
            selectedx = selectedy = 0;
            mark = new QLabel(w);
            mark->move(locy(selectedy)+20, locx(selectedx)+30);
            mark->setMovie(arrow);
            arrow->start();
            mark->show();
            break;
        case Qt::Key_R:
            state = REMOVING;
            selectedx = selectedy = 0;
            mark = new QLabel(w);
            mark->move(locy(selectedy)+30, locx(selectedx)+10);
            mark->setPixmap(shovel);
            mark->show();
            break;
        case Qt::Key_Escape:
            store.selected = -1;
            break;
        case Qt::Key_P:
            state = PAUSE;
            pausesound->play();
            break;
        default: break;
    }
}

void Game::choosing(QKeyEvent *event){
    if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9){
        int PlantNumber = (int)event->key() - Qt::Key_0;
        if (store.pay(PlantNumber, selectedx, selectedy, map, w)) {
            delete mark;
            mark = nullptr;
            state = RUNNING;
        }
        return;
    }
    switch (event->key()){
        case Qt::Key_Up:
            if (selectedx > 0){
                selectedx--;
                mark->move(mark->pos()-QPoint(0, gridh));
            }
            break;
        case Qt::Key_Down:
            if (selectedx < ALL_ROW-1){
                selectedx++;
                mark->move(mark->pos()+QPoint(0, gridh));
            }
            break;
        case Qt::Key_Left:
            if (selectedy > 0){
                selectedy--;
                mark->move(mark->pos()-QPoint(gridw, 0));
            }
            break;
        case Qt::Key_Right:
            if (selectedy < ALL_COLUMN-1){
                selectedy++;
                mark->move(mark->pos()+QPoint(gridw, 0));
            }
            break;
        case Qt::Key_Escape:
            store.selected = -1;
            delete mark;
            mark = nullptr;
            state = RUNNING;
            break;
        case Qt::Key_Enter: case Qt::Key_Return:
            store.selected = 0;
            state = BUYING;
            break;
        case Qt::Key_P:
            pausesound->play();
            state = PAUSE;
            break;
    }
}

void Game::buying(QKeyEvent *event){
    if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9){
        int PlantNumber = (int)event->key() - Qt::Key_0;
        if (store.pay(PlantNumber, selectedx, selectedy, map, w)) {
            delete mark;
            mark = nullptr;
            state = RUNNING;
        }
        return;
    }
    switch (event->key()){
        case Qt::Key_Up:
            store.selected = (store.selected-1) % MAX_PLANT_NUMBER;
            break;
        case Qt::Key_Down:
            store.selected = (store.selected+1) % MAX_PLANT_NUMBER;
            break;
        case Qt::Key_Left:
            store.selected = (store.selected-5+MAX_PLANT_NUMBER) % MAX_PLANT_NUMBER;
            break;
        case Qt::Key_Right:
            store.selected = (store.selected+5+MAX_PLANT_NUMBER) % MAX_PLANT_NUMBER;
            break;
        case Qt::Key_Escape:
            store.selected = -1;
            state = CHOOSING;
            break;
        case Qt::Key_Enter: case Qt::Key_Return:
            if (store.pay(store.selected, selectedx, selectedy, map, w)) {
                store.selected = -1;
                delete mark;
                mark = nullptr;
                state = RUNNING;
            }
            break;
        case Qt::Key_P:
            pausesound->play();
            state = PAUSE;
            break;
    }
}

void Game::removing(QKeyEvent *event){
    switch (event->key()){
        case Qt::Key_Up:
            if (selectedx > 0){
                selectedx--;
                mark->move(mark->pos()-QPoint(0, gridh));
            }
            break;
        case Qt::Key_Down:
            if (selectedx < ALL_ROW-1){
                selectedx++;
                mark->move(mark->pos()+QPoint(0, gridh));
            }
            break;
        case Qt::Key_Left:
            if (selectedy > 0){
                selectedy--;
                mark->move(mark->pos()-QPoint(gridw, 0));
            }
            break;
        case Qt::Key_Right:
            if (selectedy < ALL_COLUMN-1){
                selectedy++;
                mark->move(mark->pos()+QPoint(gridw, 0));
            }
            break;
        case Qt::Key_Escape:
            store.selected = -1;
            delete mark;
            mark = nullptr;
            state = RUNNING;
            break;
        case Qt::Key_Enter: case Qt::Key_Return:
            if (map.blocks[selectedx][selectedy]._plant != nullptr){
                map.blocks[selectedx][selectedy].delPlant();
                delete mark;
                mark = nullptr;
                state = RUNNING;
            }
            break;
        case Qt::Key_P:
            pausesound->play();
            state = PAUSE;
            break;
    }
}

void Game::gameover(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_Escape:
            exit(0);
        case Qt::Key_Enter: case Qt::Key_Return:
            score = 0;
            cnt = 0;
            scnt = 0;
            selectedx = selectedy = 0;
            if (mark) delete mark;
            delete gameoverlab;
            map.restart();
            store.restart(level);
            for (auto it = bullets.begin(); it != bullets.end(); ){
                delete (*it);
                it = bullets.erase(it);
            }
            for (auto it = zombies.begin(); it != zombies.end(); ){
                delete (*it);
                it = zombies.erase(it);
            }
            w->player->play();
            gameplayer->setMedia(QUrl("qrc:/audio/awooga.mp3"));
            gameplayer->play();
            state = RUNNING;
            break;
    }
}

void Game::pause(QKeyEvent *event){
    if (event->key() == Qt::Key_P){
        state = RUNNING;
        pausesound->play();
    }
}

void Game::keyprocess(int x, int y){
    if (instore(x, y)){
        store.selected = cardnum(x, y);
        buttonclick->play();
    }
    else if (ingrid(x, y) && store.selected != -1){
        if (store.selected == -2){
            int tmp_x = blockx(y), tmp_y = blocky(x);
            if (map.blocks[tmp_x][tmp_y]._plant != nullptr){
                map.blocks[tmp_x][tmp_y].delPlant();
                store.selected = -1;
                shovelsound->play();
            }
        }
        else {
            int tmp_x = blockx(y), tmp_y = blocky(x);
            if (store.pay(store.selected, tmp_x, tmp_y, map, w)) {
                store.selected = -1;
            }
        }
    }
    else if (inshovel(x, y)){
        store.selected = -2;
        buttonclick->play();
    }
}

int Game::ZombiesAllowed(){
    //出现僵尸的级别随分数变高
    return min(MAX_ZOMBIE_NUMBER, 1+score/500);
}

void Game::GenerateZombies(){
    cnt++;
	if (cnt >= cd) {
        cnt = 0;
        Zombie* newZombie = nullptr;
        int x = rand()%ALL_ROW;
        int y = locy(ALL_COLUMN);
        int type = rand()%ZombiesAllowed();
        switch(type){
            case ZOMBIE:       newZombie = new NormalZombie(x, y, w, level);       break;
            case CONEHEAD:     newZombie = new ConeheadZombie(x, y, w, level);     break;
            case NEWSPAPER:    newZombie = new NewspaperZombie(x, y, w, level);    break;
            case POLEVAULTING: newZombie = new PoleVaultingZombie(x, y, w, level); break;
            case JACKINTHEBOX: newZombie = new JackInTheBoxZombie(x, y, w, level); break;
            case CATAPULT:     newZombie = new CatapultZombie(x, y, w, level);     break;
        }
        zombies.push_back(newZombie);
	}
}

Zombie* Game::HaveZombie(int x, int y, int scope){
    for (auto& var : zombies){
        if (var->x == x && var->y+50 >= y && var->y+50 < y + scope && var->HP > 0)
            return var;
    }
    return nullptr;
}

void Game::MoveBullet(){
    for (auto& var : bullets) {
        var->move(*this);
	}
    bool hitflag = false;
	for (auto it = bullets.begin(); it != bullets.end(); ){
        if ((*it)->hit){
            if (-gridw < (*it)->y && (*it)->y < locy(ALL_COLUMN+1))
                hitflag = true;
			delete (*it);
			it = bullets.erase(it);
		}
		else it++;
	}
    if (hitflag) normalhit->play();
}

void Game::AddBullet(Bullet* p){
    bullets.push_back(p);
    firepea->play();
}

bool Game::UpdateZombie(){
    bool eatingflag = false;
    // update state
    for (auto& var : zombies){
        int i = var->x;
        int j = blocky(var->y+50);
        if (map.blocks[i][j]._plant != nullptr){
            var->eating = true;
            eatingflag = true;
        }
        else if (map.blocks[i][j]._plant == nullptr)
            var->eating = false;
    }
    if (eatingflag && frame%FPS == 0)
        chomp->play();
    // move and attack
    for (auto& var : zombies){
        if (var->run(*this)){
            gameoverlab = new QLabel(w);
            gameoverlab->move(350, 85);
            QPixmap tmp = QPixmap(":/images/interface/ZombiesWon.png");
            gameoverlab->setPixmap(tmp);
            gameoverlab->show();
            gameplayer->setMedia(QUrl("qrc:/audio/losemusic.mp3"));
            gameplayer->play();
            w->player->stop();
            w->refreshrecord(level, score);
            state = GAMEOVER;
            return true;
        }
    }
    return false;
}

void Game::DelZombie(){
	for (auto it = zombies.begin(); it != zombies.end(); ){
        if ((*it)->HP <= 0){
            score += (*it)->score;
			delete (*it);
			it = zombies.erase(it);
		}
		else it++;
	}
}

void Game::updatescore(){
    scnt++;
	if (scnt >= scd) {
		scnt = 0;
		score += 10;
        scorelab->setText("得分："+QString::number(score));
	}
    cd = max(1*FPS, raw_cd-(score/1000)*FPS);
}

void Game::run(){
    frame++;
    if (state == GAMEOVER or state == PAUSE)
        return;
    // generate zombies
    GenerateZombies();
    // update plant
    map.update(*this);
    DelZombie();
    // update bullets and zombies
    if (UpdateZombie()) return;
    MoveBullet();
    DelZombie();
    // update store
    store.run(w);
    // update score
    updatescore();
}

void Game::showfps(){
    fpslab->setText("FPS: "+QString::number(frame));
    frame = 0;
}
