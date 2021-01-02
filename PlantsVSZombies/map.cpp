#include "common.h"

Block::Block(){
    x = y = 0;
	_plant = nullptr;
    plantonplant = nullptr;
}

void Block::set(int _x, int _y){
	x = _x;
    y = _y;
}

bool Block::addPlant(int choice, PVZ_Widget* w){
	Plant* newPlant;
	switch(choice){
        case PEASHOOTER: newPlant = new Peashooter(x, y, w); break;
        case SUNFLOWER:  newPlant = new Sunflower(x, y, w);  break;
        case REPEATER:   newPlant = new Repeater(x, y, w);   break;
        case SNOWPEA:    newPlant = new Snowpea(x, y, w);    break;
        case WALLNUT:    newPlant = new Wallnut(x, y, w);    break;
        case TALLNUT:    newPlant = new Tallnut(x, y, w);    break;
        case SQUASH:     newPlant = new Squash(x, y, w);     break;
        case CHERRYBOMB: newPlant = new Cherrybomb(x, y, w); break;
        case GRALIC:     newPlant = new Gralic(x, y, w);     break;
        case PUMPKIN:    newPlant = new Pumpkin(x, y, w);    break;
	}
    if (_plant == nullptr && newPlant->OnGrassland){
        _plant = newPlant;
        return true;
    }
    else if (_plant != nullptr && plantonplant == nullptr && newPlant->OnPlant){
        plantonplant = newPlant;
        return true;
    }
    else {
        delete newPlant;
	    return false;
    }  
}

void Block::delPlant(){
	delete _plant; 
	_plant = nullptr;
    if (plantonplant != nullptr)
        delPlantOnPlant();
}

void Block::delPlantOnPlant(){
	delete plantonplant; 
	plantonplant = nullptr;
}

void Block::eatPlant(int att, int whichfirst){
    if (whichfirst == 0){
        if (plantonplant != nullptr){
            plantonplant->hit(att);
            if (plantonplant->HP <= 0) {
		    	delPlantOnPlant();
		    }
        }
	    else if (_plant != nullptr) {
		    _plant->hit(att);
            if (_plant->HP <= 0) {
			    delPlant();
		    }
	    }
    }
    else if (whichfirst == 1){
        if (_plant != nullptr) {
		    _plant->hit(att);
            if (_plant->HP <= 0) {
			    delPlant();
		    }
	    }
    }
}

void Block::restart(){
    if (_plant != nullptr)
        delPlant();
    if (plantonplant != nullptr)
        delPlantOnPlant();
}

Map::Map(){
	for (int i = 0; i < ALL_ROW; i++) {
		for (int j = 0; j <= ALL_COLUMN; j++) {
			blocks[i][j].set(i, j);
		}
	}
}

void Map::update(Game& _game){
    for (int i = 0; i < ALL_ROW; i++) {
        for (int j = 0; j <= ALL_COLUMN; j++){
			if (blocks[i][j]._plant != nullptr){
				blocks[i][j]._plant->run(_game);
			}
            if (blocks[i][j].plantonplant != nullptr){
				blocks[i][j].plantonplant->run(_game);
			}
		}
	}
}

void Map::restart(){
    for (int i = 0; i < ALL_ROW; i++)
		for (int j = 0; j <= ALL_COLUMN; j++)
            blocks[i][j].restart();
}
