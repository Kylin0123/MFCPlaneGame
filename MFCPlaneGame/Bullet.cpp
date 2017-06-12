#include"stdafx.h"
#include "Bullet.h"
#include"Resource.h"

 Bullet::Bullet(int x, int y, int s) {
	posX = x;
	posY = y;
	speed = s;
	cnt = 0;
}

 int Bullet::getX() { return posX; }

 int Bullet::getY() { return posY; }

 void Bullet::updateMap(CDC* pDC) {
	 CPngImage image;
	 CBitmap bitmap;
	 image.Load(IDB_PLAYER_BULLET, AfxGetInstanceHandle());
	 bitmap.Attach(image.Detach());
	 CDC dcCompatible;
	 dcCompatible.CreateCompatibleDC(pDC);  // 创建与当前DC（pDC）兼容的DC
	 dcCompatible.SelectObject(&bitmap);
	 pDC->AlphaBlend(posY - picWidth / 2,
		 posX,
		 picWidth,
		 picHeight,
		 &dcCompatible,
		 0,
		 0,
		 5,
		 11,
		 { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

 void Bullet::move() {
	cnt++;
	if (cnt == speed) {
		cnt = 0;
		posX-=5;
	}
}

 bool Bullet::checkBorder(int x1, int y1, int x2, int y2) {
	if (posX < x1) return false;
	if (posY < y1) return false;
	if (posX > x2) return false;
	if (posY > y2) return false;
	return true;
}

 bool Bullet::checkHit(int x, int y) {
	if (posX == x && posY == y)
		return true;
	if (posX == x - 1 && posY == y)
		return true;
	if (posX == x + 1 && posY == y)
		return true;
	return false;
}

 Bullet::~Bullet() {}
