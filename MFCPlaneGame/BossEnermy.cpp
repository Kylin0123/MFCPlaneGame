#include"stdafx.h"
#include "BossEnermy.h"
#include"resource.h"

  void BossEnermy::updateMap(CDC * pDC)
  {
	  CPngImage cimage;
	  CBitmap bitmap;
	  cimage.Load(IDB_BOSS_ENERMY, AfxGetInstanceHandle());
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
		  169,
		  258,
		  { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
  }

  bool BossEnermy::checkHit(int x, int y, int height, int width)
  {
	  if (abs(x - posX) <= (height + picHeight) / 2 && abs(y - posY) <= (width + picWidth) / 2)
	  {
		  life--;
		  return true;
	  }
	  return false;
  }

 void BossEnermy::move() {
	cnt++;
	if (cnt == speed) {
		cnt = 0;
		if (posX <= PLAY_HEIGHT / 3)
			posX++;
		else {
			if (direction == 0) {
				posY--;
				if (posY < 4)
					direction = 1;
			}
			else {
				posY++;
				if (posY > PLAY_WIDTH - 5)
					direction = 0;
			}
		}
	}
}

 void BossEnermy::shoot(list<shared_ptr<Enermy>>& enermyArray) {
	shootSpeedCnt++;
	if (shootSpeed == shootSpeedCnt) {
		shootSpeedCnt = 0;
		enermyArray.push_back(shared_ptr<Enermy>(new Enermy(posX + 1, posY, 1)));
		enermyArray.push_back(shared_ptr<Enermy>(new Enermy(posX + 1, posY - 50, 1)));
		enermyArray.push_back(shared_ptr<Enermy>(new Enermy(posX + 1, posY + 50, 1)));
	}
}
