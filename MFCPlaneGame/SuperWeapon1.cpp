#include"stdafx.h"
#include "SuperWeapon1.h"

 SuperWeapon1::SuperWeapon1() {
	bulletSpeed = 1;
	cnt = 0;
}

 SuperWeapon1::~SuperWeapon1() {}

 void SuperWeapon1::bulletAddTo(list<Bullet>& bulletArray, int x, int y) {
	cnt++;
	if (cnt == bulletSpeed) {
		cnt = 0;
		bulletArray.push_back(Bullet(x, y, 1));
	}
}
