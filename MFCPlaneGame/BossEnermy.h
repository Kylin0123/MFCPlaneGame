#pragma once
#include "OrdinaryEnermy.h"
#include<list>
#include<memory>
#define GAME_HEIGHT 600
#define GAME_WIDTH 1400
#define PLAY_HEIGHT GAME_HEIGHT
#define PLAY_WIDTH (GAME_WIDTH*3/4)

class BossEnermy :
	public OrdinaryEnermy
{
public:
	BossEnermy(int x, int y, int s) : OrdinaryEnermy(x, y, s, s){ }
	~BossEnermy(){}
	void updateMap(CDC* pDC);
	bool checkHit(int x, int y, int height, int width);
	void move();
	void shoot(list<shared_ptr<Enermy> > &enermyArray);
	int getLife() { return life; }
private:
	int life = 100;
	int direction = 0;//0:left 1:right
	const int picWidth = 169;
	const int picHeight = 258;
};

