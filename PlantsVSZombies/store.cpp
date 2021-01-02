#include "common.h"

void PlantCard::set(string _name, int _CD, int _price, QString path){
    name = _name;
    CD = _CD;
    price = _price;
    cnt = 0;
    pm = QPixmap(path);
}

void PlantCard::cooling(){
	if (cnt >= CD) return;
	else cnt++;
}

bool PlantCard::cooled(){
    return cnt >= CD;
}

Store::Store(PVZ_Widget* w, int level){
    // logic init
    allplant[0].set("豌豆射手", 7*FPS, 100, ":/images/Card/Plants/Peashooter.png");
    allplant[1].set("向日葵", 7*FPS, 50, ":/images/Card/Plants/SunFlower.png");
    allplant[2].set("双发射手", 7*FPS, 200, ":/images/Card/Plants/Repeater.png");
    allplant[3].set("寒冰射手", 7*FPS, 175, ":/images/Card/Plants/SnowPea.png");
    allplant[4].set("坚果墙", 30*FPS, 50, ":/images/Card/Plants/WallNut.png");
    allplant[5].set("高坚果", 30*FPS, 125, ":/images/Card/Plants/TallNut.png");
    allplant[6].set("倭瓜", 30*FPS, 50, ":/images/Card/Plants/Squash.png");
    allplant[7].set("樱桃炸弹", 50*FPS, 150, ":/images/Card/Plants/CherryBomb.png");
    allplant[8].set("大蒜", 7*FPS, 50, ":/images/Card/Plants/Garlic.png");
    allplant[9].set("南瓜头", 30*FPS, 125, ":/images/Card/Plants/PumpkinHead.png");
    sun = 150 - 50*level;
    speed = (7+level)*FPS;
    cnt = 0;
    selected = -1;
    // ui init
    for (int i = 0; i < ceil(MAX_PLANT_NUMBER/5); ++i){
        for (int j = 0; j < 5; ++j){
            int index = i*5 + j;
            lab[index] = new QLabel(w);
            lab[index]->setGeometry(i*cardw, j*cardh, cardw, cardh);
            lab[index]->setPixmap(allplant[index].pm.copy(0, cardh, cardw, cardh));
            lab[index]->show();
            shadowlab[index] = new QLabel(w);
            shadowlab[index]->setGeometry(i*cardw+2, j*cardh+5, cardw-4, cardh-5);
            shadowlab[index]->setStyleSheet("background-color:rgba(125, 125, 125, 0.5)");
            shadowlab[index]->show();
            textlab[index] = new QLabel(w);
            textlab[index]->setGeometry(i*cardw, j*cardh, cardw, cardh);
            textlab[index]->setAlignment(Qt::AlignRight|Qt::AlignBottom);
            textlab[index]->setStyleSheet(QString("color:black;"
                                                  "font-weight: bold;"
                                                  "font-size: 20px;"));
            textlab[index]->setText(QString::number(allplant[index].price));
            textlab[index]->show();
        }
    }
    sunlab = new QLabel(w);
    sunlab->setGeometry(ceil(MAX_PLANT_NUMBER/5)*cardw, 0, sunlabelw, sunlabelh);
    sunlab->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    sunlab->setStyleSheet(QString("border-image:url(:/images/interface/SunBack.png);"
                                  "color:black;"
                                  "font-weight: bold;"
                                  "font-size: 24px;"));
    sunlab->setText(QString::number(sun)+"  ");
    sunlab->show();
    shovellab = new QLabel(w);
    shovellab->setGeometry(ceil(MAX_PLANT_NUMBER/5)*cardw, sunlabelh, shovellabelw, shovellabelh);
    shovellab->setPixmap(QPixmap(":/images/interface/Shovel.png"));
    shovellab->show();
    plant = new QSound(":/wavaudio/plant1.wav");
}

void Store::addSun(int add){
    sun += add;
    sunlab->setText(QString::number(sun)+"  ");
}

int Store::get_sun(){
	return sun;
}

void Store::run(PVZ_Widget* w){
    cnt++;
	if (cnt >= speed) {
		cnt = 0;
		addSun(50);
        sunlab->setText(QString::number(sun)+"  ");
	}
	for (int i = 0; i < MAX_PLANT_NUMBER; i++) {
		allplant[i].cooling();
	}
    for (int i = 0; i < MAX_PLANT_NUMBER; ++i){
        if (allplant[i].cooled())
            lab[i]->setPixmap(allplant[i].pm.copy(0, 0, cardw, cardh));
        else
            lab[i]->setPixmap(allplant[i].pm.copy(0, cardh, cardw, cardh));
        double rate = 1-(double)allplant[i].cnt/allplant[i].CD;
        shadowlab[i]->resize(cardw-4, (cardh-5)*rate);
        if (i == selected)
            lab[i]->setStyleSheet("border:2px solid yellow;");
        else lab[i]->setStyleSheet("");
    }
    if (selected == -2)
        shovellab->setStyleSheet("border:2px solid yellow;");
    else shovellab->setStyleSheet("");
}

bool Store::enough(int choice){
    return sun >= allplant[choice].price && allplant[choice].cooled();
}

bool Store::pay(int choice, int x, int y, Map &map, PVZ_Widget* w){
    if (enough(choice)) {
        if (map.blocks[x][y].addPlant(choice, w)) {
			sun -= allplant[choice].price;
            sunlab->setText(QString::number(sun)+"  ");
			allplant[choice].cnt = 0;
            plant->play();
			return true;
		}
	}
	return false;
}

void Store::restart(int level){
    sun = 250 - 50*level;
    sunlab->setText(QString::number(sun)+"  ");
    cnt = 0;
    selected = -1;
    for (int i = 0; i < MAX_PLANT_NUMBER; ++i){
        allplant[i].cnt = 0;
    }
}

void Store::cool2full(){
    for (int i = 0; i < MAX_PLANT_NUMBER; ++i){
        allplant[i].cnt = allplant[i].CD;
    }
}
