#include"stdafx.h"
#include "Weapon.h"

 Weapon::Weapon() {
	bulletSpeed = 5;
	cnt = 0;
}

 Weapon::~Weapon() {}

 void Weapon::bulletAddTo(list<Bullet>& bulletArray, int x, int y) {
	cnt++;
	if (cnt == bulletSpeed) {
		cnt = 0;
		bulletArray.push_back(Bullet(x, y, 1));
	}
}
