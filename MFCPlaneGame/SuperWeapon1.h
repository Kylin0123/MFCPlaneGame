#pragma once
#include "Weapon.h"
class SuperWeapon1 :
	public Weapon
{
public:
	SuperWeapon1();
	~SuperWeapon1();
	void bulletAddTo(list<Bullet> &bulletArray, int x, int y);
};

