#pragma once
#include "Weapon.h"
class SuperWeapon2 :
	public Weapon
{
public:
	SuperWeapon2();
	~SuperWeapon2();
	void bulletAddTo(list<Bullet> &bulletArray, int x, int y);
};

