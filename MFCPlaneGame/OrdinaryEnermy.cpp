#include"stdafx.h"
#include "OrdinaryEnermy.h"
#include"resource.h"

 OrdinaryEnermy::OrdinaryEnermy(int x, int y, int s, int ss) :Enermy(x, y, s), shootSpeed(ss), shootSpeedCnt(0) { }

 OrdinaryEnermy::~OrdinaryEnermy() {}

 void OrdinaryEnermy::updateMap(CDC* pDC) {
	 CPngImage cimage;
	 CBitmap bitmap;
	 cimage.Load(IDB_ORDINARY_ENERMY, AfxGetInstanceHandle());
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
		 57,
		 43,
		 { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

 void OrdinaryEnermy::shoot(list<shared_ptr<Enermy>>& enermyArray) {
	shootSpeedCnt++;
	if (shootSpeed == shootSpeedCnt) {
		shootSpeedCnt = 0;
		enermyArray.push_back(shared_ptr<Enermy>(new Enermy(posX + 1, posY, 1)));
	}
}

 void OrdinaryEnermy::move() {
	cnt++;
	if (cnt == speed) {
		cnt = 0;
		posX++;
		//if (rand() % 2) posY--;
		//else posY++;
	}
}

 bool OrdinaryEnermy::checkHit(int x, int y, int height, int width) {
	if (abs(x - posX) <= (height + picHeight) / 2 && abs(y - posY) <= (width + picWidth) / 2)
		return true;
	return false;
}
