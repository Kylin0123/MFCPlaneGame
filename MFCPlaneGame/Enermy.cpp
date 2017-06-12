#include"stdafx.h"
#include "Enermy.h"
#include"resource.h"

 Enermy::Enermy(int x, int y, int s) {
	posX = x;
	posY = y;
	speed = s;
	cnt = 0;
}

 Enermy::~Enermy() {}

 void Enermy::updateMap(CDC* pDC) {
	 CPngImage cimage;
	 CBitmap bitmap;
	 cimage.Load(IDB_ENERMY_BULLET, AfxGetInstanceHandle());
	 bitmap.Attach(cimage.Detach());
	 CDC dcCompatible;
	 dcCompatible.CreateCompatibleDC(pDC);
	 dcCompatible.SelectObject(&bitmap);
	 pDC->AlphaBlend(posY - picWidth / 2,
		 posX - picHeight / 2,
		 picWidth,
		 picHeight,
		 &dcCompatible,
		 0,
		 0,
		 5,
		 11,
		 { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

 void Enermy::move() {
	cnt++;
	if (cnt == speed) {
		cnt = 0;
		posX+=3;
	}
}

 bool Enermy::checkBorder(int x1, int y1, int x2, int y2) {
	if (posX < x1) return false;
	if (posY < y1) return false;
	if (posX > x2) return false;
	if (posY > y2) return false;
	return true;
}

 bool Enermy::checkHit(int x, int y, int height, int width) {
	if (abs(x - posX) <= (height + picHeight) / 2 && abs(y - posY) <= (width + picWidth) / 2)
		return true;
	return false;
}
