#include"stdafx.h"
#include "SuperWeapon2.h"

 SuperWeapon2::SuperWeapon2() {
	bulletSpeed = 5;
	cnt = 0;
}

 SuperWeapon2::~SuperWeapon2() {}

 void SuperWeapon2::bulletAddTo(list<Bullet>& bulletArray, int x, int y) {
	cnt++;
	if (cnt == bulletSpeed) {
		cnt = 0;
		bulletArray.push_back(Bullet(x, y, 1));
		bulletArray.push_back(Bullet(x, y - 10, 1));
		bulletArray.push_back(Bullet(x, y + 10, 1));
	}
}
