#pragma once
#include<vector>
#include"Bullet.h"
#include"BossEnermy.h"
#include"Weapon.h"
#include"SuperWeapon1.h"
#include"SuperWeapon2.h"
#include<algorithm>
using namespace std;

class Player
{
public:
	Player();
	~Player();
	int getX();
	int getY();
	int getScore();
	int getLife();
	int getBomb();
	void setInitPlayer(int x, int y, int lifeNum, int bombNum);
	void updateMap(CDC* pDC);
	void control(char c);
	void checkBorder(int x1, int y1, int x2, int y2);
	void getDamaged();
	bool checkHit(int x, int y, int height, int width);
	void addBullet();
	void addBomb();
	void updateBullet(list<shared_ptr<Enermy> > &enermyArray);
	void bulletUpdateMap(CDC* pDC);
	void setPosition(int x, int y);
	const int picWidth = 102 / 1.5;
	const int picHeight = 126 / 1.5;
private:
	int posX, posY;
	int life;
	int bomb;
	int score;
	int BulletCnt;
	list<Bullet> bulletArray;
	shared_ptr<Weapon> weapon = shared_ptr<Weapon>(new Weapon);
};

