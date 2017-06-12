#pragma once
#include"Bullet.h"
#include<list>
using namespace std;
class Weapon
{
public:
	Weapon();
	~Weapon();
	virtual void bulletAddTo(list<Bullet> &bulletArray, int x, int y);
protected:
	int bulletSpeed;
	int cnt;
};

